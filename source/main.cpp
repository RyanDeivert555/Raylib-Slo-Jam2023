#include "../include/sprite.h"
#include "../include/world.h"
#include "raylib.h"

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(windowWidth, windowHeight, "GameJam2023");
	SetTargetFPS(60);
	Sprite::Init();

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_ENTER)) {
			World::SpawnAsteroid(4, Sprite::asteroid1Id);
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