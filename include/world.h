#pragma once
#include "spaceship.h"
#include "bullet.h"
#include "asteroid.h"
#include <vector>

constexpr int windowWidth = 1280;
constexpr int windowHeight = 720;

enum class GameState {
	Logo,
	Menu,
	Gameplay,
	Paused,
	GameOver,
};

namespace World {
	extern std::vector<Spaceship> spaceships;
	extern std::vector<Bullet> bullets;
	extern std::vector<Asteroid> asteroids;

	Spaceship& SpawnSpaceship(std::size_t textureId);
	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId);
	Asteroid& SpawnAsteroid(int level, std::size_t textureId);
	void Update();
	void Draw();
}
