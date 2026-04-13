#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct GameState {
    std::unordered_map<std::string, u32>         characterIndices;
    std::unordered_map<std::string, std::string> characterImagePaths;
    std::unordered_map<std::string, bool>        completedCharacters;
    std::unordered_map<std::string, bool>        itemsLocked;
    std::unordered_map<std::string, bool>        items;
};

FLK_ARCHIVE(GameState, characterIndices, characterImagePaths, completedCharacters, itemsLocked, items)

inline void ApplyGameState(World &world, GameState &state) {
    world.Registry().ForEach<SpriteRenderer, Interactable>([&](SpriteRenderer &renderer, Interactable &interactable) {
        if (interactable.isItem || interactable.name.empty()) {
            return;
        }

        renderer.spritePath          = state.characterImagePaths[interactable.name];
        interactable.currentDialogue = state.characterIndices[interactable.name];
        interactable.completed       = state.completedCharacters[interactable.name];

        if (interactable.name == "jack") {
            interactable.locked = state.itemsLocked["jack"];
        }
    });

    world.Registry().ForEach<Entity, Interactable>([&](Entity e, Interactable &interactable) {
        if (!interactable.isItem) {
            return;
        }

        interactable.locked = state.itemsLocked[interactable.name];
        if (!state.items[interactable.name]) {
            world.Registry().Destroy(e);
        }
    });
}

#endif //GAMESTATE_HPP
