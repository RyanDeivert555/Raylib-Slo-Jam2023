#include "../include/world.h"
#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"
#include <type_traits>
// debug
#include <iostream>

namespace World {
    GameState state = GameState::Logo;
    std::vector<NpcShip> spaceships{};
    std::vector<Bullet> bullets{};
    std::vector<Asteroid> asteroids{};
    Player player{Sprite::redShip1Id};
    const float cameraZoomFactor = 2.0f;
    const float minZoom = 0.5f;
    const float maxZoom = 1.0f;
    Camera2D camera{
        .offset = Vector2{windowWidth / 2.0f, windowHeight / 2.0f},
        .target = Vector2{1000.0f, 1000.0f}, // create "zoom to" effect for player
        .rotation = 0.0f,
        .zoom = 1.0f
    };

    // TODO: better culling system for asteroids for performance
    const float asteroidTime = 1.0f;
    float asteroidSpawnTimer = asteroidTime;
    const float shipTime = 5.0f;
    float shipSpawnTimer = shipTime;

    // player score and time limit
    int score = 0;
    const float maxTimeLimit = 120.0f;
    float playerTimeLimit = maxTimeLimit;

    void Reset() {
        spaceships.clear();
        bullets.clear();
        asteroids.clear();
        score = 0;
        playerTimeLimit = maxTimeLimit;
        player.Position = Vector2Zero();
    }

    NpcShip& SpawnSpaceship(std::size_t textureId) {
        spaceships.emplace_back(textureId);
        return spaceships.back();
    }

    Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, bool fromPlayer, std::size_t textureId) {
        bullets.emplace_back(position, velocity, speed, fromPlayer, textureId);
        return bullets.back();
    }

    Asteroid& SpawnAsteroid(int level) {
        std::size_t textureId = Sprite::GetRandomTexture(Sprite::asteroidTextures);
        asteroids.emplace_back(level, textureId);
        return asteroids.back();
    }

    void DecrementAsteroidTimer() {
        asteroidSpawnTimer -= GetFrameTime();
        if (asteroidSpawnTimer <= 0.0f) {
            SpawnAsteroid(Asteroid::GetRandomLevel());
            asteroidSpawnTimer = asteroidTime;
        }
    }

    void DecrementShipTimer() {
        shipSpawnTimer -= GetFrameTime();
        if (shipSpawnTimer < 0.0f) {
            std::size_t randId = Sprite::GetRandomTexture(Sprite::shipTextures);
            SpawnSpaceship(randId);
            shipSpawnTimer = shipTime;
        }
    }

    bool DecrementPlayerTimer() {
        playerTimeLimit -= GetFrameTime();
        return playerTimeLimit <= 0.0f;
    }

    void CollideBulletsAndAsteroids() {
        for (auto& bullet : bullets) {
            for (auto& asteroid : asteroids) {
                if (bullet.Collide(asteroid)) {
                    bullet.Kill();
                    asteroid.Split();
                    if (bullet.FromPlayer) {
                        score++;
                    }
                }
            }
        }
    }

    template<class T>
    void CullFromSceen(std::vector<T>& entities) {
        for (T& entity : entities) {
            Rectangle rect = entity.GetRect();

            float x = rect.x;
            float y = rect.y;
            Vector2 screenOrigin = GetScreenToWorld2D(Vector2Zero(), camera);
            Vector2 screenBounds = GetScreenToWorld2D(Vector2{windowWidth, windowHeight}, camera);

            if (x < screenOrigin.x - rect.width
                || x > screenBounds.x
                || y < screenOrigin.y - rect.height
                || y > screenBounds.y) {
                entity.ShouldDraw = false;
                if constexpr (std::is_same_v<T, Bullet>) {
                    entity.Alive = false;
                }
            }
            else {
                entity.ShouldDraw = true;
            }
        } 
    }

    void UpdateCamera() {
        // TODO: fix magic numbers
        Vector2 difference = Vector2Subtract(player.Position, camera.target);
        float length = Vector2Length(difference);
        if (length > 10.0f) {
            float cameraSpeed = std::max(length * 2.0f, 30.0f);
            camera.target = Vector2Add(camera.target, Vector2Scale(difference, cameraSpeed * GetFrameTime() / length));
        }
        if (IsKeyDown(KEY_UP)) {
            camera.zoom = Clamp(camera.zoom + cameraZoomFactor * GetFrameTime(), minZoom, maxZoom);
        }
        if (IsKeyDown(KEY_DOWN)) {
            camera.zoom = Clamp(camera.zoom - cameraZoomFactor * GetFrameTime(), minZoom, maxZoom);
        }
    }

    template<class T>
    void UpdateEntities(std::vector<T>& entities) {
        for (T& e : entities) {
            e.Update();
        }
        std::erase_if(entities, [](const T& e) { return !e.Alive; });
    }

    template<class T>
    void DrawEntities(std::vector<T>& entities) {
        for (const T& e : entities) {
            if (e.ShouldDraw) {
                e.Draw();
                // debug
                DrawRectangleLinesEx(e.GetRect(), 1.0f, GREEN);
            }
        }
    }

    void Update() {
        switch (state) {
            case GameState::Logo:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    state = GameState::Gameplay;
                }
                break;
            }
            case GameState::Gameplay:
            {
                DecrementAsteroidTimer();
                DecrementShipTimer();
                player.Update();
                UpdateCamera();
                UpdateEntities(spaceships);
                UpdateEntities(bullets);
                UpdateEntities(asteroids);
                CollideBulletsAndAsteroids();
                CullFromSceen(spaceships);
                CullFromSceen(bullets);
                CullFromSceen(asteroids);
                if (IsKeyPressed(KEY_P)) {
                    state = GameState::Paused;
                }
                bool gameOver = DecrementPlayerTimer();
                if (gameOver) {
                    state = GameState::GameOver;
                }
                break;
            }
            case GameState::Paused:
            {
                if (IsKeyPressed(KEY_P)) {
                    state = GameState::Gameplay;
                }
                break;
            }

            case GameState::GameOver:
            {
                if (IsKeyPressed(KEY_ENTER)) {
                    state = GameState::Gameplay;
                    Reset();
                }
                break;
            }
        }
    }

    void DrawGame() {
        Sprite::DrawBackground();
        BeginMode2D(camera);
        player.Draw();
        DrawEntities(bullets);
        DrawEntities(spaceships);
        DrawEntities(asteroids);
        EndMode2D();
        //DrawFPS(0, 0);
        Sprite::DrawText(TextFormat("Score [%d]", score), Vector2Zero(), 50.0f, 10.0f, MAROON);
        Sprite::DrawText(TextFormat("Time Limit [%.0f]", playerTimeLimit), Vector2{0.0f, 50.0f}, 25.0f, 10.0f, MAROON);
    }

    void Draw() {
        switch (state) {
            case GameState::Logo:
            {
                Sprite::DrawBackground();
                Sprite::DrawTextCenter("Press [Enter] to Start", 75.0f, 10.0f, MAROON);
                break;
            }

            case GameState::Gameplay:
            {
                DrawGame();
                break;
            }
            case GameState::Paused:
            {
                DrawGame();
                Sprite::DrawTextCenter("Press [P] to Unpause", 50.0f, 10.0f, MAROON);
                break;
            }

            case GameState::GameOver:
            {
                Sprite::DrawBackground();
                Sprite::DrawTextCenter(TextFormat("Score %d\n\n\n\nPress [Enter] to Play Again", score), 50.0f, 10.0f, MAROON);
                break;
            }
        }
    }
}
