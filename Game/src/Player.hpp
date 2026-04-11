#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Flock.hpp"
#include "Interactable.hpp"
#include "Using.hpp"

struct Player {
    bool     canMove  = true;
    bool     isMoving = false;
    Vector2i prevPos  = {};
};

FLK_ARCHIVE(Player, canMove)

std::optional<std::tuple<Entity, Ref<Interactable> > > GetNearbyInteractable(World &world, const Transform &transform);

void UpdatePlayer(World &world);

#endif //PLAYER_HPP
