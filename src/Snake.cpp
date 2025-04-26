//
// Created by Gustavo Novais on 26/04/2025.
//
#include "Snake.h"
#include <vector>
#include <GLFW/glfw3.h>
using namespace std;

Snake::Snake() {
    this->head = {
        {0.0f, 0.0f},
        {size, 0.0f},
        {size, size},
        {0.0f, size}
    };
    this->direction = NONE;
}

void Snake::render() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    for (auto i: this->head) {
        glVertex2f(i[0], i[1]);
    }
    glEnd();
}

void Snake::setMovement(Movement& movement) {
    switch (this->direction) {
        case UP:
            movement.movY += movement.speed;
            break;
        case DOWN:
            movement.movY -= movement.speed;
            break;
        case LEFT:
            movement.movX += movement.speed;
            break;
        case RIGHT:
            movement.movX -= movement.speed;
            break;
        case NONE:
            break;
    }
}

bool Snake::verifyCollision(float limitMax, float limitMin, float x, float y) {
    for (auto v: this->head) {
        float limitX = v[0] + x;
        float limitY = v[1] + y;
        if (limitX > limitMax || limitX < limitMin) {
            return true;
        }
        if (limitY > limitMax || limitY < limitMin) {
            return true;
        }
    }
    return false;
}
