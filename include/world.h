#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include "player.h"
#include <vector>

constexpr int windowWidth = 1440;
constexpr int windowHeight = 900;

enum class GameState {
	Logo,
	Gameplay,
	Paused,
	GameOver,
};

namespace World {
	extern GameState state;
	extern std::vector<Spaceship> spaceships;
	extern std::vector<Bullet> bullets;
	extern std::vector<Asteroid> asteroids;
	extern Player player;

	Spaceship& SpawnSpaceship(std::size_t textureId);
	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, bool fromPlayer, std::size_t textureId);
	Asteroid& SpawnAsteroid(int level, std::size_t textureId);
	void Update();
	void Draw();
}
