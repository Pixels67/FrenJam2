#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "Fade.hpp"
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
        if (!interactable.isItem || interactable.name != itemName) {
            return;
        }

        interactable.locked = false;
    });
}

inline void AddItem(World &world, const std::string &itemName, const std::string &imagePath) {
    world.Resource<AudioHandler>().PlaySfx(world.Registry(), "item");
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
        if (interactable.isItem || interactable.name != name) {
            return;
        }

        interactable.currentDialogue++;
    });
}

inline void BaldifyCharacter(World &world, const std::string &name) {
    if (name.empty()) {
        return;
    }

    if (name != "girlfren" && name != "joel") {
        world.Resource<AudioHandler>().PlaySfx(world.Registry(), "bald");
    }

    world.Registry().ForEach<Interactable, SpriteRenderer>([&](Interactable &interactable, SpriteRenderer &renderer) {
        if (interactable.isItem || interactable.name != name) {
            return;
        }

        std::string imageName                                 = renderer.spritePath;
        imageName                                             = imageName.substr(0, imageName.size() - 4);
        imageName                                             += "_b";
        imageName                                             += ".png";
        renderer.spritePath                                   = imageName;
        world.Resource<GameState>().characterImagePaths[name] = renderer.spritePath;

        interactable.completed                                = true;
        world.Resource<GameState>().completedCharacters[name] = true;
    });
}

inline void BaldifyPlayer(World &world) {
    world.Registry().All<Player>().ForEach<SpriteRenderer>([&](SpriteRenderer &renderer) {
        std::string imageName = renderer.spritePath;
        imageName             = imageName.substr(0, imageName.size() - 4);
        imageName             += "_b";
        imageName             += ".png";
        renderer.spritePath   = imageName;
    });
}

