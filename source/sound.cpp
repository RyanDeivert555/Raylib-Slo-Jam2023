#include "../include/sound.h"
#include "raylib.h"

namespace SFX {
    std::vector<Sound> sounds{};
    std::size_t projectileShootId{};
    std::size_t shipExplosionId{};
    std::size_t asteroidExplosionId{};
    std::size_t hitId{};
    std::size_t aggressiveAiId{};
    std::size_t flightyAiId{};
    std::size_t loseId{};
    std::size_t gameStartId{};
    std::size_t gameOverId{};
    std::size_t pauseId{};
    std::size_t unpauseId{};
    std::size_t shieldBreakId;
    Music music{};

    std::size_t AddSound(const char* filePath, float pitch) {
        Sound sound = LoadSound(filePath);
        sounds.push_back(sound);

        return sounds.size() - 1;
    }

    void Init() {
        InitAudioDevice();
        SetMasterVolume(0.5);
        projectileShootId = AddSound("../assets/projectileShoot.ogg");
        shipExplosionId = AddSound("../assets/ship_explosion.ogg");
        asteroidExplosionId = AddSound("../assets/asteroid_explosion.ogg");
        hitId = AddSound("../assets/hit.ogg");
        aggressiveAiId = AddSound("../assets/aggressive.ogg");
        flightyAiId = AddSound("../assets/flighty.ogg");
        loseId = AddSound("../assets/lose.ogg");
        gameStartId = AddSound("../assets/game_start.ogg");
        gameOverId = AddSound("../assets/time_out.ogg");
        pauseId = AddSound("../assets/pause.ogg");
        unpauseId = AddSound("../assets/unpause.ogg");
        shieldBreakId = AddSound("../assets/shield_break.ogg");
        music = LoadMusicStream("../assets/music.ogg");
        PlayMusicStream(music);
    }

    void PlaySound(std::size_t id) {
        ::PlaySound(sounds[id]);
    }

    void UnloadSounds() {
        for (auto& sound : sounds) {
            UnloadSound(sound);
        }
        UnloadMusicStream(music);
        CloseAudioDevice();
    }
}
