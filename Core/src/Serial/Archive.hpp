#ifndef FLK_ARCHIVE_HPP
#define FLK_ARCHIVE_HPP

#include "Common.hpp"
#include "Math/Math.hpp"

namespace Flock::Serial {
    enum class ArchiveType {
        Input,
        Output
    };

    class IArchive;

    template<typename T>
    bool Serialize(IArchive &archive, T &value);

    class FLK_API IArchive {
    public:
        ArchiveType type = ArchiveType::Output;

        virtual ~IArchive() = default;

        template<typename T> requires IsReflectable<T>
        bool operator()(const std::string_view key, T &value) {
            BeginObject(key);
            if (!Serialize(*this, value)) {
                EndObject();
                Debug::LogErr("IArchive: Failed to archive '{}' of type '{}'", key, GetTypeName<T>());
                return false;
            }

            EndObject();
            return true;
        }

        template<typename T>
        bool operator()(const std::string_view key, std::vector<T> &value) {
            usize size = value.size();
            BeginArray(key, size);
            value.resize(size);

            bool success = true;

            i32 idx = 0;
            for (T &elem: value) {
                BeginObject();
                if (!(*this)("value", elem)) {
                    EndObject();
                    success = false;
                    Debug::LogErr("IArchive: Failed to archive array element '{}[{}]' of type '{}'", key, idx, GetTypeName<T>());
                    continue;
                }

                EndObject();
                idx++;
            }

            EndArray();
            return success;
        }

        template<typename T> requires std::is_enum_v<T>
        bool operator()(const std::string_view key, T &value) {
            auto underlying = static_cast<u64>(value);
            (*this)(key, underlying);
            value = static_cast<T>(underlying);

            return true;
        }

        virtual usize CurrentArraySize() = 0;

        virtual bool operator()(std::string_view, bool &) = 0;

        virtual bool operator()(std::string_view, u32 &) = 0;
        virtual bool operator()(std::string_view, u64 &) = 0;

        virtual bool operator()(std::string_view, i32 &) = 0;
        virtual bool operator()(std::string_view, i64 &) = 0;

        virtual bool operator()(std::string_view, f32 &) = 0;
        virtual bool operator()(std::string_view, f64 &) = 0;

        virtual bool operator()(std::string_view, char &) = 0;
        virtual bool operator()(std::string_view, std::string &) = 0;

        virtual bool operator()(std::string_view, Vector2f &) = 0;
        virtual bool operator()(std::string_view, Vector3f &) = 0;
        virtual bool operator()(std::string_view, Vector4f &) = 0;

        virtual bool operator()(std::string_view, Vector2i &) = 0;
        virtual bool operator()(std::string_view, Vector3i &) = 0;
        virtual bool operator()(std::string_view, Vector4i &) = 0;

        virtual bool operator()(std::string_view, Color3u8 &) = 0;
        virtual bool operator()(std::string_view, Color4u8 &) = 0;

        virtual bool operator()(std::string_view, Quaternion &) = 0;

        virtual void BeginObject() = 0;
        virtual void BeginObject(std::string_view key) = 0;

        virtual void BeginArray(std::string_view key, usize &) = 0;

        virtual void EndObject() = 0;
        virtual void EndArray() = 0;
    };

    template<typename T>
    bool Serialize(IArchive &archive, T &value) {
        auto reflectable = Reflect(value);
        bool success = true;
        std::apply([&](auto &... fields) {
            if (!(archive(fields.name, *fields.value) && ...)) {
                success = false;
            }
        }, reflectable.fields);
        
        return success;
    }
}

#endif //FLK_ARCHIVE_HPP
