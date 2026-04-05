#include "World.hpp"
#include "FileIo/World.hpp"

#include "App.hpp"
#include "Asset/Assets.hpp"
#include "Audio/AudioListener.hpp"
#include "Audio/AudioSource.hpp"
#include "Event/EventRegistry.hpp"
#include "FileIo/File.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Light.hpp"
#include "Graphics/ModelRenderer.hpp"
#include "Graphics/Skybox.hpp"
#include "Graphics/SpriteRenderer.hpp"
#include "Gui/Box.hpp"
#include "Gui/Button.hpp"
#include "Gui/Image.hpp"
#include "Gui/Text.hpp"
#include "Input/Input.hpp"
#include "Math/Transform.hpp"
#include "Physics/Collider.hpp"
#include "Physics/RigidBody.hpp"
#include "Serial/JsonArchive.hpp"
#include "Time/Time.hpp"

namespace Flock::Ecs {
    World World::Default() {
        World world;
        world.SetDefaults();

        return world;
    }

    void World::SetDefaults() {
        InsertResource<Time::TimeState>();
        InsertResource<Input::InputState>();
        InsertResource<Graphics::Camera>();
        InsertResource<Graphics::AmbientLight>();
        InsertResource<Graphics::Skybox>();
        InsertResource<Audio::AudioListener>();
        InsertResource<Application>();
        InsertResource<Event::EventRegistry>();

        GetRegistry().RegisterComponent<Transform>();
        GetRegistry().RegisterComponent<RigidTransform>();
        GetRegistry().RegisterComponent<Gui::RectTransform>();
        GetRegistry().RegisterComponent<Graphics::SpriteRenderer>();
        GetRegistry().RegisterComponent<Graphics::ModelRenderer>();
        GetRegistry().RegisterComponent<Physics::BoxCollider>();
        GetRegistry().RegisterComponent<Physics::SphereCollider>();
        GetRegistry().RegisterComponent<Physics::RigidBody>();
        GetRegistry().RegisterComponent<Audio::AudioSource>();
        GetRegistry().RegisterComponent<Gui::Text>();
        GetRegistry().RegisterComponent<Gui::Button>();
        GetRegistry().RegisterComponent<Gui::Image>();
        GetRegistry().RegisterComponent<Gui::Box>();
    }

    Registry &World::GetRegistry() {
        return m_Registry;
    }

    void World::Archive(Serial::IArchive &archive) {
        archive.BeginObject("registry");
        m_Registry.Archive(archive);
        archive.EndObject();

        archive.BeginObject("resources");
        for (auto &[typeId, fn]: m_ArchiveFns) {
            if (!m_Resources.contains(typeId)) {
                continue;
            }

            fn(archive, m_Resources.at(typeId));
        }

        archive.EndObject();
    }

    bool World::Load(const std::filesystem::path &filePath) {
        const auto result = FileIo::ReadText(filePath);
        if (!result) {
            return false;
        }

        const std::string file = result.value();
        if (!Serial::Json::Parse(file)) {
            return false;
        }

        const Serial::Json json = Serial::Json::Parse(file).value();
        Serial::JsonReader reader(json);

        Archive(reader);
        return true;
    }

    bool World::Save(const std::filesystem::path &filePath) {
        Serial::JsonWriter writer;
        Archive(writer);

        const Serial::Json json = writer.GetOutput();

        return FileIo::WriteText(filePath, json.ToString());
    }
}