inline void SetEvents(World &world) {
    auto &ereg = world.Resource<Event::EventRegistry>();
    auto &reg  = world.Registry();

    ereg.Add("start", [&] {
        world.Resource<AudioHandler>().StopMusic(reg);
        world.Resource<AudioHandler>().PlaySfx(world.Registry(), "select");

        world.Registry().All<Gui::Image>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Gui::Image>(e);
        });

        world.Registry().All<Button>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Button>(e);
        });

        world.Registry().All<Text>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Text>(e);
        });

        Entity box = world.Registry().Create(
            RectTransform{
                {{0, 520}, {1280, 200}}
            },
            Box{
                .color = Color4u8::Black()
            },
            DialogueBox{}
        );

        world.Registry().Create(
            RectTransform{
                {{0, 0}, {1280, 90}}
            },
            Box{
                .color = Color4u8::Black()
            }
        );

        Entity title = world.Registry().Create(
            RectTransform{
                {{10, 530}, {1270, 190}}
            },
            Text{
                .content  = "Title",
                .fontPath = "assets/font.ttf",
                .color    = {40, 120, 140, 255}
            },
            DialogueTitle{}
        );

        Entity text = world.Registry().Create(
            RectTransform{
                {{10, 560}, {1270, 190}}
            },
            Text{
                .content  = "Content\nMore content\nEven more content",
                .fontPath = "assets/font.ttf"
            },
            DialogueText{}
        );

        Entity yesButton = world.Registry().Create(
            RectTransform{
                {{660, 330}, {180, 60}}
            },
            Button{
                .hoverTint      = {20, 40, 255, 40},
                .onReleaseEvent = "yes",
            },
            Text{
                .content             = "Yes",
                .fontSize            = 40,
                .fontPath            = "assets/font.ttf",
                .horizontalAlignment = Center,
                .verticalAlignment   = Middle,
            },
            DialogueYesButton{}
        );

        Entity noButton = world.Registry().Create(
            RectTransform{
                {{440, 330}, {180, 60}}
            },
            Button{
                .hoverTint      = {255, 40, 20, 40},
                .onReleaseEvent = "no",
            },
            Text{
                .content             = "No",
                .fontSize            = 40,
                .fontPath            = "assets/font.ttf",
                .horizontalAlignment = Center,
                .verticalAlignment   = Middle,
            },
            DialogueNoButton{}
        );

        world.Registry().Disable<Button>(noButton);
        world.Registry().Disable<Button>(yesButton);
        world.Registry().Disable<Text>(noButton);
        world.Registry().Disable<Text>(yesButton);
        world.Registry().Disable<Text>(text);
        world.Registry().Disable<Text>(title);
        world.Registry().Disable<Box>(box);

        LoadMap(world, "assets/map.txt", true);
    });

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
    ereg.Add("u_card", [&] {
        UnlockItem(world, "card");
    });

    ereg.Add("a_maxwell", [&] {
        AddItem(world, "Maxwell", "assets/sprites/maxwell.png");
        ereg.Invoke("a_maggie");
    });
    ereg.Add("a_grill", [&] {
        AddItem(world, "Grill", "assets/sprites/grill.png");
        ereg.Invoke("a_dilto");
    });
    ereg.Add("a_statuette", [&] {
        AddItem(world, "Statuette", "assets/sprites/statuette.png");
        ereg.Invoke("a_mike");
    });
    ereg.Add("a_verse", [&] {
        AddItem(world, "Bible Verse", "assets/sprites/verse.png");
        ereg.Invoke("a_samson");
    });
    ereg.Add("a_cd", [&] {
        AddItem(world, "CD", "assets/sprites/cd_item.png");
        ereg.Invoke("a_jack");
    });
    ereg.Add("a_pillow", [&] {
        AddItem(world, "Saitama Body Pillow", "assets/sprites/pillow.png");
        ereg.Invoke("a_mike");
    });
    ereg.Add("a_coin", [&] {
        AddItem(world, "Bald Eagle Coin", "assets/sprites/coin.png");
        ereg.Invoke("a_chris");
    });
    ereg.Add("a_toothbrush", [&] {
        AddItem(world, "Electric Toothbrush", "assets/sprites/toothbrush.png");
        ereg.Invoke("a_mike");
    });
    ereg.Add("a_card", [&] {
        AddItem(world, "Vinerizon Card", "assets/sprites/card.png");
        ereg.Invoke("a_vinny");
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
    ereg.Add("r_card", [&] {
        RemoveItem(world, "Vinerizon Card");
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
    ereg.Add("a_vinny", [&] {
        AdvanceCharacter(world, "vinny");
    });

    ereg.Add("b_mike", [&] {
        BaldifyCharacter(world, "mike");
    });
    ereg.Add("b_samson", [&] {
        BaldifyCharacter(world, "samson");
    });
    ereg.Add("b_chris", [&] {
        BaldifyCharacter(world, "chris");
    });
    ereg.Add("b_dilto", [&] {
        BaldifyCharacter(world, "dilto");
    });
    ereg.Add("b_maggie", [&] {
        BaldifyCharacter(world, "maggie");
    });
    ereg.Add("b_jack", [&] {
        BaldifyCharacter(world, "jack");
    });
    ereg.Add("b_vinny", [&] {
        BaldifyCharacter(world, "vinny");
    });

    ereg.Add("u_jack", [&] {
        world.Resource<GameState>().itemsLocked["jack"] = false;
        world.Registry().ForEach<Interactable>([&](Interactable &interactable) {
            if (interactable.name != "jack") {
                return;
            }

            interactable.locked = false;
        });
    });

    ereg.Add("reveal", [&] {
        BaldifyCharacter(world, "girlfren");
    });

    ereg.Add("yes", [&] {
        auto &dialogue = world.Resource<Dialogue>();
        dialogue       = dialogue.messages[dialogue.currentMessage].choices[1];
    });

    ereg.Add("no", [&] {
        auto &dialogue = world.Resource<Dialogue>();
        dialogue       = dialogue.messages[dialogue.currentMessage].choices[0];
    });

    ereg.Add("steve", [&] {
        world.Resource<Dialogue>().lockTime = 12.0F;
        world.Resource<AudioHandler>().PlaySfx(reg, "steve");
        world.Resource<AudioHandler>().StopMusic(reg);
        world.Resource<AudioHandler>().PlayMusic("assets/music/scsa-loop.oga", true, 12.0F);

        world.Registry().Create(RectTransform{{{}, {1280, 720}}}, Box{.color = Color4u8::White()}, Fade{});
        reg.ForEach<Entity, Box>([&](Entity e, Box &box) {
            if (reg.Has<DialogueBox>(e) || reg.Has<Fade>(e)) {
                return;
            }

            reg.Destroy(e);
        });
        reg.Create(
            Transform{
                .position = {4.0F, -3.0F, -0.5F},
                .scale    = Vector3f::One() * 3.0F,
            },
            SpriteRenderer{
                .spritePath = "assets/sprites/steve.png"
            }
        );
    });

    ereg.Add("beam", [&] {
        world.Resource<Dialogue>().lockTime = 5.0F;
        world.Registry().Create(RectTransform{{{}, {1280, 720}}}, Box{.color = Color4u8::White()}, Fade{.time = 5.0F});
    });

    ereg.Add("radio", [&] {
        if (world.Resource<AudioHandler>().currentMusic == "assets/music/house.oga") {
            world.Resource<AudioHandler>().PlayMusic("assets/music/joel.oga");
        }

        if (world.Resource<AudioHandler>().currentMusic == "assets/music/3.oga") {
            world.Resource<AudioHandler>().PlayMusic("assets/music/vargbonezone.oga");
        }
    });

    ereg.Add("dookie", [&] {
        world.Resource<AudioHandler>().PlayMusic("assets/music/musicthatmakesyougodookie-loop.oga");
    });

    ereg.Add("goodend", [&] {
        world.Resource<AudioHandler>().PlayMusic("assets/music/goodend.oga");
        BaldifyCharacter(world, "girlfren");
        BaldifyPlayer(world);
        reg.ForEach<SpriteRenderer, Entity>([&](const SpriteRenderer &renderer, const Entity e) {
            if (renderer.spritePath == "assets/sprites/steve.png") {
                world.Registry().Destroy(e);
            }
        });
    });

    ereg.Add("end", [&] {
        world.Registry().All<Gui::Image>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Gui::Image>(e);
        });

        world.Registry().All<Button>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Button>(e);
        });

        world.Registry().All<Text>().ForEach<Entity>([&](Entity e) {
            world.Registry().Disable<Text>(e);
        });

        bool goodend = false;
        world.Registry().All<Player>().ForEach<SpriteRenderer>([&](const SpriteRenderer &renderer) {
            goodend = renderer.spritePath == "assets/sprites/joel_b.png";
        });

        if (!goodend) {
            world.Resource<AudioHandler>().PlayMusic("assets/music/bad-end.oga");
        } else {
            world.Resource<AudioHandler>().PlayMusic("assets/music/credits.oga");
        }

        world.Registry().Create(RectTransform{{{0, 0}, {1280, 720}}}, Box{.color = Color4u8::Black()});
        world.Registry().Create(
            RectTransform{{{240, 40}, {800, 360}}},
            Text{
                .content             = R"(
Game made by:


Programming - Pixels

Art - Major (@MsMajor)

Music & SFX - zephiX

Narrative - Major + zephiX

Art assets from CraftPix and The Spriters Resource were used


Game made for FrenJam 2

Thank you for playing!
)",
                .fontSize            = 20,
                .fontPath            = "assets/font.ttf",
                .horizontalAlignment = Center
            }
        );

        world.Registry().Create(
            RectTransform{{{540, 600}, {200, 50}}},
            Button{.defaultColor = Color4u8::White(), .hoverTint = {0, 0, 0, 40}, .onReleaseEvent = "quit"},
            Text{
                .content             = "Quit",
                .fontSize            = 30,
                .fontPath            = "assets/font.ttf",
                .color               = Color4u8::Black(),
                .horizontalAlignment = Center,
                .verticalAlignment   = Middle
            }
        );
    });

    ereg.Add("quit", [&] {
        world.Resource<AudioHandler>().PlaySfx(world.Registry(), "select");
        world.Resource<Application>().Close();
    });
}

#endif //EVENTS_HPP
