#ifndef DIALOGUEUI_HPP
#define DIALOGUEUI_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Using.hpp"

struct DialogueText {
};

struct DialogueTitle {
};

struct DialogueImage {
};

struct DialogueBox {
};

FLK_ARCHIVE_TAG(DialogueText)
FLK_ARCHIVE_TAG(DialogueTitle)
FLK_ARCHIVE_TAG(DialogueImage)
FLK_ARCHIVE_TAG(DialogueBox)

inline void ShowDialogue(World &world) {
    world.Registry().ForEach<Player>([&](Player &player) { player.canMove = false; });

    world.Registry().All<DialogueText>().ForEach<Entity>([&](const Entity e) {
        world.Registry().SetEnabled<Text>(e, true);
    });

    world.Registry().All<DialogueTitle>().ForEach<Entity>([&](const Entity e) {
        world.Registry().SetEnabled<Text>(e, true);
    });

    world.Registry().All<DialogueBox>().ForEach<Entity>([&](const Entity e) {
        world.Registry().SetEnabled<Box>(e, true);
    });
}

inline void HideDialogue(World &world) {
    world.Registry().ForEach<Player>([&](Player &player) { player.canMove = true; });

    world.Registry().All<DialogueText>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Disable<Text>(e);
    });

    world.Registry().All<DialogueTitle>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Disable<Text>(e);
    });

    world.Registry().All<DialogueBox>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Disable<Box>(e);
    });
}

inline void UpdateDialogueUi(World &world) {
    auto &[messages, currentMessage] = world.Resource<Dialogue>();

    const auto input = world.Resource<InputState>();
    if (input.IsKeyPressed(Key::Space) && currentMessage < messages.size()) {
        currentMessage++;
    }

    std::string content;
    std::string title;
    if (currentMessage < messages.size()) {
        content = messages[currentMessage].text;
        title   = messages[currentMessage].title;

        ShowDialogue(world);
    } else {
        HideDialogue(world);
    }

    world.Registry().All<DialogueText>().ForEach<Text>([&](Text &text) {
        text.content = content;
    });

    world.Registry().All<DialogueTitle>().ForEach<Text>([&](Text &text) {
        text.content = title;
    });
}

#endif //DIALOGUEUI_HPP
