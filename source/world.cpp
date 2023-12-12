#include "../include/world.h"
#include "raylib.h"
#include <vector>
#include <type_traits>
// debug
#include <iostream>

namespace World {
	std::vector<Spaceship> spaceships{};
	std::vector<Bullet> bullets{};
	std::vector<Asteroid> asteroids{};

	Spaceship& SpawnSpaceship(std::size_t textureId) {
		spaceships.emplace_back(textureId);
		return spaceships.back();
	}

	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, std::size_t textureId) {
		bullets.emplace_back(position, velocity, speed, textureId);
		return bullets.back();
	}

	Asteroid& SpawnAsteroid(int level, std::size_t textureId) {
		asteroids.emplace_back(level, textureId);
		return asteroids.back();
	}

	template<class T>
	void CullFromSceen(std::vector<T> &entities) {
		for (T& entity : entities) {
			Rectangle rect = entity.GetRect();
			Vector2 scale = entity.Scale;
			rect.width /= scale.x;
			rect.height /= scale.y;

			float x = rect.x;
			float y = rect.y;
			float screenWidth = static_cast<float>(GetScreenWidth());
			float screenHeight = static_cast<float>(GetScreenHeight());
			if (x > screenWidth 
				|| x < 0.0f - rect.width 
				|| y > screenHeight 
				|| y <= 0.0f - rect.height) {
				entity.ShouldDraw = false;
				if constexpr (std::is_same_v<T, Bullet>) {
					entity.Alive = false;
				}
			} else {
				entity.ShouldDraw = true;
			}
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
		UpdateEntities(spaceships);
		UpdateEntities(bullets);
		UpdateEntities(asteroids);
		CullFromSceen(spaceships);
		CullFromSceen(bullets);
		CullFromSceen(asteroids);
	}

	void Draw() {
		DrawEntities(bullets);
		DrawEntities(spaceships);
		DrawEntities(asteroids);
	}
}
