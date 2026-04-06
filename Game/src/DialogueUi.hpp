#ifndef DIALOGUEUI_HPP
#define DIALOGUEUI_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Reflect.hpp"
#include "Using.hpp"

struct DialogueText {
};

struct DialogueTitle {
};

struct DialogueImage {
};

struct DialogueBox {
};

inline auto Reflect(DialogueText &) {
    return Reflectable{
        "DialogueText",
        std::make_tuple()
    };
}

inline auto Reflect(DialogueTitle &) {
    return Reflectable{
        "DialogueTitle",
        std::make_tuple()
    };
}

inline auto Reflect(DialogueImage &) {
    return Reflectable{
        "DialogueImage",
        std::make_tuple()
    };
}

inline auto Reflect(DialogueBox &) {
    return Reflectable{
        "DialogueBox",
        std::make_tuple()
    };
}

inline void ShowDialogue(World &world) {
    world.GetRegistry().Iter<Player>([&](Player &player) { player.canMove = false; });

    world.GetRegistry().Query<DialogueText>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Text>(e, true);
    });

    world.GetRegistry().Query<DialogueTitle>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Text>(e, true);
    });

    world.GetRegistry().Query<DialogueBox>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Box>(e, true);
    });
}

inline void HideDialogue(World &world) {
    world.GetRegistry().Iter<Player>([&](Player &player) { player.canMove = true; });

    world.GetRegistry().Query<DialogueText>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Text>(e, false);
    });

    world.GetRegistry().Query<DialogueTitle>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Text>(e, false);
    });

    world.GetRegistry().Query<DialogueBox>().Iter<Entity>([&](const Entity e) {
        world.GetRegistry().SetComponentEnabled<Box>(e, false);
    });
}

inline void UpdateDialogueUi(World &world) {
    auto &[messages, currentMessage] = world.GetResource<Dialogue>();

    const auto input = world.GetResource<InputState>();
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

    world.GetRegistry().Query<DialogueText>().Iter<Text>([&](Text &text) {
        text.content = content;
    });

    world.GetRegistry().Query<DialogueTitle>().Iter<Text>([&](Text &text) {
        text.content = title;
    });
}

#endif //DIALOGUEUI_HPP
