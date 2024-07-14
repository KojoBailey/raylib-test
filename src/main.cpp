#include "raylib.h"

int main() {
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "Test Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangle(50, 50, 200, 200, BLACK);
        DrawText("I am going to commit mass murder.", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}