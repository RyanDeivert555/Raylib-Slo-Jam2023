#include "raylib.h"
#include "../include/game.h"
#include "../include/sprite.h"
#include "../include/world.h"

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(windowWidth, windowHeight, "GameJame2023");
	SetTargetFPS(60);
	Sprite::Init();

	for (int i = 0; i < 5; i++) {
		Spaceship& ship = World::SpawnSpaceship(Sprite::redShipId);
		ship.Position.x += 100.0f * i;
	}

	while (!WindowShouldClose()) {
		for (auto& ship : World::spaceships) {
			if (IsKeyDown(KEY_A)) {
				ship.Rotation -= 5.0f;
			}
			if (IsKeyDown(KEY_D)) {
				ship.Rotation += 5.0f;
			}
			if (IsKeyDown(KEY_W)) {
				ship.RotationalVelocity = 500.0f;
			} else {
				ship.RotationalVelocity = 250.0f;
			}
		}
		World::UpdateSpaceships();
		BeginDrawing();
		ClearBackground(WHITE);
		World::DrawSpaceships();
		DrawFPS(0, 0);
		EndDrawing();
	}
	Sprite::UnloadTextures();
	CloseWindow();
	
	return 0;
}