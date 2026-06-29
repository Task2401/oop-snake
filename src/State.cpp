#include <iostream>
#include <cmath>
#include <cstdlib>

#include "../include/State.h"

using namespace std;

static int randi(int min, int max) {
    return  min + rand() % (max - min + 1);
}

static float randf() {
    return (float)rand() / (float)RAND_MAX;
}

static Position getRandomPosition(Position center) {
    return Position{ center.x + randi(-40, 40), center.y + randi(-40, 40) };
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

void State::setKeys(Keystates currentKeys) {
    keys = currentKeys;
}


void State::addObject(const GameObject& obj) {
    objects.push_back(obj);
}

void State::update() {
    Position headPos = snake.getHeadPos();
    Direction headDir = snake.getSnakeDiretion();
    list<Position> snakeBody = snake.getSnakeBody();

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

    frameCounter++;

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

        headPos = snake.getHeadPos();
        snakeBody = snake.getSnakeBody();

        int appleCount = 0;
        int eagleCount = 0;

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == APPLE) appleCount++;
            else if (objects[i].getType() == EAGLE) eagleCount++;
        }

        while (eagleCount < MAX_EAGLE_COUNT) {
            Position randomPos = getRandomPosition(headPos);
            GameObject eagle = GameObject(EAGLE, randomPos, (Direction)randi(0, 3));
            addObject(eagle);
            eagleCount++;
        }

        while (appleCount < MAX_APPLE_COUNT) {
            Position randomPos = getRandomPosition(headPos);
            GameObject apple = GameObject(APPLE, randomPos, UP);
            addObject(apple);
            appleCount++;
        }

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == EAGLE) {
                if(randf() < EAGLE_NEXT_DIRECTION_PROBABILITY) 
                    objects[i].setDirection((Direction)randi(0, 3));
                objects[i].move();
            }
        }

        bool appleEaten = false;
        int appleIndex = -1;

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == EAGLE && calculateDistance(headPos, objects[i].getPosition()) == 0)
                gameOver = true;
            else if (objects[i].getType() == APPLE && calculateDistance(headPos, objects[i].getPosition()) == 0) {
                appleEaten = true;
                appleIndex = i;
                score++;
            }
            for (const Position& snakeNode : snakeBody) {
                if (objects[i].getType() == EAGLE && calculateDistance(snakeNode, objects[i].getPosition()) == 0) 
                    gameOver = true;
            }        
        }

        size_t nodeCounter = 0;

        for (const Position& snakeNode : snakeBody) {
            nodeCounter++;
            if (nodeCounter == snakeBody.size()) break;
            if (calculateDistance(snakeNode, headPos) == 0) gameOver = true;
        }
        
        if (appleEaten == true) {
            objects.erase(objects.begin() + appleIndex);
            Position newSnakeNode = snakeBody.front();
            snakeBody.push_front(newSnakeNode);
            snake.setSnakeBody(snakeBody);
        }
    }
}
