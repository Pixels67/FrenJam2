#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Using.hpp"

struct Interactable {
    std::string           name;
    std::vector<Dialogue> dialogue;
    u32                   currentDialogue   = 0;
    bool                  destroyOnInteract = false;
    bool                  locked            = true;
};

FLK_ARCHIVE(Interactable, name, dialogue, destroyOnInteract)

#endif //INTERACTABLE_HPP
