#ifndef FLK_AUDIOSOURCE_HPP
#define FLK_AUDIOSOURCE_HPP

#include "Common.hpp"
#include "Math/Vector.hpp"
#include "Serial/Archive.hpp"

namespace Flock::Audio {
    struct FLK_API AudioSource {
        std::string audioClipPath;
        bool        play       = false;
        Vector3f    position   = {};
        f32         volume     = 0.5F;
        f32         pitch      = 1.0F;
        f32         pan        = 0.0F;
        bool        looping    = false;
        bool        spatialize = false;

        void Play() {
            play = true;
        }
    };

    FLK_ARCHIVE(
        AudioSource,
        audioClipPath,
        play,
        position,
        volume,
        pitch,
        pan,
        looping,
        spatialize
    )
}

#endif //FLK_AUDIOSOURCE_HPP
