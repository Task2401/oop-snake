#ifndef INTERFACE_H
#define INTERFACE_H

class State;

// Handles Raylib window creation and rendering

class Interface {
    public:
        Interface();
        ~Interface();

        void init();                            // Initializes the game window and audio
        void close();                           // Closes the window and frees resources
        void draw_frame(const State& state);    // Renders the current game state to the screen
};

#endif