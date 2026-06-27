#ifndef SNAKE_H
#define SNAKE_H

#include <list>

#include "Common.h"

class Snake {
    private:
        std::list<Position> body;
        Direction direction;

    public:
        Snake(Direction dir);
        ~Snake();

        Direction getSnakeDiretion() const;
        Position getHeadPos() const;
        const std::list<Position> getSnakeBody() const;

        void move();
        void setDirection(Direction dir);
};

#endif