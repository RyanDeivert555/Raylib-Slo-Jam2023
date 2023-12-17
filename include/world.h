#pragma once
#include "npc_ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "player.h"
#include <vector>

constexpr int windowWidth = 1440;
constexpr int windowHeight = 900;

static constexpr float SpawnOffset = 500.0f;

inline Vector2 GetRandomVector2(float xMin, float xMax, float yMin, float yMax) {
	float x = static_cast<float>(GetRandomValue(xMin, xMax));
	float y = static_cast<float>(GetRandomValue(yMin, yMax));
	Vector2 result = Vector2{x, y};

	return result;
}

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
	extern std::vector<Asteroid> asteroids;
	extern Player player;
	extern Camera2D camera;

	// TODO: purpose of Init?
	void Init();
	NpcShip& SpawnSpaceship(std::size_t textureId);
	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, bool fromPlayer, std::size_t textureId);
	Asteroid& SpawnAsteroid(int level);
	void Update();
	void Draw();
}
