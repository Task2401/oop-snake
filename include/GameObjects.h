#ifndef GAMEOBJECTS_H
#define GAMEOBJECT_H

#include "Common.h"

enum ObjectType {APPLE, EAGLE};

class GameObject {
    private:
        ObjectType type;
        Position position;
        Direction direction;

    public:
        GameObject(ObjectType type, Position pos, Direction dir);
        ~GameObject();

        ObjectType getType() const;
        Position getPos() const;
        Direction getDi() const;

        void setDirection(Direction dir);
};



#endif