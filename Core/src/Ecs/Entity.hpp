#ifndef FLK_ENTITY_HPP
#define FLK_ENTITY_HPP

#include "Common.hpp"
#include "Reflect.hpp"

using EntityId      = u32;
using EntityVersion = u32;

namespace Flock::Ecs {
    struct Entity {
        EntityId      id      = 0;
        EntityVersion version = 0;
    };

    inline auto Reflect(Entity &entity) {
        return Reflectable{
            "Entity",
            std::make_tuple(
                Field{"id", &entity.id},
                Field{"version", &entity.version}
            )
        };
    }
}

#endif //FLK_ENTITY_HPP
