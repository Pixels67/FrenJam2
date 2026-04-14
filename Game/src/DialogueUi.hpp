#ifndef DIALOGUEUI_HPP
#define DIALOGUEUI_HPP

#include <thread>

#include "Dialogue.hpp"
#include "Flock.hpp"
#include "Player.hpp"
#include "Using.hpp"

struct DialogueText {
    std::string content;
    f32         currentChar = 0.0F;
    bool        changedChar = false;
    i32         prevIdx     = 0;
};

struct DialogueTitle {
};

struct DialogueImage {
};

struct DialogueBox {
};

struct DialogueYesButton {
};

struct DialogueNoButton {
};

FLK_ARCHIVE(DialogueText, content)
FLK_ARCHIVE_TAG(DialogueTitle)
FLK_ARCHIVE_TAG(DialogueImage)
FLK_ARCHIVE_TAG(DialogueBox)
FLK_ARCHIVE_TAG(DialogueYesButton)
FLK_ARCHIVE_TAG(DialogueNoButton)

inline void ShowDialogue(World &world) {
    world.Registry().ForEach<Player>([&](Player &player) { player.canMove = false; });

    world.Registry().All<DialogueText>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Enable<Text>(e);
    });

    world.Registry().All<DialogueTitle>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Enable<Text>(e);
    });

    world.Registry().All<DialogueBox>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Enable<Box>(e);
    });
}

inline void ShowButtons(World &world) {
    world.Registry().All<DialogueYesButton, Text>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Enable<Button>(e);
        world.Registry().Enable<Text>(e);
    });

    world.Registry().All<DialogueNoButton, Text>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Enable<Button>(e);
        world.Registry().Enable<Text>(e);
    });
}

inline void HideButtons(World &world) {
    world.Registry().All<DialogueYesButton, Text>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Disable<Button>(e);
        world.Registry().Disable<Text>(e);
    });

    world.Registry().All<DialogueNoButton, Text>().ForEach<Entity>([&](const Entity e) {
        world.Registry().Disable<Button>(e);
        world.Registry().Disable<Text>(e);
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
    if (input.IsKeyPressed(Key::Space) && currentMessage < messages.size() && messages[currentMessage].choices.empty()) {
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

        if (!messages[currentMessage].choices.empty()) {
            ShowButtons(world);
        } else {
            HideButtons(world);
        }

        ShowDialogue(world);
    } else {
        HideDialogue(world);
        HideButtons(world);
    }

    world.Registry().ForEach<Text, DialogueText>([&](Text &text, DialogueText &dText) {
        if (content.size() > 2 && content.substr(0, 2) == "/s") {
            if (content.substr(2) != dText.content) {
                dText.content     = content.substr(2);
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
            text.content += dText.content[0];
        }

        const u32 diff = static_cast<u32>(dText.currentChar) - dText.prevIdx;
        if (diff != 0) {
            for (i32 i = diff - 1; i >= 0; i--) {
                if (static_cast<u32>(dText.currentChar) - i > dText.content.size()) {
                    continue;
                }

                if (static_cast<u32>(dText.currentChar) % 4 == 0 && title != "Locked.") {
                    world.Resource<AudioHandler>().PlaySfx(world.Registry(), title);
                }

                text.content += dText.content[static_cast<u32>(dText.currentChar) - i];
            }
        }

        dText.prevIdx     = static_cast<u32>(dText.currentChar);
        dText.currentChar += world.Resource<Time::TimeState>().deltaTime * 50.0F;
    });

    world.Registry().All<DialogueTitle>().ForEach<Text>([&](Text &text) {
        text.content = title;
    });
}

#endif //DIALOGUEUI_HPP
