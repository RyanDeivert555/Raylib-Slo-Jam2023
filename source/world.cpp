#include "../include/world.h"
#include "../include/sprite.h"
#include "raylib.h"
#include <vector>
#include <type_traits>
// debug
#include <iostream>

namespace World {
	GameState state = GameState::Logo;
	std::vector<Spaceship> spaceships{};
	std::vector<Bullet> bullets{};
	std::vector<Asteroid> asteroids{};
	Player player{Sprite::redShipId};

	Spaceship& SpawnSpaceship(std::size_t textureId) {
		spaceships.emplace_back(textureId);
		return spaceships.back();
	}

	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, bool fromPlayer, std::size_t textureId) {
		bullets.emplace_back(position, velocity, speed, fromPlayer, textureId);
		return bullets.back();
	}

	Asteroid& SpawnAsteroid(int level, std::size_t textureId) {
		asteroids.emplace_back(level, textureId);
		return asteroids.back();
	}

	void CollideBulletsAndAsteroids() {
		for (auto& bullet : bullets) {
			for (auto& asteroid : asteroids) {
				if (bullet.Collide(asteroid)) {
					bullet.Kill();
					asteroid.Split();
				}
			}
		}
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
				player.Update();
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
				break;
			}
		}
	}

	void Draw() {
		switch (state) {
			case GameState::Logo:
			{
				DrawText("Press Enter to Start", 100, 100, 100, RED);
				break;
			}

			case GameState::Gameplay:
			{
				player.Draw();
				DrawEntities(bullets);
				DrawEntities(spaceships);
				DrawEntities(asteroids);
				break;
			}
			case GameState::Paused:
			{
				player.Draw();
				DrawEntities(bullets);
				DrawEntities(spaceships);
				DrawEntities(asteroids);
				DrawText("Press P to Unpause", 100, 100, 100, RED);
				break;
			}

			case GameState::GameOver:
			{
				break;
			}
		}
	}
}
