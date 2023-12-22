#include "../include/sound.h"
#include "raylib.h"
// debug
#include <iostream>

namespace SFX {
    std::vector<Sound> sounds{};
    std::size_t projectileShootId{};

    std::size_t AddSound(const char* filePath, float pitch) {
        Sound sound = LoadSound(filePath);
        sounds.push_back(sound);

        return sounds.size() - 1;
    }

    void Init() {
        InitAudioDevice();
        SetMasterVolume(0.5);
        projectileShootId = AddSound("../assets/projectileShoot.ogg");
    }

    void PlaySound(std::size_t id) {
        ::PlaySound(sounds[id]);
    }

    void UnloadSounds() {
        for (auto& sound : sounds) {
            UnloadSound(sound);
        }
        CloseAudioDevice();
    }
}