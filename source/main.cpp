#include "../include/sprite.h"
#include "../include/world.h"
#include "../include/sound.h"
#include "raylib.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif

void MainLoop() {
    World::Update();
    BeginDrawing();
    ClearBackground(WHITE);
    World::Draw();
    EndDrawing();
}

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(windowWidth, windowHeight, "GameJam2023");
    
    Sprite::Init();
    SFX::Init();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(MainLoop, 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        MainLoop();
    }
#endif

    Sprite::UnloadTextures();
    SFX::UnloadSounds();
    CloseWindow();
    
    return 0;
}