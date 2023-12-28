#include "../include/world.h"
#include "../include/sprite.h"
#include "../include/sound.h"
#include "raylib.h"
#include "raymath.h"
#include <type_traits>
// debug
#include <iostream>

float GetRandomValueF(float min, float max) {
    if (min > max) {
        float temp = min;
        min = max;
        max = temp;
    }
    float param = rand() / static_cast<float>(RAND_MAX);
    return float(min + (max - min) * param);
}

Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax) {
    float x = GetRandomValueF(xMin, xMax);
    float y = GetRandomValueF(yMin, yMax);
    Vector2 result{x, y};

    return result;
}

Vector2 GetSpawnPoint() {
    Vector2 screenOrigin = GetScreenToWorld2D(Vector2Zero(), World::camera);
    Vector2 screenBounds = GetScreenToWorld2D(Vector2{windowWidth, windowHeight}, World::camera);
    
    const Vector2 PossibleSpawnPoints[] = {
        // top
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenBounds.x + SpawnOffset, -SpawnOffset + screenOrigin.y, screenOrigin.y),
        // bottom
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenBounds.x + SpawnOffset, screenBounds.y, screenBounds.y + SpawnOffset),
        // left
        GetRandomVector2(-SpawnOffset + screenOrigin.x, screenOrigin.x, -SpawnOffset + screenBounds.y, screenBounds.y + SpawnOffset),
        // right
        GetRandomVector2(screenBounds.x, screenBounds.x + SpawnOffset, -SpawnOffset + screenOrigin.y, screenBounds.y),
    };

    int randIndex = GetRandomValue(0, 3);
    return PossibleSpawnPoints[randIndex];
}

namespace World {
    GameState state = GameState::Logo;
    std::vector<NpcShip> spaceships{};
    std::vector<Bullet> bullets{};
    std::vector<Bullet> playerBullets{};
    std::vector<Asteroid> asteroids{};
    // sprites not init yet!
    Player player{Sprite::ship0Id};
    const float cameraZoomFactor = 2.0f;
    const float minZoom = 0.50f;
    const float maxZoom = 1.0f;
    Camera2D camera{
        .offset = Vector2{windowWidth / 2.0f, windowHeight / 2.0f},
        .target = player.Position,
        .rotation = 0.0f,
        .zoom = maxZoom
    };
    bool supportController = false;

    // TODO: better culling system for asteroids for performance
    const float asteroidTime = 0.5f;
    float asteroidSpawnTimer = asteroidTime;
    const float shipTime = 3.0f;
    float shipSpawnTimer = shipTime;

    // player score and time limit
    std::size_t score = 0;
    const float maxTimeLimit = 120.0f;
    float playerTimeLimit = maxTimeLimit;

    void Init() {
        player.TextureId = Sprite::ship0Id;
    }

    void Reset() {
        spaceships.clear();
        bullets.clear();
        playerBullets.clear();
        asteroids.clear();
        player.Reset();
        score = 0;
        playerTimeLimit = maxTimeLimit;
        camera.target = player.Position;
    }

    void CheckGamePad() {
        supportController = IsGamepadAvailable(0);
    }

