#include "raylib.h"

class Player {
public:
    double x, y;
    double x_vel, y_vel;
    const int width = 50;
    const int height = 50;
    const int speed = 1;

    void draw() {
        DrawRectangle(x, y, width, height, RED);
    }

    void set_pos(int input_x, int input_y) {
        x = input_x;
        y = input_y;
    }

    void change_x(double distance) {
        x += distance;
    }
    void change_y(double distance) {
        y += distance;
    }
};

int main() {
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height, "Test Game");
    SetTargetFPS(60);
    HideCursor();

    Player player;
    player.set_pos(400, 225);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Player

        player.x_vel *= 0.85;
        player.x_vel += IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
        player.change_x(player.x_vel * player.speed);

        player.y_vel *= 0.85;
        player.y_vel += IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
        player.change_y(player.y_vel * player.speed);
    
        player.draw();

        // Crosshair

        DrawCircle(GetMouseX(), GetMouseY(), 10, BLACK);

        EndDrawing();
    }

    CloseWindow();
}