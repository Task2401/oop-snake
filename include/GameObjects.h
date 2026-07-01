#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "Common.h"

enum ObjectType {APPLE, EAGLE};

class GameObject {
    private:
        ObjectType type;            // Object type identifier (Apple or Eagle)
        Position position;          // Current map coordinates
        Direction direction;        // Movement direction vector

    public:
        GameObject(ObjectType type, Position pos, Direction dir);
        ~GameObject();

        // Getters

        ObjectType getType() const;
        Position getPosition() const;
        Direction getDirection() const;

        // Setters

        void setPosition(Position newPos);
        void setDirection(Direction dir);
        
        // Object movement function

        void move();    // Updates position for moving objects
};

#endif