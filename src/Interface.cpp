#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "raylib.h"
#include "../include/State.h"
#include "../include/Interface.h"

Interface::Interface() {
    cout << "Interface created successfully!" << endl;
}

Interface::~Interface() {
    cout << "Interface destroyed successfully!" << endl;
}

void Interface::init() {
    int screenWidth = 800;
    int screenHight = 600;
    int gameFps = 60;
    
    InitWindow(screenWidth, screenHight, "Snake Game by Task2401");
    SetTargetFPS(gameFps);

    Image gameIcon = LoadImage("../asset/game_icon.svg");
    
    SetWindowIcon(gameIcon);
    UnloadImage(gameIcon);

    cout << "Window opened and configured successfully via init()!" << endl;
}

void Interface::close() {
    CloseWindow();
    cout << "Window closed successfully via close()!" << endl;
}

void Interface::draw_frame(const State& state) {
    ClearBackground(LIGHTGRAY);

    const auto& objects = state.getObjects();
    const auto& snake = state.getSnake();
    const auto& snakeBody = snake.getSnakeBody();
    Position snakeHeadPos = snake.getHeadPos();
    Camera2D camera = { 0 };

    camera.target = Vector2{ (float)snakeHeadPos.x, (float)snakeHeadPos.y };
    camera.offset = Vector2 { 800.0f / 2.0f, 600.0f / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    BeginMode2D(camera);

        for (size_t i = 0; i < objects.size(); i++) {
            int x = objects[i].getPosition().x;
            int y = objects[i].getPosition().y;

            if (objects[i].getType() == APPLE) DrawCircle(x, y, APPLE_SIZE / 2, RED);
            else if (objects[i].getType() == EAGLE) {
                Vector2 v1 = { (float)x, (float)y - (EAGLE_SIZE / 2) };
                Vector2 v2 = { (float)x - (EAGLE_SIZE / 2), (float)y + (EAGLE_SIZE / 2) };
                Vector2 v3 = { (float)x + (EAGLE_SIZE / 2), (float)y + (EAGLE_SIZE / 2) };
                DrawTriangle(v1, v2, v3, BLACK);
            }
        }

        for (const Position& snakeBodyNode : snakeBody) {
            if (snakeBodyNode.x == snakeHeadPos.x && snakeBodyNode.y == snakeHeadPos.y) continue;
            DrawCircle(snakeBodyNode.x, snakeBodyNode.y, SNAKE_SIZE / 2, LIME);
        }
        DrawCircle(snakeHeadPos.x, snakeHeadPos.y, SNAKE_SIZE / 2, DARKGREEN);
    EndMode2D();

    DrawText(TextFormat("SCORE: %d", state.getScore()), 20, 20, 20, DARKGRAY);
    DrawFPS(700, 20);

    if (!state.isPlaying() && !state.isGameOver()){
        DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.4f));
        DrawText("[SNAKE GAME]", 280, 220, 40, LIME);
        DrawText("PRESS ENTER TO PLAY", 240, 320, 22, WHITE);
    }

    if (state.isPaused() == true && state.isGameOver() == false) {
        DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.4f));
        DrawText("[PAUSED]", 280, 220, 40, LIME);
        DrawText("PRESS P TO RESUME", 240, 320, 22, WHITE);
    }

    if (state.isGameOver()) {
        DrawRectangle(0, 0, 800, 600, Fade(BLACK, 0.6f));
        DrawText("[GAME OVER]", 280, 220, 45, RED);
        DrawText(TextFormat("[FINAL SCORE] -> %d", state.getScore()), 320, 300, 24, WHITE);
        DrawText("[PRESS ENTER TO RESTART]", 240, 370, 22, GOLD);
    }

} 