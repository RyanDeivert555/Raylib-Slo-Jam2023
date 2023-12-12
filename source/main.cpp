#include "raylib.h"
#include "../include/sprite.h"
#include "../include/world.h"

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(windowWidth, windowHeight, "GameJam2023");
	SetTargetFPS(60);
	Sprite::Init();

	for (int i = 0; i < 5; i++) {
		Spaceship& ship = World::SpawnSpaceship(Sprite::redShipId);
		ship.Position.x += 100.0f * i;
		ship.Position.y += 100.0f * i;
	}

	while (!WindowShouldClose()) {
		for (auto& ship : World::spaceships) {
			if (IsKeyDown(KEY_A)) {
				ship.Rotation -= 150.0f * GetFrameTime();
			}
			if (IsKeyDown(KEY_D)) {
				ship.Rotation += 150.0f * GetFrameTime();
			}
			if (IsKeyDown(KEY_W)) {
				ship.Speed = 500.0f;
			} else {
				ship.Speed = 250.0f;
			}
			if (IsKeyDown(KEY_SPACE)) {
				ship.Shoot();
			}
		}
		World::Update();
		BeginDrawing();
		ClearBackground(WHITE);
		World::Draw();
		DrawFPS(0, 0);
		EndDrawing();
	}
	Sprite::UnloadTextures();
	CloseWindow();
	
	return 0;
}