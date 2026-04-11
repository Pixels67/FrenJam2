#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Flock.hpp"
#include "Interactable.hpp"
#include "Using.hpp"

struct PlayerInfo {
    Vector2i overworldPos     = {};
    Vector2i overworldPrevPos = {};
};

struct Player {
    bool     canMove     = true;
    bool     isMoving    = false;
    bool     inOverworld = true;
    Vector2i prevPos     = {};
};

FLK_ARCHIVE(Player, canMove)

std::optional<std::tuple<Entity, Ref<Interactable> > > GetNearbyInteractable(World &world, const Transform &transform);

void UpdatePlayer(World &world);

#endif //PLAYER_HPP
