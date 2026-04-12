#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "Flock.hpp"
#include "GameState.hpp"
#include "Item.hpp"
#include "Using.hpp"

inline void UnlockItem(World &world, const std::string &itemName) {
    if (itemName.empty()) {
        return;
    }

    world.Resource<GameState>().itemsLocked[itemName] = false;
    world.Registry().ForEach<Interactable>([&](Interactable &interactable) {
        if (!interactable.destroyOnInteract || interactable.name != itemName) {
            return;
        }

        interactable.locked = false;
    });
}

inline void AddItem(World &world, const std::string &itemName, const std::string &imagePath) {
    world.Resource<Inventory>().items.push_back(Item{.name = itemName, .imagePath = imagePath});
}

inline void RemoveItem(World &world, const std::string &itemName) {
    const auto items = world.Resource<Inventory>().items;
    world.Resource<Inventory>().items.clear();
    for (const auto &i: items) {
        if (i.name == itemName) {
            continue;
        }

        world.Resource<Inventory>().items.push_back(i);
    }
}

inline void AdvanceCharacter(World &world, const std::string &name) {
    if (name.empty()) {
        return;
    }

    world.Resource<GameState>().characterIndices[name]++;

    world.Registry().ForEach<Interactable>([&](Interactable &interactable) {
        if (interactable.destroyOnInteract || interactable.name != name) {
            return;
        }

        interactable.currentDialogue++;
    });
}

inline void SetEvents(World &world) {
    auto &ereg = world.Resource<Event::EventRegistry>();
    auto &reg  = world.Registry();

    // Items
    ereg.Add("u_maxwell", [&] {
        UnlockItem(world, "maxwell");
    });
    ereg.Add("u_grill", [&] {
        UnlockItem(world, "grill");
    });
    ereg.Add("u_statuette", [&] {
        UnlockItem(world, "statuette");
    });
    ereg.Add("u_cd", [&] {
        UnlockItem(world, "cd");
    });
    ereg.Add("u_pillow", [&] {
        UnlockItem(world, "pillow");
    });
    ereg.Add("u_coin", [&] {
        UnlockItem(world, "coin");
    });
    ereg.Add("u_toothbrush", [&] {
        UnlockItem(world, "toothbrush");
    });

    ereg.Add("a_maxwell", [&] {
        AddItem(world, "Maxwell", "");
        ereg.Invoke("a_maggie");
    });
    ereg.Add("a_grill", [&] {
        AddItem(world, "Grill", "");
        ereg.Invoke("a_dilto");
    });
    ereg.Add("a_statuette", [&] {
        AddItem(world, "Statuette", "");
        ereg.Invoke("a_mike");
    });
    ereg.Add("a_verse", [&] {
        AddItem(world, "Bible Verse", "");
        ereg.Invoke("a_samson");
    });
    ereg.Add("a_cd", [&] {
        AddItem(world, "CD", "");
        ereg.Invoke("a_jack");
    });
    ereg.Add("a_pillow", [&] {
        AddItem(world, "Saitama Body Pillow", "");
        ereg.Invoke("a_mike");
    });
    ereg.Add("a_coin", [&] {
        AddItem(world, "Bald Eagle Coin", "");
        ereg.Invoke("a_chris");
    });
    ereg.Add("a_toothbrush", [&] {
        AddItem(world, "Electric Toothbrush", "");
        ereg.Invoke("a_mike");
    });

    ereg.Add("r_maxwell", [&] {
        RemoveItem(world, "Maxwell");
    });
    ereg.Add("r_grill", [&] {
        RemoveItem(world, "Grill");
    });
    ereg.Add("r_statuette", [&] {
        RemoveItem(world, "Statuette");
    });
    ereg.Add("r_verse", [&] {
        RemoveItem(world, "Bible Verse");
    });
    ereg.Add("r_cd", [&] {
        RemoveItem(world, "CD");
        ereg.Invoke("a_jack2");
    });
    ereg.Add("r_pillow", [&] {
        RemoveItem(world, "Saitama Body Pillow");
    });
    ereg.Add("r_coin", [&] {
        RemoveItem(world, "Bald Eagle Coin");
    });
    ereg.Add("r_toothbrush", [&] {
        RemoveItem(world, "Electric Toothbrush");
    });


    // Characters
    ereg.Add("a_mike", [&] {
        AdvanceCharacter(world, "mike");
    });
    ereg.Add("a_samson", [&] {
        AdvanceCharacter(world, "samson");
    });
    ereg.Add("a_chris", [&] {
        AdvanceCharacter(world, "chris");
    });
    ereg.Add("a_dilto", [&] {
        AdvanceCharacter(world, "dilto");
    });
    ereg.Add("a_maggie", [&] {
        AdvanceCharacter(world, "maggie");
    });
    ereg.Add("a_jack", [&] {
        AdvanceCharacter(world, "jack");
    });
    ereg.Add("a_jack2", [&] {
        AdvanceCharacter(world, "jack2");
    });
}

#endif //EVENTS_HPP
