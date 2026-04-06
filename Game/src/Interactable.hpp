#ifndef INTERACTABLE_HPP
#define INTERACTABLE_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Using.hpp"

struct Interactable {
    Dialogue dialogue;
    bool     destroyOnInteract = false;
};

inline auto Reflect(Interactable &interactable) {
    return Reflectable{
        "Interactable",
        std::make_tuple(
            Field{"dialogue", &interactable.dialogue},
            Field{"destroyOnInteract", &interactable.destroyOnInteract}
        )
    };
}

#endif //INTERACTABLE_HPP
