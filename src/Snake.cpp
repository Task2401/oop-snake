#include <iostream>
#include <cstdlib>

using namespace std;

#include "../include/Snake.h"

// Constructor: Initializes direction and starting body segments

Snake::Snake(Direction dir):direction(dir) {
    body.push_back(Position{6, 5});
    body.push_back(Position{7, 5});

    cout << "Snake is created successfully!" << endl;
}

// Destructor

Snake::~Snake() {
    cout << "Snake destroyed successfully!";
}

// Getters & Setters of the class Snake

Direction Snake::getSnakeDiretion() const {
    return direction;
}

Position Snake::getHeadPos() const {
    return body.back(); // Head is always the last element in the list
}

const list<Position> Snake::getSnakeBody() const {
    return body;
}

void Snake::setSnakeBody(const std::list<Position>& newBody) {
    body = newBody; 
}

void Snake::setDirection(Direction newDir) {
    direction = newDir;
}

// Moves the snake forward by shifting positions

void Snake::move() {
    Position newHead = getHeadPos();
    Direction dir = getSnakeDiretion();

    // Calculate new head coordinates based on direction

    switch (dir) {
        case UP: newHead.y -= 8; break;
        case DOWN: newHead.y += 8; break;
        case RIGHT: newHead.x += 8; break;
        case LEFT: newHead.x -= 8; break;
    }

    // Advance snake movement by adding new head and removing old tail segment

    body.push_back(newHead);
    body.pop_front();
}


