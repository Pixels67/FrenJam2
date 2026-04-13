#ifndef FLK_TILE_HPP
#define FLK_TILE_HPP

#include "Flock.hpp"
#include "Player.hpp"
#include "Fren.hpp"
#include "Using.hpp"

enum TileType {
    Ground,
    Trail,
    Sand,
    Trash,
    Water,
    Wall,
};

inline bool IsPassable(const TileType type) {
    switch (type) {
        case Ground: return true;
        case Trail: return true;
        case Sand: return true;
        case Trash: return false;
        case Water: return false;
        case Wall: return false;
    }

    FLK_ASSERT(false);
}

inline std::string GetTileSprite(const TileType type) {
    switch (type) {
        case Ground: return "assets/ground.png";
        case Trail: return "assets/trail.png";
        case Sand: return "assets/sand.png";
        case Trash: return "assets/trash.png";
        case Water: return "assets/water.png";
        case Wall: return "assets/wall.png";
    }

    FLK_ASSERT(false);
}

struct Tile {
    Vector2i position = {};
    TileType type     = Ground;
    Entity   occupant = {};

    [[nodiscard]] bool HasOccupant() const {
        return occupant.id != FLK_INVALID;
    }
};

FLK_ARCHIVE(Tile, position, type, occupant)

inline void UpdateTiles(World &world) {
    Registry &reg = world.Registry();
    reg.ForEach<Transform, SpriteRenderer, Tile>([&](Transform &trans, SpriteRenderer &renderer, Tile &tile) {
        trans.position      = Vector3i{tile.position.x, tile.position.y, 0};
        renderer.spritePath = GetTileSprite(tile.type);

        if (!reg.IsAlive(tile.occupant)) {
            tile.occupant = {};
        }

        if (tile.HasOccupant() && reg.Has<Transform>(tile.occupant) && !reg.Has<Player>(tile.occupant) && !reg.Has<Fren>(tile.occupant)) {
            reg.Get<Transform>(tile.occupant)->get()            = trans;
            reg.Get<Transform>(tile.occupant)->get().position.z = trans.position.z - 1;
        }
    });
}

#endif //FLK_TILE_HPP
