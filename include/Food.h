//
// Created by Gustavo Novais on 27/04/2025.
//

#ifndef FOOD_H
#define FOOD_H

#include <vector>
using namespace std;

class Food {
    static const int NUM_SEGMENTS = 100;
    float radius;
    vector<float> center;
    bool eated;

public:
    Food() {
        this->radius = 0.5f;
        this->center = {0.0f, 5.0f};
        this->eated = false;
    }

    void render();
    void generateNewPosition(float boardWidth, float boardHeight);

    vector<float> &getCenter() {
        return this->center;
    }

    void setCenter(vector<float> newCenter) {
        this->center = newCenter;
    }

    void setEated(bool newEated) {
        this->eated = newEated;
    }

    void setRadius(float newRadius) {
        this->radius = newRadius;
    }

    bool isEated() const {
        return this->eated;
    }
};


#endif //FOOD_H
