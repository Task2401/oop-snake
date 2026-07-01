#ifndef SNAKE_H
#define SNAKE_H

#include <list>

#include "Common.h"

// Main class for the snake

class Snake {
    private:
        std::list<Position> body;      // List of positions representing the snake's body segments
        Direction direction;           // Current movement direction of the snake

    public:
        Snake(Direction dir);
        ~Snake();

        // class Snake gatters

        Position getHeadPos() const; 
        Direction getSnakeDiretion() const;            
        const std::list<Position> getSnakeBody() const;

        // class Snake setters

        void setSnakeBody(const std::list<Position>& newBody);
        void setDirection(Direction newDir);

        //  Snake movement function

        void move();
};

#endif