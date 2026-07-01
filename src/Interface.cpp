#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

#include "raylib.h"
#include "../include/State.h"
#include "../include/Interface.h"

// Constructor

Interface::Interface() {
    cout << "Interface created successfully!" << endl;
}

// Destructor

Interface::~Interface() {
    cout << "Interface destroyed successfully!" << endl;
}

// Opens and configures the Raylib window setup

void Interface::init() {
    int screenWidth = 800;
    int screenHight = 600;
    int gameFps = 60;
    
    InitWindow(screenWidth, screenHight, "Snake Game by Task2401");
    SetTargetFPS(gameFps);

    // Load and apply window taskbar icon

    Image gameIcon = LoadImage("assets/game_icon.png");
    
    ImageResize(&gameIcon, 32, 32);
    SetWindowIcon(gameIcon);
    UnloadImage(gameIcon);

    cout << "Window opened and configured successfully via init()!" << endl;
}

// Terminates window and context resources

void Interface::close() {
    CloseWindow();
    cout << "Window closed successfully via close()!" << endl;
}

// Core rendering system function

void Interface::draw_frame(const State& state) {
    ClearBackground(LIGHTGRAY);

    float snakeRadius = SNAKE_SIZE / 2;
    float appleRadius = APPLE_SIZE / 2;
    float eagleRadius = EAGLE_SIZE / 2;

    const auto& objects = state.getObjects();
    const auto& snake = state.getSnake();
    const auto& snakeBody = snake.getSnakeBody();
    Position snakeHeadPos = snake.getHeadPos();
   
    // Camera Viewport Lock (Tracks snake head position)

    Camera2D camera = { 0 };
    camera.target = Vector2{ (float)snakeHeadPos.x, (float)snakeHeadPos.y };
    camera.offset = Vector2 { 800.0f / 2.0f, 600.0f / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    BeginMode2D(camera);

        // Render external game objects (Apples & Eagles)

        for (size_t i = 0; i < objects.size(); i++) {
            int x = objects[i].getPosition().x;
            int y = objects[i].getPosition().y;

            if (objects[i].getType() == APPLE) DrawCircle(x, y, appleRadius, RED);
            else if (objects[i].getType() == EAGLE) {
                Vector2 v1 = { (float)x, (float)y - eagleRadius };
                Vector2 v2 = { (float)x - eagleRadius, (float)y + eagleRadius }; 
                Vector2 v3 = { (float)x + eagleRadius, (float)y + eagleRadius };
                DrawTriangle(v1, v2, v3, BLACK);
            }
        }

        // Render full snake body nodes (Lime segments, Dark Green head)

        for (const Position& snakeBodyNode : snakeBody) {
            if (snakeBodyNode.x == snakeHeadPos.x && snakeBodyNode.y == snakeHeadPos.y) continue;
            DrawCircle(snakeBodyNode.x, snakeBodyNode.y, snakeRadius, LIME);
        }
        DrawCircle(snakeHeadPos.x, snakeHeadPos.y, snakeRadius, DARKGREEN);
    
    EndMode2D();

    // HUD Rendering (Score overlay display)

    DrawText(TextFormat("SCORE: %d", state.getScore()), 20, 20, 20, DARKGRAY);
    DrawFPS(700, 20);

    int screenWidth = 800;
    int screenHeight = 600;

    // UI Layer: Main Menu Overlay

    if (!state.isPlaying() && !state.isGameOver()){
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.75f));
        
        string title = "[SNAKE GAME]";
        string subTitle = "PRESS ENTER TO PLAY";
        
        int titleX = (screenWidth / 2) - (MeasureText(title.c_str(), 45) / 2);
        int subTitleX = (screenWidth / 2) - (MeasureText(subTitle.c_str(), 24) / 2);

        DrawText(title.c_str(), titleX, 220, 45, GOLD);
        DrawText(subTitle.c_str(), subTitleX, 320, 24, ORANGE);
    }

    // UI Layer: Active Gameplay Pause Overlay

    if (state.isPaused() == true && state.isGameOver() == false) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.75f));
        
        string pauseTitle = "[PAUSED]";
        string pauseSub = "PRESS P TO RESUME";

        int pauseTitleX = (screenWidth / 2) - (MeasureText(pauseTitle.c_str(), 45) / 2);
        int pauseSubX = (screenWidth / 2) - (MeasureText(pauseSub.c_str(), 24) / 2);

        DrawText(pauseTitle.c_str(), pauseTitleX, 220, 45, SKYBLUE);
        DrawText(pauseSub.c_str(), pauseSubX, 320, 24, WHITE);
    }

    // UI Layer: Game Over Window Reset Screen

    if (state.isGameOver()) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.85f));
        
        string gameOverTitle = "[GAME OVER]";
        string finalScoreText = "FINAL SCORE -> " + to_string(state.getScore());
        string restartText = "PRESS ENTER TO RESTART";

        int goX = (screenWidth / 2) - (MeasureText(gameOverTitle.c_str(), 50) / 2);
        int fsX = (screenWidth / 2) - (MeasureText(finalScoreText.c_str(), 26) / 2);
        int rtX = (screenWidth / 2) - (MeasureText(restartText.c_str(), 24) / 2);

        DrawText(gameOverTitle.c_str(), goX, 220, 50, RED);
        DrawText(finalScoreText.c_str(), fsX, 300, 26, WHITE);
        DrawText(restartText.c_str(), rtX, 370, 24, GOLD);
    }
}