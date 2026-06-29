#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "../include/State.h"

using namespace std;

static int randi(int min, int max) {
    return  min + rand() % (max - min + 1);
}

static float randf() {
    return (float)rand() / (float)RAND_MAX;
}

static Position getRandomPosition() {
    return Position{ randi(0, 29), randi(0,29) };
}

static int  calculateDistance(Position p1, Position p2) {
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return dx + dy;
}

State::State() : snake(RIGHT), score(0), frameCounter(0), gameOver(false), playing(false), paused(false), keys{false, false, false, false, false, false} {
    cout << "State created succesfully!" << endl;
}

State::~State() {
    cout << "State destroyed succesfully!" << endl;
}

const Snake& State::getSnake() const {
    return snake;
}

const std::vector<GameObject>& State::getObjects() const {
    return objects;
}

int State::getScore() const {
    return score;
}

bool State::isGameOver() const {
    return gameOver;
}

bool State::isPlaying() const {
    return playing;
}

bool State::isPaused() const {
    return paused;
}

void State::addObject(const GameObject& obj) {
    objects.push_back(obj);
}

void State::update() {
    Position headPos = snake.getHeadPos();
    Direction headDir = snake.getSnakeDiretion();
    list<Position> body = snake.getSnakeBody();
    frameCounter++;

    if (playing == false) {
        if (keys.start == true) {
            playing = true;
            keys.start = false;
        }
        return;
    }

    if (gameOver) {
        if (keys.start) {
            score = 0;
            frameCounter = 0;
            gameOver = false;
            paused = false;
            playing = true;
            snake = Snake(RIGHT);
            objects.clear();
            keys.start = false;
        }
        return;
    }

    if (keys.pause) {
        paused = !paused;
        keys.pause = false;
    }

    if (paused) return;


    if (frameCounter % FRAMES_PER_STATE == 0) {
        
        if (keys.up && headDir != DOWN)
            snake.setDirection(UP);

        else if (keys.down && headDir != UP)
            snake.setDirection(DOWN);

        else if (keys.left && headDir != RIGHT)
            snake.setDirection(LEFT);

        else if (keys.right && headDir != LEFT)
            snake.setDirection(RIGHT);

        snake.move();

        int appleCount = 0;
        int eagleCount = 0;

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == APPLE) appleCount++;
            else if (objects[i].getType() == EAGLE) eagleCount++;
        }

        while (eagleCount < MAX_EAGLE_COUNT) {
            Position randomPos = getRandomPosition();
            GameObject eagle = GameObject(EAGLE, randomPos, (Direction)randi(0, 3));
            addObject(eagle);
        }

        while (appleCount < MAX_APPLE_COUNT) {
            Position randomPos = getRandomPosition();
            GameObject apple = GameObject(APPLE, randomPos, UP);
            addObject(apple);
        }

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == EAGLE) {
                if(randf() < EAGLE_NEXT_DIRECTION_PROBABILITY) 
                    objects[i].setDirection((Direction)randi(0, 3));
                objects[i].move();
            }
        }
    }
}
