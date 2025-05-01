//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef SNAKE_H
#define SNAKE_H

#include "Body.h"
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


    bool verifyCollision(float widthLimit, float heigthLimit) const;

    void moveSnake(float speed);

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

    void setDirection(const Direction &direction) {
        this->direction = direction;
    }

    [[nodiscard]] vector<float> getHeadCenter() const {
        Body head = getHead();
        vector headCenter = {0.0f, 0.0f};
        for (auto &v: head.vertices) {
            headCenter[0] += (v[0] + head.movement.movX);
            headCenter[1] += (v[1] + head.movement.movY);
        }

        headCenter[0] = headCenter[0] / 4;
        headCenter[1] = headCenter[1] / 4;
        return headCenter;
    }

    static vector<float> getCenter(const Body& snakePart) {
        vector center = {0.0f, 0.0f};
        for (auto &v: snakePart.vertices) {
            center[0] += (v[0] + snakePart.movement.movX);
            center[1] += (v[1] + snakePart.movement.movY);
        }

        center[0] = center[0] / 4;
        center[1] = center[1] / 4;
        return center;
    }
};
#endif //SNAKE_H
