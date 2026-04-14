#ifndef FREN_HPP
#define FREN_HPP

#include "Flock.hpp"
#include "Player.hpp"
#include "Using.hpp"

static constexpr f32 s_FrenSpeed = 5.0F;

struct Fren {
};

FLK_ARCHIVE_TAG(Fren)

inline void UpdateFren(World &world) {
    Registry &reg               = world.Registry();
    auto      [time, deltaTime] = world.Resource<Time::TimeState>();

    Vector2i frenPos = {};

    reg.ForEach<Player>([&](const Player &player) {
        frenPos = player.prevPos;
    });

    reg.All<Fren>().ForEach<Transform>([&](Transform &trans) {
        trans.position.z = -1.0F;
    });

    if (frenPos == Vector2i::Zero()) {
        return;
    }

    reg.All<Fren>().ForEach<Transform>([&](Transform &trans) {
        const Vector2f actualPos = {trans.position.x, trans.position.y};

        const Vector3f dist = Vector3f{frenPos} - Vector3f{actualPos};
        if (dist.Magnitude() > s_FrenSpeed * deltaTime) {
            const Vector3f dir      = dist.Normalized();
            const Vector3f movement = dir * s_FrenSpeed * deltaTime;
            trans.position          += movement;
            trans.position.z        = -7.0F;
        } else {
            trans.position   = Vector3f{frenPos};
            trans.position.z = -7.0F;
        }
    });
}
#endif //FREN_HPP
