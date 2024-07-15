#include "raylib.h"

#include <cmath>
#include <string>

const int screen_width = 800;
const int screen_height = 450;

class Player {
public:
    double x, y;
    double x_vel, y_vel;
    const int width = 50;
    const int height = 50;
    const int speed = 1;

    void draw() {
        DrawRectangle(x - (width / 2), y - (height / 2), width, height, RED);
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

    void draw_center() {
        DrawCircle(x, y, 3, GREEN);
    }
};

class Coin {
public:
    double x, y;
    const int radius = 10;

    void go_random_pos() {
        x = GetRandomValue(20, screen_width - 20);
        y = GetRandomValue(20, screen_height - 20);
    }

    void draw() {
        DrawCircle(x, y, radius, ORANGE);
    }

    bool touching_player(Player& player, int extra_distance = 0) {
        double distance = radius + (player.width / 2) + extra_distance;
        return abs(player.x - x) < distance && abs(player.y - y) < distance;
    }
};

class Score {
private:
    int score = 0;
    const char* text;
    const int size = 60;
    int x;
    int y = 25;
    int frame_count; 

public:
    void draw() {
        text = std::to_string(score).c_str();
        x = (screen_width / 2) - (MeasureText(text, size) / 2);

        if (frame_count > 2) {
            y = 25;
        }

        DrawText(text, x, y, size, BLUE);
        frame_count++;
    }

    void change(int increase) {
        score += increase;
        frame_count = 0;
        y = 15;
    }
};

int main() {
    InitWindow(screen_width, screen_height, "Test Game");
    SetTargetFPS(60);
    HideCursor();

    Player player;
    player.set_pos(400, 225);

    Coin coin;
    coin.go_random_pos();

    Score score;
    InitAudioDevice();
    Sound coin_sfx = LoadSound("C:\\Users\\kojom\\Downloads\\V_sys_039_0.wav");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Player

            player.x_vel *= 0.85;
            player.x_vel += IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
            player.change_x(player.x_vel * player.speed);
            // Stage Collision
            if (player.x - player.width / 2 < 0) {
                player.x = player.width / 2;
                player.x_vel = 0;
            }
            if (player.x + player.width / 2 > screen_width) {
                player.x = screen_width - player.width / 2;
                player.x_vel = 0;
            }

            player.y_vel *= 0.85;
            player.y_vel += IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
            player.change_y(player.y_vel * player.speed);
            // Stage Collision
            if (player.y - player.height / 2 < 0) {
                player.y = player.height / 2;
                player.y_vel = 0;
            }
            if (player.y + player.height / 2 > screen_height) {
                player.y = screen_height - player.height / 2;
                player.y_vel = 0;
            }

        // Coin

            if (coin.touching_player(player)) {
                score.change(1);
                PlaySound(coin_sfx);

                while(coin.touching_player(player, 100)) {
                    coin.go_random_pos();
                }
            }

        // Draw

            player.draw();
            coin.draw();
            DrawCircle(GetMouseX(), GetMouseY(), 4, BLACK); // Crosshair
            
            if (IsKeyDown(KEY_I)) {
                player.draw_center();
                DrawText(std::to_string(abs(player.x - coin.x)).c_str(), 5, 5, 20, GREEN); // X Difference
                DrawText(std::to_string(abs(player.y - coin.y)).c_str(), 5, 25, 20, GREEN); // Y Difference
            }

            score.draw();

        EndDrawing();
    }

    CloseWindow();
}