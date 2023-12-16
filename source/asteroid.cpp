#include "../include/asteroid.h"
#include "../include/sprite.h"
#include "../include/world.h"
// debug
#include <iostream>

// helpers
static Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax) {
	float x = static_cast<float>(GetRandomValue(xMin, xMax));
	float y = static_cast<float>(GetRandomValue(yMin, yMax));
	Vector2 result = Vector2{x, y};

	return result;
}

static constexpr float Offset = 500.0f;

Asteroid::Asteroid(int level, std::size_t id) {
	Vector2 screenOrigin = GetScreenToWorld2D(Vector2Zero(), World::camera);
	Vector2 screenBounds = GetScreenToWorld2D(Vector2{windowWidth, windowHeight}, World::camera);
	
	const Vector2 PossibleSpawnPoints[] = {
		// top
		GetRandomVector2(-Offset + screenOrigin.x, screenBounds.x + Offset, -Offset + screenOrigin.y, screenOrigin.y),
		// bottom
		GetRandomVector2(-Offset + screenOrigin.x, screenBounds.x + Offset, screenBounds.y, screenBounds.y + Offset),
		// left
		GetRandomVector2(-Offset + screenOrigin.x, screenOrigin.x, -Offset + screenBounds.y, screenBounds.y + Offset),
		// right
		GetRandomVector2(screenBounds.x, screenBounds.x + Offset, -Offset + screenOrigin.y, screenBounds.y),
	};

	TextureId = id;
	RotationSpeed = static_cast<float>(GetRandomValue(-50, 50));
	int randIndex = GetRandomValue(0, 3);
	Position = PossibleSpawnPoints[randIndex];
	Vector2 centerScreen = Vector2Scale(screenBounds, 0.5f);
	Vector2 target = Vector2Add(centerScreen, GetRandomVector2(-Offset, Offset, -Offset, Offset));
	Direction = Vector2Normalize(Vector2Subtract(target, Position));
	_level = level;
	Scale = Vector2Scale(Scale, _level / (MaxLevel * 2.0f));
}

void Asteroid::Split() {
	Kill();
	_level--;
	if (_level <= 0) return;
	int randIndex = GetRandomValue(0, Sprite::asteroidTextures.size() - 1);
	std::size_t textureId = Sprite::asteroidTextures[randIndex];
	for (int i = 0; i < 2; i++) {
		Asteroid& asteroid = World::SpawnAsteroid(_level, textureId);
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