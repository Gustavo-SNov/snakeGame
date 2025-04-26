//
// Created by Gustavo Novais on 26/04/2025.
//
#include "Game.h"

#include <iostream>
#include <ostream>

#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <GL/gl.h>

Snake Game::snake;
Board Game::board;
Config Game::config;
Movement Game::movement;


void Game::render() {
    drawBoard();
    double currentTime = glfwGetTime();
    if (currentTime >= 1.0) {
        snake.setMovement(movement);
    }

    glPushMatrix();
    glTranslatef(movement.movX, movement.movY, 0.0f);
    snake.render();
    glPopMatrix();
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
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                if (snake.getDirection() != Direction::UP) {
                    snake.setDirection(Direction::UP);
                    movement.movY += movement.speed;
                }
                break;
            case GLFW_KEY_S:
                if (snake.getDirection() != Direction::DOWN) {
                    snake.setDirection(Direction::DOWN);
                    movement.movY -= movement.speed;
                }
                break;
            case GLFW_KEY_D:
                if (snake.getDirection() != Direction::LEFT) {
                    snake.setDirection(Direction::LEFT);
                    movement.movX += movement.speed;
                }
                break;
            case GLFW_KEY_A:
                if (snake.getDirection() != Direction::RIGHT) {
                    snake.setDirection(Direction::RIGHT);
                    movement.movX -= movement.speed;
                }
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        config.gameStart = snake.getDirection() != Direction::NONE;
    }
}
