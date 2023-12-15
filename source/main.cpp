#include "../include/sprite.h"
#include "../include/world.h"
#include "raylib.h"

int main() {
	SetTraceLogLevel(LOG_WARNING);
	InitWindow(windowWidth, windowHeight, "GameJam2023");
	SetTargetFPS(60);
	
	World::Init();
	Sprite::Init();

	while (!WindowShouldClose()) {
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