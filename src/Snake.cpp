#define EPSILON 0.001f // float com margem de erro
#include "Snake.h"
#include <vector>
#include <algorithm>
#include <Game.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
using namespace std;

float Snake::size = 1.0f;

Snake::Snake() {
    this->body.emplace_back(Body{
        {
            {-0.5f, 0.5f}, // A
            {0.5f, 0.5f}, // B
            {0.5f, -0.5f}, // C
            {-0.5f, -0.5f} // D
        },
        Movement(), // posição da cabeça
        Direction::NONE,
        true

    });

    // A B
    // D C

    this->direction = NONE;
}

void Snake::render() {
    for (auto &b: this->body) {
        glPushMatrix();
        glTranslatef(b.movement.movX, b.movement.movY, 0.0f);
        glBegin(GL_QUADS);
        glColor3f(0.0, 1.0, 0.0);
        for (auto v: b.vertices) {
            glVertex2f(v[0], v[1]);
        }
        glEnd();
        glPopMatrix();
    }
}

void Snake::moveSnake(float speed) {
    auto &head = body[0];
    vector<vector<float> > oldHeadPoints = head.vertices;
    Movement oldMovement = head.movement;
    switch (this->direction) {
        case UP:
            head.movement.movY += speed;
            break;
        case DOWN:
            head.movement.movY -= speed;
            break;
        case LEFT:
            head.movement.movX -= speed;
            break;
        case RIGHT:
            head.movement.movX += speed;
            break;
        default:
            break;
    }
    for (int i = 1; i < body.size(); ++i) {
        vector<vector<float> > tempVertices = body[i].vertices;
        Movement tempMovement = body[i].movement;

        body[i].vertices = oldHeadPoints;
        body[i].movement = oldMovement;

        oldHeadPoints = tempVertices;
        oldMovement = tempMovement;
    }
}

void Snake::growBody() {
    Body tail = this->body.back();
    Body newTail = Body();
    float x = 0.0f, y = 0.0f;
    switch (this->direction) {
        case UP:
            y = -size;
            break;
        case DOWN:
            y = size;
            break;
        case LEFT:
            x = -size;
            break;
        case RIGHT:
            x = size;
            break;
        default:
            return;
    }
    cout << "Vertices: " << endl;

    for (auto &v: tail.vertices) {
        vector<float> newVertices = {v[0] + x, v[1] + y};
        newTail.vertices.push_back(newVertices);
    }
    newTail.isHead = false;
    //newTail.movement = Movement();
    newTail.movement = tail.movement;
    newTail.direction = NONE;

    this->body.emplace_back(newTail);
}


bool Snake::verifyCollision(float widthLimit, float heigthLimit) const {
    Body head = getHead();
    vector<float> headCenter = getCenter(head);

    if (headCenter[0] > widthLimit || headCenter[0] < -widthLimit
        || headCenter[1] > heigthLimit || headCenter[1] < -heigthLimit) {
        cout << "Colidiu Borda" << endl;
        cout << "Head Center: " << headCenter[0] << " " << headCenter[1] << endl;
        cout << "Centro Head  ( " << widthLimit << ", " << heigthLimit << " )" << endl;
        return true;
    }

    for (int i = 4; i < body.size(); ++i) { // Começa do 1 para ignorar a cabeça
        vector<float> segmentCenter = getCenter(body[i]);

        if (abs(headCenter[0] - segmentCenter[0]) < EPSILON &&
            abs(headCenter[1] - segmentCenter[1]) < EPSILON) {
            cout << "Colidiu com corpo!" << endl;
            return true;
            }
    }

    return false;
}
