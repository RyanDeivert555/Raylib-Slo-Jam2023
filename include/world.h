#pragma once
#include "npc_ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "player.h"
#include <vector>

constexpr int windowWidth = 1000; // dev in 1920
constexpr int windowHeight = 800; // dev in 1080

static constexpr float SpawnOffset = 500.0f;

float GetRandomValueF(float min, float max);
Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax);
Vector2 GetSpawnPoint();

enum class GameState {
    Logo,
    Gameplay,
    Paused,
    GameOver,
};

namespace World {
    // FIXME: do these need to be extern? might only need to be in this namespace
    extern GameState state;
    extern std::vector<NpcShip> spaceships;
    extern std::vector<Bullet> bullets;
    extern std::vector<Bullet> playerBullets;
    extern std::vector<Asteroid> asteroids;
    extern Player player;
    extern Camera2D camera;

    void Init();
    NpcShip& SpawnSpaceship(std::size_t textureId);
    Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId);
    Bullet& SpawnPlayerBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId);
    Asteroid& SpawnAsteroid(int level);
    void MainLoop();
}
