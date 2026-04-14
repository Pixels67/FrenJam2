#ifndef FADE_HPP
#define FADE_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct Fade {
    f32 time  = 12.0F;
    f32 timer = 0.0F;
};

FLK_ARCHIVE(Fade, time, timer)

inline void UpdateFades(World &world) {
    world.Registry().ForEach<Fade, Box>([&](Fade &fade, Box &box) {
        if (fade.timer < fade.time) {
            fade.timer += world.Resource<Time::TimeState>().deltaTime;
            box.color.a = 255 - std::min(fade.timer / fade.time, 0.98F) * 255;
        } else {
            box.color.a = 0;
        }
    });
}

#endif //FADE_HPP
