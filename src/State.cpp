#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "../include/State.h"

using namespace std;

static int randi(int min, int max) {
    return  min + rand() % (max - min + 1);
}

static float randf() {
    return (float)rand() / (float)RAND_MAX;
}

State::State() : snake(RIGHT), score(0), frameCounter(0), gameOver(false), playing(false), paused(false), keys{false, false, false, false, false, false} {
    cout << "State created succesfully!" << endl;
}

State::~State() {
    cout << "State destroyed succesfully!" << endl;
}

const Snake& State::getSnake() const {
    return snake;
}

const std::vector<GameObject>& State::getObjects() const {
    return objects;
}

int State::getScore() const {
    return score;
}

bool State::isGameOver() const {
    return gameOver;
}

bool State::isPlaying() const {
    return playing;
}

bool State::isPaused() const {
    return paused;
}

void State::addObject(const GameObject& obj) {
    objects.push_back(obj);
}

void State::update() {

}
