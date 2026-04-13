#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Using.hpp"

struct Interactable {
    std::string           name;
    std::vector<Dialogue> dialogue;
    u32                   currentDialogue = 0;
    bool                  isItem          = false;
    bool                  locked          = true;
    bool                  completed       = false;
};

FLK_ARCHIVE(Interactable, name, dialogue, isItem)

#endif //INTERACTABLE_HPP
