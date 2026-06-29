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

        void setSnakeBody(const std::list<Position>& newBody);
        void setDirection(Direction newDir);

        void move();
};

#endif