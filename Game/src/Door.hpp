#ifndef DOOR_HPP
#define DOOR_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct Door {
    std::string mapPath = "assets/map.txt";
};

FLK_ARCHIVE(Door, mapPath)

#endif //DOOR_HPP