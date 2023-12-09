#include "raylib.h"

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(800, 600, "GameJame2023");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}