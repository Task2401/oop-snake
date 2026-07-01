#include <iostream>
#include <cmath>
#include <cstdlib>

#include "../include/State.h"

using namespace std;

// Generates a random integer between min and max

static int randi(int min, int max) {
    return  min + rand() % (max - min + 1);
}

// Generates a random float between 0.0 and 1.0

static float randf() {
    return (float)rand() / (float)RAND_MAX;
}

// Spawns a random position in a 100-400 pixel radius around a center point

static Position getRandomPosition(Position center) {
    int signX = (rand() % 2 == 0) ? 1 : -1;
    int signY = (rand() % 2 == 0) ? 1 : -1;
    
    return Position{ 
        center.x + (signX * randi(100, 400)), 
        center.y + (signY * randi(100, 400)) 
    };
}

// Calculates Manhattan distance between two points

static int  calculateDistance(Position p1, Position p2) {
    int dx = abs(p1.x - p2.x);
    int dy = abs(p1.y - p2.y);
    return dx + dy;
}

// Constructor -> Initializes game flags and registers

State::State() : 
    snake(RIGHT), 
    keys{false, false, false, false, false, false}, 
    score(0), 
    frameCounter(0), 
    playing(false), 
    gameOver(false), 
    paused(false) 
{
    cout << "State created succesfully!" << endl;
}

// Destructor

State::~State() {
    cout << "State destroyed succesfully!" << endl;
}

// Getters & Setters

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

// This update function is the core of the snake game logic
// because is running in every frame of the game;

void State::update() {
    Position headPos = snake.getHeadPos();
    Direction headDir = snake.getSnakeDiretion();
    list<Position> snakeBody = snake.getSnakeBody();

    // Start screen menu handler

    if (playing == false) {
        if (keys.start == true) {
            playing = true;
            keys.start = false;
        }
        return;
    }

    // Game over reset handler

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

    // Pause input handler

    if (keys.pause) {
        paused = !paused;
        keys.pause = false;
    }

    if (paused) return;

    frameCounter++;

    // Fixed logic tick

    if (frameCounter % FRAMES_PER_STATE == 0) {
        
        // / Process snake direction inputs (preventing 180-degree self-turns)

        if (keys.up && headDir != DOWN)
            snake.setDirection(UP);

        else if (keys.down && headDir != UP)
            snake.setDirection(DOWN);

        else if (keys.left && headDir != RIGHT)
            snake.setDirection(LEFT);

        else if (keys.right && headDir != LEFT)
            snake.setDirection(RIGHT);

        // Advance snake positioning
        
        snake.move();

        // Refresh dynamic positions

        headPos = snake.getHeadPos();
        snakeBody = snake.getSnakeBody();

        // Count existing objects currently on the map

        size_t appleCount = 0;
        size_t eagleCount = 0;

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == APPLE) appleCount++;
            else if (objects[i].getType() == EAGLE) eagleCount++;
        }

         // Procedural generation: Replenish missing eagles

        while (eagleCount < MAX_EAGLE_COUNT) {
            Position randomPos = getRandomPosition(headPos);
            GameObject eagle = GameObject(EAGLE, randomPos, (Direction)randi(0, 3));
            addObject(eagle);
            eagleCount++;
        }

        // Procedural generation: Replenish missing apples

        while (appleCount < MAX_APPLE_COUNT) {
            Position randomPos = getRandomPosition(headPos);
            GameObject apple = GameObject(APPLE, randomPos, UP);
            addObject(apple);
            appleCount++;
        }

        // Run Eagle's self pathfinding updates and movement

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == EAGLE) {
                if(randf() < EAGLE_NEXT_DIRECTION_PROBABILITY) 
                    objects[i].setDirection((Direction)randi(0, 3));
                objects[i].move();
            }
        }

        bool appleEaten = false;
        int appleIndex = -1;

        //  Global Collision Checking

        for (size_t i = 0; i < objects.size(); i++) {
            if (objects[i].getType() == EAGLE) {

                // Eagle vs Snake Head collision

                if ( calculateDistance(objects[i].getPosition(), headPos) < EAGLE_SIZE) gameOver = true;
                
                // Eagle vs Snake Body collision
                
                for (const Position& snakeNode : snakeBody) {
                    
                    // Snake Head vs Apple collision
                    
                    if (calculateDistance(objects[i].getPosition(), snakeNode) < EAGLE_SIZE) {
                        gameOver = true;
                        break;
                    }
                }
            }



            else if (objects[i].getType() == APPLE) {
                
                // Snake Head vs Apple collision

                if (calculateDistance(objects[i].getPosition(), headPos) < APPLE_SIZE) {
                    score++;
                    appleIndex = i;
                    appleEaten = true;
                    break;
                }
            }
        }

        // Snake Self-Collision check (Head vs Body segments)

        size_t snakeNodeCounter = 0;
        
        for (const Position& snakeNode : snakeBody) {
            snakeNodeCounter++;
            if (snakeNodeCounter == snakeBody.size()) break;
            if (calculateDistance(snakeNode, headPos) < 1) gameOver = true;
        }

        //  Handle apple consumption: delete the apple and grow the snake body

        if (appleEaten == true) {
            objects.erase(objects.begin() + appleIndex);
            Position newSnakeNode = snakeBody.front();
            snakeBody.push_front(newSnakeNode);
            snake.setSnakeBody(snakeBody);
        }

        // Memory Management: Despawn far away out-of-bounds objects

        for (int i = (int)objects.size() - 1; i >= 0; i--)
            if (calculateDistance(objects[i].getPosition(), headPos) > 600)
                objects.erase(objects.begin() + i);
    }
}
