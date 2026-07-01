#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "../include/State.h"
#include "../include/Interface.h"
#include "raylib.h"


int main() {

    // Initialize core game modules

    State state = State();
    Interface interface = Interface();

    // Setup window and graphics context

    interface.init();

    // Main Game Loop

    while (!WindowShouldClose()) {
        Keystates currentKeys;

        // Capture movement inputs (Arrow keys or WASD)

        currentKeys.up = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        currentKeys.down = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
        currentKeys.left = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        currentKeys.right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

        // Capture menu and state trigger inputs

        currentKeys.start = IsKeyPressed(KEY_ENTER);
        currentKeys.pause = IsKeyPressed(KEY_P);

        // Pass inputs to the logic engine

        state.setKeys(currentKeys);

        // Update physics, positioning, and logic rules

        state.update();

        // Render current frame to screen

        BeginDrawing();
            interface.draw_frame(state);
        EndDrawing();
    }

    // Cleanup window context on exit

    interface.close();
    
    return 0;
}