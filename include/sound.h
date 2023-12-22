#pragma once
#include "raylib.h"
#include <vector>

namespace SFX {
    extern std::vector<Sound> sounds;
    extern std::size_t projectileShootId;

    std::size_t AddSound(const char* filePath, float pitch=1.0f);
    void Init();
    void PlaySound(std::size_t id);
    void UnloadSounds();
}