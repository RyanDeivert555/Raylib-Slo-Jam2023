#include "raylib.h"
#include "../include/game.h"
#include "../include/sprite.h"
#include "../include/spaceship.h"

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(windowWidth, windowHeight, "GameJame2023");
	SetTargetFPS(60);
	Sprite::Init();

	Spaceship test(Sprite::playerShipId);
	test.Position = Vector2{500.0f, 500.0f};

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_A)) {
			test.Rotation -= 5.0f;
		}
		if (IsKeyDown(KEY_D)) {
			test.Rotation += 5.0f;
		}
		if (IsKeyDown(KEY_W)) {
			test.RotationalVelocity = 500.0f;
		} else {
			test.RotationalVelocity = 250.0f;
		}
		test.Update();
		BeginDrawing();
		ClearBackground(WHITE);
		test.Draw();
		DrawFPS(0, 0);
		EndDrawing();
	}
	Sprite::UnloadTextures();
	CloseWindow();
	
	return 0;
}