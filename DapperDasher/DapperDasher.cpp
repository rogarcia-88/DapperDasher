#include "raylib.h"

int main()
{
    // Window Dimensions
    const int windowWidth = 512;
    const int windowHeight = 380;

    // Initialize Window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher!");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
}
