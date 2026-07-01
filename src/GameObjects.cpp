#include <iostream>
#include <cstdlib>

using namespace std;

#include "../include/GameObjects.h"

// Constructor: Initializes type, position, and direction

GameObject::GameObject (ObjectType t, Position p, Direction dir) : type(t), position(p), direction(dir) {
    cout << "Object -> " << type << " created successfully!" << endl;
}

// Destructor

GameObject::~GameObject() {
    cout << "Object -> " << type << " destroyed successfully!" << endl;
}

// Setters & Getters of the class GameObject

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

// Updates position for moving entities (Eagles)

void GameObject::move() {
    ObjectType obj = getType();

    if ( obj == APPLE) return;
    
    Position objPos = getPosition();
    Direction objDir = getDirection();

    // Calculate next coordinates based on object's direction

    switch (objDir) {
        case UP: objPos.y -= 4; break;
        case DOWN: objPos.y += 4; break;
        case RIGHT: objPos.x += 4; break;
        case LEFT: objPos.x -= 4; break;
    }

    position = objPos;
}