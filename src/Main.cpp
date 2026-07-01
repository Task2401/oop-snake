#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "../include/State.h"
#include "../include/Interface.h"
#include "raylib.h"


int main() {
    State state = State();
    Interface interface = Interface();

    interface.init();

    while (!WindowShouldClose()) {
        Keystates currentKeys;

        currentKeys.up = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
        currentKeys.down = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
        currentKeys.left = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        currentKeys.right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

        currentKeys.start = IsKeyPressed(KEY_ENTER);
        currentKeys.pause = IsKeyPressed(KEY_P);

        state.setKeys(currentKeys);

        state.update();

        BeginDrawing();
            interface.draw_frame(state);
        EndDrawing();
    }
    interface.close();
    
    return 0;
}