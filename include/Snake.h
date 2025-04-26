//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Movement.h"
#include <vector>
using namespace std;


enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NONE
};

class Snake {
  float size = 1.0f;
  vector<vector<float>> head;
  vector<vector<float>> body;
  Direction direction;

  public:
    explicit Snake();
    void render();
    bool verifyCollision(float limitMax, float limitMin, float x, float y);
    void setMovement(Movement& movement);
    vector<vector<float>> getHead() {
        return head;
    }
    [[nodiscard]] Direction getDirection() const {
        return this->direction;
    }
    void setDirection(const Direction& direction) {
        this->direction = direction;
    }

};
#endif //SNAKE_H
