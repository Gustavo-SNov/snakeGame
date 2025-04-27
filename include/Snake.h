//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Body.h"
#include "Movement.h"
#include <vector>
using namespace std;


class Snake {

    int bodySize = 1;
    static float size;
    vector<Body> body;
    Direction direction;

    public:
        explicit Snake();
        void render();
        bool verifyCollision(float limitMax, float limitMin, float x, float y);
        void moveSnake(float speed, vector<float>& foodCenter);
        void growBody();
        [[nodiscard]] vector<Body> getBody() const {
            return this->body;
        }
        [[nodiscard]] Direction getDirection() const {
            return this->direction;
        }
        [[nodiscard]] Body getHead() const {
            return this->body[0];
        }
        void setDirection(const Direction& direction) {
            this->direction = direction;
        }



};
#endif //SNAKE_H
