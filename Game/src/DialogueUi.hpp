#ifndef DIALOGUEUI_HPP
#define DIALOGUEUI_HPP

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Using.hpp"

struct DialogueText {
    std::string content;
    f32         currentChar = 0.0F;
    bool        changedChar = false;
};

struct DialogueTitle {
};

struct DialogueImage {
};

struct DialogueBox {
};

FLK_ARCHIVE(DialogueText, content)
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
        for (const auto &event: messages[currentMessage].events) {
            world.Resource<Event::EventRegistry>().Invoke(event);
        }

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

    world.Registry().ForEach<Text, DialogueText>([&](Text &text, DialogueText &dText) {
        if (content.size() > 2 && content.substr(0, 2) == "/s") {
            if (content.substr(3) != dText.content) {
                dText.content     = content.substr(3);
                dText.currentChar = 0.0F;
                text.fontSize     = 10;
            }
        } else {
            if (content != dText.content) {
                dText.content     = content;
                dText.currentChar = 0.0F;
                text.fontSize     = 20;
            }
        }
    });

    world.Registry().ForEach<Text, DialogueText>([&](Text &text, DialogueText &dText) {
        if (dText.currentChar == 0.0F) {
            text.content = "";
            dText.changedChar = true;
        }

        if (static_cast<u32>(dText.currentChar) < dText.content.size() && dText.changedChar) {
            text.content += dText.content[static_cast<u32>(dText.currentChar)];
        }

        u32 oldIdx = static_cast<u32>(dText.currentChar);
        dText.currentChar += world.Resource<Time::TimeState>().deltaTime * 50.0F;

        if (static_cast<u32>(dText.currentChar) != oldIdx) {
            dText.changedChar = true;
        } else {
            dText.changedChar = false;
        }
    });

    world.Registry().All<DialogueTitle>().ForEach<Text>([&](Text &text) {
        text.content = title;
    });
}

#endif //DIALOGUEUI_HPP
