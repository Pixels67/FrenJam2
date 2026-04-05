#ifndef BOX_HPP
#define BOX_HPP

#include "Common.hpp"
#include "Math/Color.hpp"

namespace Flock::Gui {
    struct FLK_API Box {
        Color4u8 color = Color4u8::Black();
    };

    inline auto Reflect(Box &box) {
        return Reflectable{
            "Box",
            std::make_tuple(
                Field{"color", &box.color}
            )
        };
    }
}

#endif //BOX_HPP
