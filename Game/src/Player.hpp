#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Flock.hpp"
#include "Tile.hpp"
#include "Using.hpp"

struct Player {
};

inline auto Reflect(Player &player) {
    return Reflectable{
        "Player",
        std::make_tuple()
    };
}

inline void UpdatePlayer(World &world) {
    Registry &reg = world.GetRegistry();

    reg.ForEachEntity<Transform, Player>([&](const Entity e, const Transform &trans, Player &) {
        world.GetResource<Camera>().transform.position = Vector3f(trans.position.x, trans.position.y, -10);

        Vector2i   movement = {};
        const auto input    = world.GetResource<InputState>();

        if (input.IsKeyPressed(Key::D)) {
            movement.x = 1;
            movement.y = 0;
        }

        if (input.IsKeyPressed(Key::A)) {
            movement.x = -1;
            movement.y = 0;
        }

        if (input.IsKeyPressed(Key::W)) {
            movement.y = 1;
            movement.x = 0;
        }

        if (input.IsKeyPressed(Key::S)) {
            movement.y = -1;
            movement.x = 0;
        }

        if (movement == Vector2i{}) {
            return;
        }

        const Vector2i playerPos = Vector2i(trans.position.x, trans.position.y);

        bool moved = false;
        reg.ForEach<Tile>([&](Tile &tile) {
            if (tile.position == playerPos + movement && IsPassable(tile.type)) {
                tile.occupant = e;
                moved         = true;
            }
        });

        if (!moved) {
            return;
        }

        reg.ForEach<Tile>([&](Tile &tile) {
            if (tile.position == playerPos) {
                tile.occupant = {~0u, 0};
            }
        });
    });
}

#endif //PLAYER_HPP
