#include <iostream>
#include <cstdlib>

using namespace std;

#include "../include/GameObjects.h"

GameObject::GameObject (ObjectType t, Position p, Direction dir) : type(t), position(p), direction(dir) {
    cout << "Object -> " << type << " created successfully!" << endl;
}

GameObject::~GameObject() {
    cout << "Object -> " << type << " destroyed successfully!" << endl;
}

ObjectType GameObject::getType() const {
    return type;
}

Position GameObject::getPosition() const {
    return position;
}

Direction GameObject::getDirection() const {
    return direction;
}

void GameObject::setPosition(Position newPos) {
    position = newPos;
}

void GameObject::setDirection(Direction newDir) {
    direction = newDir;
}

void GameObject::move() {
    ObjectType obj = getType();

    if ( obj == APPLE) return;
    
    Position objPos = getPosition();
    Direction objDir = getDirection();

    switch (objDir) {
        case UP: objPos.y -= 1; break;
        case DOWN: objPos.y += 1; break;
        case RIGHT: objPos.x += 1; break;
        case LEFT: objPos.x -= 1; break;
    }

    position = objPos;
}