    NpcShip& SpawnSpaceship(std::size_t textureId) {
        spaceships.emplace_back(textureId);
        return spaceships.back();
    }

    Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId) {
        bullets.emplace_back(position, velocity, speed, textureId);
        return bullets.back();
    }

    Bullet& SpawnPlayerBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId) {
        playerBullets.emplace_back(position, velocity, speed, textureId);
        return playerBullets.back();
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
        for (auto& bullet : playerBullets) {
            for (auto& asteroid : asteroids) {
                if (bullet.Collide(asteroid)) {
                    bullet.Kill();
                    asteroid.Split();
                    score++;
                }
            }
        }
    }

    void CollideAsteroidsAndPlayer() {
        for (const auto& asteroid : asteroids) {
            if (asteroid.Collide(player)) {
                float damage = GetRandomValueF(10.0f, 20.0f);
                player.TakeDamage(damage);
            }
        }
    }

    void CollideBulletsAndNpcs() {
        for (auto& bullet : playerBullets) {
            for (auto& npc : spaceships) {
                if (bullet.Collide(npc)) {
                    bullet.Kill();
                    float damage = GetRandomValueF(10.0f, 50.0f);
                    npc.TakeDamage(damage);
                    if (!npc.Alive) {
                        score += 5;
                    }
                    npc.ReactToDamage();
                }
            }
        }
    }

    void CollideBulletsAndPlayer() {
        for (auto& bullet : bullets) {
            if (bullet.Collide(player)) {
                bullet.Kill();
                float damage = GetRandomValueF(10.0f, 25.0f);
                player.TakeDamage(damage);
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
        if (IsKeyDown(KEY_UP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) {
            camera.zoom = Clamp(camera.zoom + cameraZoomFactor * GetFrameTime(), minZoom, maxZoom);
        }
        if (IsKeyDown(KEY_DOWN) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) {
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
            }
        }
    }

    void Update() {
        CheckGamePad();
        switch (state) {
            case GameState::Logo:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
                    SFX::PlaySound(SFX::gameStartId);
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
                UpdateEntities(playerBullets);
                UpdateEntities(asteroids);
                CollideBulletsAndAsteroids();
                CollideAsteroidsAndPlayer();
                CollideBulletsAndNpcs();
                CollideBulletsAndPlayer();
                CullFromSceen(spaceships);
                CullFromSceen(bullets);
                CullFromSceen(playerBullets);
                CullFromSceen(asteroids);
                if (IsKeyPressed(KEY_P) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
                    SFX::PlaySound(SFX::pauseId);
                    state = GameState::Paused;
                }
                bool gameOver = DecrementPlayerTimer();
                if (gameOver) {
                    SFX::PlaySound(SFX::gameOverId);
                    state = GameState::GameOver;
                }
                if (!player.Alive) {
                    SFX::PlaySound(SFX::loseId);
                    state = GameState::GameOver;
                }
                break;
            }
            case GameState::Paused:
            {
                if (IsKeyPressed(KEY_P) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
                    SFX::PlaySound(SFX::unpauseId);
                    state = GameState::Gameplay;
                }
                break;
            }

            case GameState::GameOver:
            {
                if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
                    SFX::PlaySound(SFX::gameStartId);
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
        DrawEntities(playerBullets);
        DrawEntities(spaceships);
        DrawEntities(asteroids);
        EndMode2D();
        Sprite::DrawText(TextFormat("Score: %zu", score), Vector2Zero(), 50.0f, 10.0f, RAYWHITE);
        Sprite::DrawText(TextFormat("Time Limit: %.0f seconds", playerTimeLimit), Vector2{0.0f, 50.0f}, 25.0f, 10.0f, RAYWHITE);
        player.DrawShieldWarning();
    }

    void Draw() {
        switch (state) {
            case GameState::Logo:
            {
                Sprite::DrawBackground();
                if (supportController) {
                    Sprite::DrawTextCenter("Press [A] to Start", Vector2Zero(), 75.0f, 10.0f, RAYWHITE);    
                }
                else {
                    Sprite::DrawTextCenter("Press [Enter] to Start", Vector2Zero(), 75.0f, 10.0f, RAYWHITE);      
                }
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
                if (supportController) {
                    Sprite::DrawTextCenter("Press [Start] to Unpause", Vector2Zero(), 50.0f, 10.0f, RAYWHITE);
                }
                else {
                    Sprite::DrawTextCenter("Press [P] to Unpause", Vector2Zero(), 50.0f, 10.0f, RAYWHITE);
                }
                break;
            }

            case GameState::GameOver:
            {
                Sprite::DrawBackground();
                if (!player.Alive) {
                    Sprite::DrawTextCenter("You Died!", Vector2{0.0f, -50.0f}, 50.0f, 10.0f, RAYWHITE);
                }
                Sprite::DrawTextCenter(TextFormat("Score: %d", score), Vector2Zero(), 50.0f, 10.0f, RAYWHITE);
                if (supportController) {
                    Sprite::DrawTextCenter("Press [A] to Play Again", Vector2{0.0f, 50.0f}, 25.0f, 10.0f, RAYWHITE);
                }
                else {
                    Sprite::DrawTextCenter("Press [Enter] to Play Again", Vector2{0.0f, 50.0f}, 25.0f, 10.0f, RAYWHITE);
                }
                break;
            }
        }
    }

    void MainLoop() {
        Update();
        BeginDrawing();
        ClearBackground(WHITE);
        Draw();
        EndDrawing();
    }
}
