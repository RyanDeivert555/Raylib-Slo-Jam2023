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
	test.AddPosition(Vector2{500.0f, 500.0f});

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_A)) {
			test.AddRotation(-5.0f);
		}
		if (IsKeyDown(KEY_D)) {
			test.AddRotation(5.0f);
		}
		if (IsKeyDown(KEY_W)) {
			test.SetRotationalVelocity(500.0f);
		} else {
			test.SetRotationalVelocity(250.0f);
		}
		test.Update();
		BeginDrawing();
		ClearBackground(WHITE);
		test.Draw();
		EndDrawing();
	}
	Sprite::UnloadTextures();
	CloseWindow();
	
	return 0;
}