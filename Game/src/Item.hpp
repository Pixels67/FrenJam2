#ifndef ITEM_HPP
#define ITEM_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct Item {
    std::string name;
    std::string imagePath;
};

FLK_ARCHIVE(Item, name, imagePath)

struct Inventory {
    std::vector<Item> items;
};

FLK_ARCHIVE(Inventory, items)

#endif //ITEM_HPP