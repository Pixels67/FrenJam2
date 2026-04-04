#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Flock.hpp"
#include "Tile.hpp"
#include "Using.hpp"

struct Player {
    static constexpr const char *GetSprite() {
        return "assets/Circle.png";
    }

    static Vector2i GetPosition(World &world) {
        Vector2i pos = {};
        world.GetRegistry().ForEach<Tile>([&](const Tile &tile) {
            if (tile.occupant.id != ~0u && world.GetRegistry().HasComponent<Player>(tile.occupant)) {
                pos = tile.position;
            }
        });

        return pos;
    }

    static Entity GetEntity(World &world) {
        Entity e = {~0u, 0};
        world.GetRegistry().ForEachEntity<Player>([&](const Entity entity, Player &) {
            e = entity;
        });

        return e;
    }
};

inline auto Reflect(Player &player) {
    return Reflectable{
        "Player",
        std::make_tuple()
    };
}

inline void UpdatePlayer(World &world) {
    Registry &reg = world.GetRegistry();
    reg.GetOrAddComponent<SpriteRenderer>(Player::GetEntity(world)).spritePath = Player::GetSprite();

    if (!reg.HasComponent<Transform>(Player::GetEntity(world))) {
        reg.AddComponent<Transform>(Player::GetEntity(world), {.scale = Vector3f::One() * 0.5F});
    }

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

    const Vector2i playerPos = Player::GetPosition(world);

    bool moved = false;
    reg.ForEach<Tile>([&](Tile &tile) {
        if (tile.position == playerPos + movement && IsPassable(tile.type)) {
            tile.occupant = Player::GetEntity(world);
            moved = true;
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
}

#endif //PLAYER_HPP
