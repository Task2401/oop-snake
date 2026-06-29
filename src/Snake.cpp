#include <iostream>
#include <cstdlib>

using namespace std;

#include "../include/Snake.h"

Snake::Snake(Direction dir):direction(dir) {
    body.push_back(Position{6, 5});
    body.push_back(Position{7, 5});

    cout << "Snake is created successfully!" << endl;
}

Snake::~Snake() {
    cout << "Snake destroyed successfully!";
}

Direction Snake::getSnakeDiretion() const {
    return direction;
}

Position Snake::getHeadPos() const {
    return body.back();
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

void Snake::move() {
    Position newHead = getHeadPos();
    Direction dir = getSnakeDiretion();

    switch (dir) {
        case UP: newHead.y -= 1; break;
        case DOWN: newHead.y += 1; break;
        case RIGHT: newHead.x += 1; break;
        case LEFT: newHead.x -= 1; break;
    }

    body.push_back(newHead);
    body.pop_front();
}


