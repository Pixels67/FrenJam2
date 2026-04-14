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
    Hidden,
    Interior,
    Bones,
    Guy,
    Stone,
    Tree,
    Mountain,
};

inline bool IsPassable(const TileType type) {
    switch (type) {
        case Ground: return true;
        case Trail: return true;
        case Sand: return true;
        case Trash: return false;
        case Water: return false;
        case Wall: return false;
        case Hidden: return false;
        case Interior: return true;
        case Bones: return false;
        case Guy: return false;
        case Stone: return true;
        case Tree: return false;
        case Mountain: return false;
    }

    FLK_ASSERT(false);
}

inline std::string GetTileSprite(const TileType type) {
    switch (type) {
        case Ground: return "assets/sprites/ground.png";
        case Trail: return "assets/sprites/trail.png";
        case Sand: return "assets/sprites/sand.png";
        case Trash: return "assets/sprites/trash.png";
        case Water: return "assets/sprites/water.png";
        case Wall: return "assets/sprites/wall.png";
        case Hidden: return "assets/sprites/ground.png";
        case Interior: return "assets/sprites/interior.png";
        case Bones: return "assets/sprites/bones.png";
        case Guy: return "assets/sprites/guy.png";
        case Stone: return "assets/sprites/stone.png";
        case Tree: return "assets/sprites/tree.png";
        case Mountain: return "assets/sprites/mountain.png";
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
