#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct GameState {
    std::unordered_map<std::string, u32>  characterIndices;
    std::unordered_map<std::string, bool> itemsLocked;
    std::unordered_map<std::string, bool> items;
};

FLK_ARCHIVE(GameState, characterIndices, itemsLocked)

inline void ApplyGameState(World &world, GameState &state) {
    world.Registry().ForEach<Interactable>([&](Interactable &interactable) {
        if (interactable.destroyOnInteract || interactable.name == "") {
            return;
        }

        interactable.currentDialogue = state.characterIndices[interactable.name];
    });

    world.Registry().ForEach<Entity, Interactable>([&](Entity e, Interactable &interactable) {
        if (!interactable.destroyOnInteract) {
            return;
        }

        interactable.locked = state.itemsLocked[interactable.name];
        if (!state.items[interactable.name]) {
            world.Registry().Destroy(e);
        }
    });
}

#endif //GAMESTATE_HPP
