#include "raylib.h"
int main()
{
    // Window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // Initialize window
    InitWindow(windowWidth,windowHeight,"Dasher");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Stop drawing
        EndDrawing();
    }
    CloseWindow();
}