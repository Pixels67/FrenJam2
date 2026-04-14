#ifndef AUDIOHANDLER_HPP
#define AUDIOHANDLER_HPP

#include "Flock.hpp"
#include "Using.hpp"

struct AudioHandler {
    Entity                                  musicPlayer;
    std::unordered_map<std::string, Entity> sfxPlayers;

    std::string currentMusic;
    f32         fadeTime = 1.0F;
    bool        fadeOut  = false;
    bool        loop     = true;

    void AddSfx(Registry &reg, const std::string &name, const std::string &clipPath, const f32 volume = 1.0F) {
        sfxPlayers[name] = reg.Create(AudioSource{.audioClipPath = clipPath, .volume = volume});
    }

    void PlaySfx(Registry &reg, const std::string &name) {
        if (sfxPlayers.contains(name)) {
            reg.GetOrAdd<AudioSource>(sfxPlayers[name]).Play();
        }
    }

    void PlayMusic(const std::string &filePath, const bool loop = true, const f32 fadeTimeSeconds = 1.0F) {
        fadeTime     = fadeTimeSeconds;
        fadeOut      = true;
        currentMusic = filePath;
        this->loop   = loop;
    }

    void StopMusic(Registry &reg) const {
        reg.Get<AudioSource>(musicPlayer)->get().Stop();
    }

    void Update(Registry &reg, const f32 deltaTime) {
        if (musicPlayer.id == FLK_INVALID) {
            musicPlayer = reg.Create();
        }

        if (fadeTime > 0.0F && fadeOut) {
            reg.GetOrAdd<AudioSource>(musicPlayer).volume = std::min(fadeTime * 0.6F, 0.6F);
            fadeTime                                      -= deltaTime;
        }

        if (fadeTime <= 0.0F && fadeOut) {
            reg.GetOrAdd<AudioSource>(musicPlayer).audioClipPath = currentMusic;
            reg.GetOrAdd<AudioSource>(musicPlayer).looping       = loop;
            reg.GetOrAdd<AudioSource>(musicPlayer).Play();
            fadeOut = false;
        }

        if (fadeTime < 1.0F && !fadeOut) {
            reg.GetOrAdd<AudioSource>(musicPlayer).volume = std::min(fadeTime * 0.6F, 0.6F);
            fadeTime                                      += deltaTime;
        }

        if (fadeTime >= 1.0F && !fadeOut) {
            reg.GetOrAdd<AudioSource>(musicPlayer).volume = 0.6F;
        }
    }
};

FLK_ARCHIVE(AudioHandler, musicPlayer, sfxPlayers, currentMusic, fadeTime, fadeOut)

inline void UpdateAudio(World &world) {
    world.Resource<AudioHandler>().Update(world.Registry(), world.Resource<Time::TimeState>().deltaTime);
}

#endif //AUDIOHANDLER_HPP
