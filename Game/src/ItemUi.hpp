#ifndef ITEMUI_HPP
#define ITEMUI_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct ItemUi {
    std::vector<Entity> items;
};

FLK_ARCHIVE(ItemUi, items)

static constexpr Vector2i s_Padding  = {20, 20};
static constexpr Vector2i s_IconSize = {80, 80};

inline void UpdateItemUi(World &world) {
    auto &reg = world.Registry();

    auto &inventory = world.Resource<Inventory>();
    auto &itemUi    = world.Resource<ItemUi>();

    while (itemUi.items.size() < inventory.items.size()) {
        itemUi.items.push_back(reg.Create());
    }

    while (itemUi.items.size() > inventory.items.size()) {
        reg.Destroy(itemUi.items.back());
        itemUi.items.pop_back();
    }

    i32 idx = 0;
    for (const auto &entity: itemUi.items) {
        reg.GetOrAdd<RectTransform>(entity).rect.origin = {idx * s_IconSize.x + s_Padding.x / 2, s_Padding.y / 2};
        reg.GetOrAdd<RectTransform>(entity).rect.aspect = {s_IconSize.x - s_Padding.x / 2, s_IconSize.y - s_Padding.y / 2};
        reg.GetOrAdd<Gui::Image>(entity).imagePath      = inventory.items[idx].imagePath;

        idx++;
    }
}

#endif //ITEMUI_HPP
