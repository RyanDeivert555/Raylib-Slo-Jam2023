#pragma once
#include "raylib.h"
#include <vector>

namespace SFX {
    extern std::vector<Sound> sounds;
    extern std::size_t projectileShootId;
    extern std::size_t shipExplosionId;
    extern std::size_t asteroidExplosionId;
    extern std::size_t hitId;
    extern std::size_t aggressiveAiId;
    extern std::size_t flightyAiId;
    extern std::size_t loseId;
    extern std::size_t gameStartId;
    extern std::size_t gameOverId;
    extern std::size_t pauseId;
    extern std::size_t unpauseId;

    std::size_t AddSound(const char* filePath, float pitch=1.0f);
    void Init();
    void PlaySound(std::size_t id);
    void UnloadSounds();
}
