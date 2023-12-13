#include "../include/asteroid.h"
#include "../include/sprite.h"
#include "../include/world.h"
#include "raylib.h"
#include "raymath.h"
// debug
#include <iostream>

// helpers
static Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax) {
	float x = static_cast<float>(GetRandomValue(xMin, xMax));
	float y = static_cast<float>(GetRandomValue(yMin, yMax));
	Vector2 result = Vector2{x, y};

	return result;
}

static Vector2 CenterScreen() {
	Vector2 result = Vector2 {
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(GetScreenHeight())
	};
	result.x /= 2.0f;
	result.y /= 2.0f;

	return result;
}

static constexpr float Offset = 500.0f;

Asteroid::Asteroid(int level, std::size_t id) {
	static const Vector2 PossibleSpawnPoints[] = {
		// top
		GetRandomVector2(-Offset, GetScreenWidth() + Offset, -Offset, 0.0f),
		// bottom
		GetRandomVector2(-Offset, GetScreenWidth() + Offset, GetScreenHeight(), GetScreenHeight() + Offset),
		// left
		GetRandomVector2(-Offset, 0.0f, -Offset, GetScreenHeight() + Offset),
		// right
		GetRandomVector2(GetScreenWidth(), GetScreenWidth() + Offset, -Offset, GetScreenHeight()),
	};

	TextureId = id;
	int randIndex = GetRandomValue(0, 3);
	Position = PossibleSpawnPoints[randIndex];
	Vector2 target = Vector2Add(CenterScreen(), GetRandomVector2(-Offset, Offset, -Offset, Offset));
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
	Position = Vector2Add(Position, Vector2Scale(Direction, Speed * GetFrameTime()));
}

void Asteroid::Draw() const {
	Sprite::Draw(TextureId, Position, Scale, Rotation, Sprite::Center(TextureId, Scale));
}