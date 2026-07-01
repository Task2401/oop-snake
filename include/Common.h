#ifndef COMMON_H
#define COMMON_H

// Directions for the snake and game objects

enum Direction {LEFT, RIGHT, UP, DOWN};

// 2D coordinates for grid positioning

struct Position {
    int x;
    int y;
};

#endif