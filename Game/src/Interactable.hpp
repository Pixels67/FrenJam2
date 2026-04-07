#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Using.hpp"

struct Interactable {
    Dialogue dialogue;
    bool     destroyOnInteract = false;
};

FLK_ARCHIVE(Interactable, dialogue, destroyOnInteract)

#endif //INTERACTABLE_HPP
