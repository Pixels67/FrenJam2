#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Flock.hpp"
#include "Interactable.hpp"
#include "Tile.hpp"
#include "Using.hpp"

struct Player {
    bool canMove = true;
};

FLK_ARCHIVE(Player, canMove)

inline std::optional<std::tuple<Entity, Ref<Interactable> > > GetNearbyInteractable(World &world, const Transform &transform) {
    const Vector2i pos = Vector2f{transform.position.x, transform.position.y};

    const std::vector positions = {
        pos + Vector2i{-1, 1}, pos + Vector2i{0, 1}, pos + Vector2i{1, 1},
        pos + Vector2i{-1, 0}, pos + Vector2i{0, 0}, pos + Vector2i{1, 0},
        pos + Vector2i{-1, -1}, pos + Vector2i{0, -1}, pos + Vector2i{1, -1}
    };

    OptionalRef<Interactable> interactable = std::nullopt;
    Entity                    entity       = {};

    auto &reg = world.Registry();
    reg.ForEach<Entity, Tile>([&](Entity e, const Tile &tile) {
        for (const auto &p: positions) {
            if (tile.position == p && tile.HasOccupant() && reg.HasComponent<Interactable>(tile.occupant)) {
                interactable = reg.Get<Interactable>(tile.occupant);
                entity       = tile.occupant;
                return;
            }
        }
    });

    if (interactable) {
        return std::make_tuple(entity, interactable.value());
    }

    return std::nullopt;
}

inline void UpdatePlayer(World &world) {
    Registry &reg = world.Registry();

    reg.ForEach<Entity, Transform, Player>([&](const Entity e, const Transform &trans, const Player &player) {
        world.Resource<Camera>().transform.position = Vector3f(trans.position.x, trans.position.y, -10);

        Vector2i   movement = {};
        const auto input    = world.Resource<InputState>();

        const auto maybeInteractable = GetNearbyInteractable(world, trans);

        if (input.IsKeyPressed(Key::E) && world.Resource<Dialogue>().IsFinished() && maybeInteractable) {
            auto &[entity, interactable] = maybeInteractable.value();

            world.Resource<Dialogue>().messages       = interactable.get().dialogue.messages;
            world.Resource<Dialogue>().currentMessage = 0;

            if (interactable.get().destroyOnInteract) {
                reg.Destroy(entity);
            }
        }

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

        if (movement == Vector2i{} || !player.canMove) {
            return;
        }

        const auto playerPos = Vector2i(trans.position.x, trans.position.y);

        bool moved = false;
        reg.ForEach<Tile>([&](Tile &tile) {
            if (tile.position == playerPos + movement && IsPassable(tile.type) && !tile.HasOccupant()) {
                tile.occupant = e;
                moved         = true;
            }
        });

        if (!moved) {
            return;
        }

        reg.ForEach<Tile>([&](Tile &tile) {
            if (tile.position == playerPos) {
                tile.occupant = {};
            }
        });
    });
}

#endif //PLAYER_HPP
