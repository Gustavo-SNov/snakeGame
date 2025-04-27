//
// Created by Gustavo Novais on 26/04/2025.
//
#include "Snake.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
using namespace std;

float Snake::size = 1.0f;

Snake::Snake() {
    this->body.emplace_back(Body{
        {{-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}},
        Movement(), // posição da cabeça
        Direction::NONE,
        true
    });

    this->body.emplace_back(Body{
        {{-0.5f, 0.5f-size}, {0.5f, 0.5f-size}, {0.5f, -0.5f-size}, {-0.5f, -0.5f-size}},
        Movement(), // posição atrás da cabeça no eixo X
        Direction::NONE,
        false
    });

    this->direction = NONE;
}

void Snake::render() {
    for (auto &b: this->body) {
        glPushMatrix();
        glTranslatef(b.movement.movX, b.movement.movY, 0.0f);
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        for (auto v: b.vertices) {
            glVertex2f(v[0], v[1]);
        }
        glEnd();
        glPopMatrix();
    }
}

void Snake::moveSnake(float speed, vector<float>& foodCenter) {

    auto &head = body[0];
    vector<vector<float>> oldHeadPoints = head.vertices;
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
        vector<vector<float>> tempVertices = body[i].vertices;
        Movement tempMovement = body[i].movement;

        body[i].vertices = oldHeadPoints;
        body[i].movement = oldMovement;

        oldHeadPoints = tempVertices;
        oldMovement = tempMovement;
    }
}

void Snake::growBody() {
    Body newTail = this->body.back();
    switch (newTail.direction) {
        case UP:
            for (auto &v: newTail.vertices) {
                v[1] -= size;
            }
            break;
        case DOWN:
            for (auto &v: newTail.vertices) {
                v[1] += size;
            }
            break;
        case LEFT: for (auto &v: newTail.vertices) {
                v[0] += size;
            }

            break;
        case RIGHT:
            for (auto &v: newTail.vertices) {
                v[0] -= size;
            }
            break;
        case NONE:
            break;
    }

    this->body.emplace_back(newTail);
}


bool Snake::verifyCollision(float limitMax, float limitMin, float x, float y) {
    Body head = this->body[0];

    for (auto v: head.vertices) {
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
