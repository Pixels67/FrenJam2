#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct Message {
    std::string              title = "Title";
    std::string              text  = "Text";
    std::string              imagePath;
    std::vector<Message>     choices;
    std::vector<std::string> events;
};

inline auto Reflect(Message &msg) {
    return Reflectable{
        "Message",
        std::make_tuple(
            Field{"title", &msg.title},
            Field{"text", &msg.text},
            Field{"image", &msg.imagePath},
            Field{"choices", &msg.choices},
            Field{"events", &msg.events}
        )
    };
}

struct Dialogue {
    std::vector<Message> messages;
    u32                  currentMessage = 0;
};

inline auto Reflect(Dialogue &dialogue) {
    return Reflectable{
        "Dialogue",
        std::make_tuple(
            Field{"messages", &dialogue.messages},
            Field{"currentMessage", &dialogue.currentMessage}
        )
    };
}

#endif //DIALOGUE_HPP
