//
// Created by Gustavo Novais on 26/04/2025.
//
#include "Game.h"

#include <iostream>
#include <Renderer.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
using namespace std;

Snake Game::snake;
Food Game::food = Food();
Board Game::board;
Config Game::config;
Movement Game::movement;


void Game::render() {
    drawBoard();
    // double currentTime = glfwGetTime();
    // if (currentTime >= 1.0) {
    //     snake.moveSnake(config.gameSpeed);
    // }

    //glPushMatrix();
    //glTranslatef(movement.movX, movement.movY, 0.0f);
    if (!food.isEated()) {
        food.render();
    }

    snake.render();

    if (snakeEatedFood()) {
        cout << "Eated Food" << endl;
        food.setEated(true);
    }
    //glPopMatrix();
    if (snake.verifyCollision(board.size, -board.size, movement.movX, movement.movY)) {
        //cout << "Tempo: " << currentTime;
        config.gameOver = true;
    }
}

void Game::drawBoard() {
    glLineWidth(board.lineWidth);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (auto &b: board.board) {
        glVertex2f(b[0], b[1]);
    }
    glEnd();
}

void Game::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    bool changeDirection = false;
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                if (snake.getDirection() != Direction::UP) {
                    snake.setDirection(Direction::UP);
                    changeDirection = true;
                    //movement.movY += movement.speed;
                }
                break;
            case GLFW_KEY_S:
                if (snake.getDirection() != Direction::DOWN) {
                    snake.setDirection(Direction::DOWN);
                    changeDirection = true;
                    //movement.movY -= movement.speed;
                }
                break;
            case GLFW_KEY_D:
                if (snake.getDirection() != Direction::RIGHT) {
                    snake.setDirection(Direction::RIGHT);
                    changeDirection = true;
                    //movement.movX += movement.speed;
                }
                break;
            case GLFW_KEY_A:
                if (snake.getDirection() != Direction::LEFT) {
                    snake.setDirection(Direction::LEFT);
                    changeDirection = true;
                    //movement.movX -= movement.speed;
                }
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        snake.moveSnake(config.gameSpeed, food.getCenter());

        config.gameStart = snake.getDirection() != Direction::NONE;
    }
}

bool Game::snakeEatedFood() {
    Body snakeHead = snake.getHead(); // você precisaria ter isso
    Movement movement = snakeHead.movement;
    vector<float> foodCenter = food.getCenter(); // getter da posição da comida
    int i = 1;
    vector<float> headCenter = {0.0f, 0.0f};
    for (auto &v: snakeHead.vertices) {
        headCenter[0] += (v[0] + movement.movX);
        headCenter[1] += (v[1] + movement.movY);
    }

    headCenter[0] = headCenter[0] / 4;
    headCenter[1] = headCenter[1] / 4;
    cout << "Head Center: " << headCenter[0] << " " << headCenter[1] << endl;
    cout << "Food Center: " << foodCenter[0] << " " << foodCenter[1] << endl;

    if (headCenter[0] == foodCenter[0] && headCenter[1] == foodCenter[1]) {
        return true;
    }
    return false;
}
