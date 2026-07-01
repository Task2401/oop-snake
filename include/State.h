#ifndef STATE_H
#define STATE_H

#include <vector>

#include "Common.h"
#include "Snake.h"
#include "GameObjects.h"

// Game Constant Values

#define SNAKE_SIZE 20                            // Size of snake segments
#define EAGLE_SIZE 30                            // Size of aagles
#define APPLE_SIZE 30                            // Size of apples
#define FRAMES_PER_STATE 4                       // Logic updates every x frames
#define MAX_EAGLE_COUNT 8                        // Max eagles on map
#define MAX_APPLE_COUNT 7                        // Max apples on map
#define EAGLE_NEXT_DIRECTION_PROBABILITY 0.25    // Eagle's change direction chance

// Keyboard input states

struct Keystates {
    bool up;
    bool down;
    bool left;
    bool right;
    bool pause;
    bool start;
};

// Main class for the state

class State {
    private:
        Snake snake;                        // The snake object
        Keystates keys;                     // Current keyboard inputs
        std::vector<GameObject> objects;    // The vector for apples and eagles
        int score;                          // Current game score
        int frameCounter;                   // Frame counter for game fps
        bool playing;                       // True if playing (game started)
        bool gameOver;                      // True if player lost
        bool paused;                        // True if game is paused

    public:
        State();
        ~State();

        // class State getters

        const Snake& getSnake() const;
        const std::vector<GameObject>& getObjects() const;
        int getScore() const;

        // class State checks

        bool isGameOver() const;
        bool isPlaying() const;
        bool isPaused() const;

        // class State core Functions

        void setKeys(Keystates currentKeys);    // Update input stetes
        void addObject(const GameObject& obj);  // Spawns new object on map
        void update();                          // Runs the core game logic
};
#endif