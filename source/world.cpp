#include "../include/world.h"
#include "../include/sprite.h"
#include "raylib.h"
#include <type_traits>
// debug
#include <iostream>

namespace World {
	GameState state = GameState::Logo;
	std::vector<NpcShip> spaceships{};
	std::vector<Bullet> bullets{};
	std::vector<Asteroid> asteroids{};
	Player player{Sprite::redShip1Id};
	const float cameraZoomFactor = 2.0f;
	const float minZoom = 0.5f;
	const float maxZoom = 1.0f;
	Camera2D camera{
		.offset = Vector2{windowWidth / 2.0f, windowHeight / 2.0f},
		.target = player.Position,
		.rotation = 0.0f,
		.zoom = 1.0f
	};

	// TODO: better culling system for asteroids for performance
	const float asteroidTime = 1.0f;
	float asteroidSpawnTimer = asteroidTime;
	const float shipTime = 2.0f;
	float shipSpawnTimer = shipTime;

	void Init() {
		// for (int i = 0; i < 1; i++) {
		// 	NpcShip& ship = SpawnSpaceship(Sprite::redShipId);
		// 	ship.Position.x += 100.0f + (i * 10.0f);
		// 	// debug
		// 	ship.SetState(State::Passive);
		// }
	}

	NpcShip& SpawnSpaceship(std::size_t textureId) {
		spaceships.emplace_back(textureId);
		return spaceships.back();
	}

	Bullet& SpawnBullet(Vector2 position, Vector2 velocity, float speed, bool fromPlayer, std::size_t textureId) {
		bullets.emplace_back(position, velocity, speed, fromPlayer, textureId);
		return bullets.back();
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
			int randIndex = GetRandomValue(0, Sprite::shipTextures.size() - 1);
			std::size_t randId = Sprite::shipTextures[randIndex];
			SpawnSpaceship(randId);
			shipSpawnTimer = shipTime;
		}
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
		if (IsKeyDown(KEY_UP)) {
			camera.zoom = Clamp(camera.zoom + cameraZoomFactor * GetFrameTime(), minZoom, maxZoom);
		}
		if (IsKeyDown(KEY_DOWN)) {
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
				// debug
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
				DecrementAsteroidTimer();
				DecrementShipTimer();
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
