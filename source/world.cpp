#include "../include/world.h"
#include "../include/sprite.h"
#include "raylib.h"
#include "raymath.h"
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
	Camera2D camera{
		.offset = Vector2{windowWidth / 2.0f, windowHeight / 2.0f},
		.target = player.Position,
		.rotation = 0.0f,
		.zoom = 1.0f
	};

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
			} else {
				entity.ShouldDraw = true;
			}
		} 
	}

	void UpdateCamera() {
		Vector2 position = player.Position;
		Vector2 direction = player.Direction;
		Vector2 oppositeDirection = Vector2Negate(direction);
		float speed = player.Speed;
		Vector2 velocity = Vector2Scale(oppositeDirection, speed / 2.0f);
		Vector2 target = Vector2Add(position, velocity);
		// TODO: make dynamic camera
		camera.target = player.Position;
		//camera.rotation = player.Rotation;
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
				if (IsKeyPressed(KEY_ENTER)) {
					World::SpawnAsteroid(4, Sprite::asteroid1Id);
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
				BeginMode2D(camera);
				player.Draw();
				DrawEntities(bullets);
				DrawEntities(spaceships);
				DrawEntities(asteroids);
				EndMode2D();
				break;
			}
			case GameState::Paused:
			{
				BeginMode2D(camera);
				player.Draw();
				DrawEntities(bullets);
				DrawEntities(spaceships);
				DrawEntities(asteroids);
				EndMode2D();
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
