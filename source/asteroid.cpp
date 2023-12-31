#include "../include/asteroid.h"
#include "../include/sprite.h"
#include "../include/world.h"
#include "../include/sound.h"

Asteroid::Asteroid(int level, std::size_t id) {
    TextureId = id;
    Position = GetSpawnPoint();
    Vector2 screenBounds = GetScreenToWorld2D(Vector2{windowWidth, windowHeight}, World::camera);
    Vector2 centerScreen = Vector2Scale(screenBounds, 0.5f);
    Direction = Vector2Normalize(Vector2Subtract(centerScreen, Position));
    Speed = GetRandomValueF(250.0f, 250.0f * level);
    RotationSpeed = GetRandomValueF(-200.0f, 200.0f);
    _level = level;
    Scale = Vector2Scale(Vector2{2.0f, 2.0f}, _level / (MaxLevel * 2.0f));
}

void Asteroid::Split() {
    SFX::PlaySound(SFX::asteroidExplosionId);
    Kill();
    _level--;
    if (_level <= 0) return;
    for (int i = 0; i < 2; i++) {
        Asteroid& asteroid = World::SpawnAsteroid(_level);
        asteroid.Position = Position;
    }
}

void Asteroid::Update() {
    Rotation += RotationSpeed * GetFrameTime();
    Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Asteroid::Draw() const {
    Sprite::Draw(TextureId, Position, Scale, Rotation, Sprite::Center(TextureId, Scale));
}
