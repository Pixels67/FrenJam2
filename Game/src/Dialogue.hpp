#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct Dialogue;

struct Message {
    std::string              title = "Title";
    std::string              text  = "Text";
    std::string              imagePath;
    std::vector<Dialogue>    choices;
    std::vector<std::string> events;
};

FLK_ARCHIVE(Message, title, text, imagePath, choices, events)

struct Dialogue {
    std::vector<Message> messages;
    u32                  currentMessage = 0;

    bool IsFinished() const {
        return currentMessage >= messages.size();
    }
};

FLK_ARCHIVE(Dialogue, messages)

#endif //DIALOGUE_HPP
