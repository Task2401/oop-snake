#ifndef STATE_H
#define STATE_H

#include <vector>

#include "Common.h"
#include "Snake.h"
#include "GameObjects.h"


#define SNAKE_SIZE 20
#define EAGLE_SIZE 30
#define APPLE_SIZE 30
#define FRAMES_PER_STATE 4
#define MAX_EAGLE_COUNT 5
#define MAX_APPLE_COUNT 5
#define EAGLE_NEXT_DIRECTION_PROBABILITY 0.25

struct Keystates {
    bool up;
    bool down;
    bool left;
    bool right;
    bool pause;
    bool start;
};

class State {
    private:
        Snake snake;
        Keystates keys;
        std::vector<GameObject> objects;
        int score;
        int frameCounter;
        bool gameOver;
        bool isPaused;

    public:
        State();
        ~State();

        void addObject(const std::vector<GameObject>& obj);
        void update();

        const Snake& getSnake() const;
        const std::vector<GameObject>& getObjects() const;
        int getScore() const;
        bool isGameOver() const;

};
#endif