//
// Created by Gustavo Novais on 27/04/2025.
//
#include "Food.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <Game.h>
#include <iostream>


void Food::render() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(this->center[0], this->center[1]);
    for (int i = 0; i <= NUM_SEGMENTS; i++) {
        float theta = 2.0f * M_PI * float(i) / float(NUM_SEGMENTS);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(this->center[0] + x, this->center[1] + y);
    }
    glEnd();
};

void Food::generateNewPosition(float boardWidth, float boardHeight) {
    // Define novas coordenadas aleatórias dentro do tabuleiro
    vector<int> axes = {(rand() % 3), (rand() % 3)};
    switch (axes[0]) {
        case 0:
            center[0] = (-boardWidth + 2) + (rand() % (int)(boardWidth / 2));
            break;
        case 1:
            center[0] = (boardWidth - 2) - (rand() % (int)(boardWidth / 2));
            break;
        default:
            center[0] = (rand() % (int)(boardWidth-3)) - ( (boardWidth / 2) - 2) ;
    }

    switch (axes[1]) {
        case 0:
            center[1] = (-boardHeight + 2) + (rand() % (int)(boardHeight / 2));
        break;
        case 1:
            center[1] = (boardHeight - 2) - (rand() % (int)(boardHeight / 2));
        break;
        default:
            center[1] = (rand() % (int)(boardHeight-3)) - ( (boardHeight / 2) - 2) ;
    }

    cout << "Food Center: " << this->center[0] << " " << this->center[1] << endl;

    this->eated = false; // A comida não foi comida ainda
}
