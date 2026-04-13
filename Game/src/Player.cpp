#include "Player.hpp"

#include "Door.hpp"
#include "Map.hpp"
#include "Tile.hpp"

static constexpr f32 s_PlayerSpeed = 5.0F;

std::optional<std::tuple<Entity, Ref<Interactable> > > GetNearbyInteractable(World &world, const Transform &transform) {
    const Vector2i pos = Vector2f{transform.position.x, transform.position.y};

    const std::vector positions = {
        pos + Vector2i{-1, 1}, pos + Vector2i{0, 1}, pos + Vector2i{1, 1},
        pos + Vector2i{-1, 0}, pos + Vector2i{0, 0}, pos + Vector2i{1, 0},
        pos + Vector2i{-1, -1}, pos + Vector2i{0, -1}, pos + Vector2i{1, -1}
    };

    OptionalRef<Interactable> interactable = std::nullopt;
    Entity                    entity       = {};

    auto &reg = world.Registry();
    reg.ForEach<Tile>([&](const Tile &tile) {
        for (const auto &p: positions) {
            if (tile.position == p && tile.HasOccupant() && reg.Has<Interactable>(tile.occupant)) {
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

OptionalRef<Door> GetNearbyDoor(World &world, const Transform &transform) {
    const Vector2i pos = Vector2f{transform.position.x, transform.position.y};

    const std::vector positions = {
        pos + Vector2i{-1, 1}, pos + Vector2i{0, 1}, pos + Vector2i{1, 1},
        pos + Vector2i{-1, 0}, pos + Vector2i{0, 0}, pos + Vector2i{1, 0},
        pos + Vector2i{-1, -1}, pos + Vector2i{0, -1}, pos + Vector2i{1, -1}
    };

    OptionalRef<Door> door = std::nullopt;

    auto &reg = world.Registry();
    reg.ForEach<Tile>([&](const Tile &tile) {
        for (const auto &p: positions) {
            if (tile.position == p && tile.HasOccupant() && reg.Has<Door>(tile.occupant)) {
                door = reg.Get<Door>(tile.occupant);
                return;
            }
        }
    });

    return door;
}

Tile &GetPlayerTile(World &world) {
    Entity tileEntity;
    world.Registry().ForEach<Entity, Tile>([&](Entity e, const Tile &tile) {
        if (tile.HasOccupant() && world.Registry().Has<Player>(tile.occupant)) {
            tileEntity = e;
        }
    });

    return world.Registry().Get<Tile>(tileEntity).value().get();
}

OptionalRef<Tile> GetTile(World &world, const Vector2i position) {
    OptionalRef<Tile> tile = std::nullopt;
    world.Registry().ForEach<Tile>([&](Tile &t) {
        if (t.position != position) {
            return;
        }

        tile = t;
    });

    return tile;
}

bool IsTileEmpty(World &world, const Vector2i position) {
    if (!GetTile(world, position)) {
        return false;
    }

    if (GetTile(world, position)->get().HasOccupant() || !IsPassable(GetTile(world, position)->get().type)) {
        return false;
    }

    return true;
}

void UpdatePlayer(World &world) {
    Registry &reg  = world.Registry();
    auto      time = world.Resource<Time::TimeState>();

    auto       chars   = world.Resource<GameState>().completedCharacters;
    const bool endgame = chars["mike"] && chars["dilto"] && chars["samson"] && chars["jack"] && chars["chris"] && chars["maggie"];

    reg.ForEach<Entity, Transform, Player>([&](Entity e, Transform &trans, Player &player) {
        Vector2i movement = {};
        auto &   input    = world.Resource<InputState>();

        const auto maybeDoor = GetNearbyDoor(world, trans);
        if (input.IsKeyPressed(Key::E) && world.Resource<Dialogue>().IsFinished() && maybeDoor) {
            auto &[mapPath] = maybeDoor.value().get();
            input.pressedKeys.erase(Key::E);
            if (mapPath != "assets/5.txt") {
                LoadMap(world, mapPath, mapPath == "assets/map.txt");
                return;
            }
            if (endgame) {
                LoadMap(world, mapPath, false);
                return;
            }
        }

        auto maybeInteractable = GetNearbyInteractable(world, trans);
        if (input.IsKeyPressed(Key::E) && world.Resource<Dialogue>().IsFinished() && maybeInteractable) {
            auto &[entity, interactable] = maybeInteractable.value();

            if (!interactable.get().locked) {
                world.Resource<Dialogue>().messages       = interactable.get().dialogue[interactable.get().currentDialogue].messages;
                world.Resource<Dialogue>().currentMessage = 0;

                if (interactable.get().isItem) {
                    world.Resource<GameState>().items[interactable.get().name] = false;
                    reg.Destroy(entity);
                }
            } else {
                world.Resource<Dialogue>().messages       = {Message{.title = "Locked.", .text = ""}};
                world.Resource<Dialogue>().currentMessage = 0;
            }
        }

        if (input.IsKeyDown(Key::D) || input.IsKeyDown(Key::Right)) {
            movement.x = 1;
            movement.y = 0;
        }

        if (input.IsKeyDown(Key::A) || input.IsKeyDown(Key::Left)) {
            movement.x = -1;
            movement.y = 0;
        }

        if (input.IsKeyDown(Key::W) || input.IsKeyDown(Key::Up)) {
            movement.y = 1;
            movement.x = 0;
        }

        if (input.IsKeyDown(Key::S) || input.IsKeyDown(Key::Down)) {
            movement.y = -1;
            movement.x = 0;
        }

        const Vector2i playerTilePos = GetPlayerTile(world).position;
        if (!player.isMoving && player.canMove && IsTileEmpty(world, playerTilePos + movement)) {
            player.prevPos = GetPlayerTile(world).position;
            if (player.inOverworld) {
                world.Resource<PlayerInfo>().overworldPrevPos = player.prevPos;
            }

            GetPlayerTile(world).occupant                            = {FLK_INVALID, 0};
            GetTile(world, playerTilePos + movement)->get().occupant = e;

            if (player.inOverworld) {
                world.Resource<PlayerInfo>().overworldPos = GetPlayerTile(world).position;
            }
        }

        const Vector2f playerPos = GetPlayerTile(world).position;
        const Vector2f actualPos = {trans.position.x, trans.position.y};

        if ((playerPos - actualPos).Magnitude() > s_PlayerSpeed * time.deltaTime) {
            player.isMoving = true;
        } else {
            player.isMoving  = false;
            trans.position   = Vector3f{playerPos};
            trans.position.z = -2.0F;
        }

        if (player.isMoving) {
            const Vector3f dir = (Vector3f{playerPos} - Vector3f{actualPos}).Normalized();
            trans.position     += dir * s_PlayerSpeed * time.deltaTime;
        }

        bool offset = false;
        reg.All<Box>().ForEach<Entity>([&](Entity e) {
            offset = !offset;
        });

        if (offset) {
            world.Resource<Camera>().transform.position = Vector3f(trans.position.x, trans.position.y + 1.0F, -10);
        } else {
            world.Resource<Camera>().transform.position = Vector3f(trans.position.x, trans.position.y, -10);
        }
    });
}
