#ifndef FLK_SPRITERENDERER_HPP
#define FLK_SPRITERENDERER_HPP

#include <filesystem>

#include "Common.hpp"

namespace Flock::Graphics {
    struct FLK_API SpriteRenderer {
        std::string spritePath = "";
        Color4u8    color      = Color4u8::White();
    };

    inline auto Reflect(SpriteRenderer &renderer) {
        return Reflectable{
            "SpriteRenderer",
            std::make_tuple(
                Field{"spritePath", &renderer.spritePath},
                Field{"color", &renderer.color}
            )
        };
    }
}

#endif //FLK_SPRITERENDERER_HPP
