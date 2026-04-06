#ifndef FLK_TILE_HPP
#define FLK_TILE_HPP

#include "Flock.hpp"
#include "Using.hpp"

enum TileType {
    Ground,
    Wall,
};

inline bool IsPassable(const TileType type) {
    switch (type) {
        case Ground: return true;
        case Wall: return false;
    }

    FLK_ASSERT(false);
}

inline std::string GetTileSprite(const TileType type) {
    switch (type) {
        case Ground: return "assets/Checkerboard.png";
        case Wall: return "";
    }

    FLK_ASSERT(false);
}

struct Tile {
    Vector2i position = {};
    TileType type     = Ground;
    Entity   occupant = {~0u, 0};

    bool HasOccupant() const {
        return occupant.id != ~0u;
    }
};

inline auto Reflect(Tile &tile) {
    return Reflectable{
        "Tile",
        std::make_tuple(
            Field{"position", &tile.position},
            Field{"type", &tile.type},
            Field{"occupant", &tile.occupant}
        )
    };
}

inline void UpdateTiles(World &world) {
    Registry &reg = world.GetRegistry();
    reg.Iter<Transform, SpriteRenderer, Tile>([&](Transform &trans, SpriteRenderer &renderer, Tile &tile) {
        trans.position      = Vector3i{tile.position.x, tile.position.y, 0};
        renderer.spritePath = GetTileSprite(tile.type);

        if (!reg.IsAlive(tile.occupant)) {
            tile.occupant = {~0u, 0};
        }

        if (tile.HasOccupant() && reg.HasComponent<Transform>(tile.occupant)) {
            reg.GetComponent<Transform>(tile.occupant)->get()            = trans;
            reg.GetComponent<Transform>(tile.occupant)->get().position.z = trans.position.z - 1;
        }
    });
}

#endif //FLK_TILE_HPP
