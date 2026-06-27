#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <list>

#include "Common.h"

class Snake {
    private:
        std::vector<Position> body;
        Direction direction;

    public:
        Snake();
        ~Snake();

        Direction getSnakeDiretion() const;
        Position getHeadPos() const;
        const std::vector<Position> getSnakeBody() const;

        void move();
        void grow();
        void setDirection(Direction dir);
};

#endif