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
int Game::points = 0;

void Game::render() {
    drawBoard();
    double currentTime = glfwGetTime();
    if (currentTime >= config.timeSpeed && config.gameStart) {
        snake.moveSnake(config.gameSpeed);
        glfwSetTime(0.0f);
    }

    if (!food.isEated()) {
        food.render();
    }

    snake.render();

    if (snakeEatedFood()) {
        food.setEated(true);
        food.generateNewPosition(board.width, board.height);
        snake.growBody();
        moreSpeed();
    }

    if (snake.verifyCollision(board.width, board.height)) {
        config.gameOver = true;
        return;
    }
}

void Game::drawBoard() {
    glLineWidth(board.lineSize);
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (auto &b: board.board) {
        glVertex2f(b[0], b[1]);
    }
    glEnd();
}

void Game::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                if (snake.getDirection() != Direction::DOWN) {
                    snake.setDirection(Direction::UP);
                    //movement.movY += movement.speed;
                }
                break;
            case GLFW_KEY_UP:
                if (snake.getDirection() != Direction::DOWN) {
                    snake.setDirection(Direction::UP);
                    //movement.movY += movement.speed;
                }
                break;
            case GLFW_KEY_S:
                if (snake.getDirection() != Direction::UP) {
                    snake.setDirection(Direction::DOWN);

                    //movement.movY -= movement.speed;
                }
                break;
            case GLFW_KEY_DOWN:
                if (snake.getDirection() != Direction::UP) {
                    snake.setDirection(Direction::DOWN);
                    //movement.movY += movement.speed;
                }
                break;
            case GLFW_KEY_D:
                if (snake.getDirection() != Direction::LEFT) {
                    snake.setDirection(Direction::RIGHT);

                    //movement.movX += movement.speed;
                }
                break;
            case GLFW_KEY_RIGHT:
                if (snake.getDirection() != Direction::LEFT) {
                    snake.setDirection(Direction::RIGHT);

                    //movement.movX += movement.speed;
                }
                break;
            case GLFW_KEY_A:
                if (snake.getDirection() != Direction::RIGHT) {
                    snake.setDirection(Direction::LEFT);

                    //movement.movX -= movement.speed;
                }
                break;
            case GLFW_KEY_LEFT:
                if (snake.getDirection() != Direction::RIGHT) {
                    snake.setDirection(Direction::LEFT);

                    //movement.movX -= movement.speed;
                }
            break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        //ssnake.moveSnake(config.gameSpeed);
        config.gameStart = snake.getDirection() != Direction::NONE;
    }
}

bool Game::snakeEatedFood() {
    Body snakeHead = snake.getHead(); // você precisaria ter isso
    Movement movement = snakeHead.movement;
    vector<float> foodCenter = food.getCenter(); // getter da posição da comida
    int i = 1;
    vector headCenter = {0.0f, 0.0f};
    for (auto &v: snakeHead.vertices) {
        headCenter[0] += (v[0] + movement.movX);
        headCenter[1] += (v[1] + movement.movY);
    }

    headCenter[0] = headCenter[0] / 4;
    headCenter[1] = headCenter[1] / 4;
    //cout << "Head Center: " << headCenter[0] << " " << headCenter[1] << endl;
    //cout << "Food Center: " << foodCenter[0] << " " << foodCenter[1] << endl;

    if (headCenter[0] == foodCenter[0] && headCenter[1] == foodCenter[1]) {
        return true;
    }
    return false;
}

void Game::resetGame() {
    board = Board();
    config = Config();
    movement = Movement();
    snake = Snake();
    food = Food();
    points = 0;
}
