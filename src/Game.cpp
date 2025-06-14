//
// Created by Gustavo Novais on 26/04/2025.
//
#include "Game.h"

#include <iostream>
#include <Renderer.h>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#define STB_EASY_FONT_IMPLEMENTATION
#include "stb_easy_font.h"
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

void Game::drawScore() {

    glPushMatrix();
    glTranslatef(-20.0f, 30.0f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    glTranslatef(23.0f, -23.0f, 0.0f);
    char text[128];
    snprintf(text, sizeof(text), "Score: %d", getPoints()); // Supondo que você tenha esse campo

    char buffer[99999]; // memória para o texto
    int num_quads = stb_easy_font_print(
        -23,  // posição X (esquerda da tela)
        23,   // posição Y (topo da tela)
        text,
        nullptr,    // cor padrão (branca)
        buffer,
        sizeof(buffer)
    );

    glColor3f(1, 1, 1); // cor branca
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

void Game::drawRank() {
    glPushMatrix();
    // glTranslatef(-20.0f, 30.0f, 0.0f);
    glTranslatef(30.0f, 30.0f, 0.0f);
    glScalef(0.5f, 0.5f, 1.0f);
    glScalef(1.0f, -1.0f, 1.0f);
    // glTranslatef(23.0f, -23.0f, 0.0f);
    char text[128];
    snprintf(text, sizeof(text), "Ranking: "); // Supondo que você tenha esse campo

    char buffer[99999]; // memória para o texto
    int num_quads = stb_easy_font_print(
        -23,  // posição X (esquerda da tela)
        23,   // posição Y (topo da tela)
        text,
        nullptr,    // cor padrão (branca)
        buffer,
        sizeof(buffer)
    );

    glColor3f(1, 1, 1); // cor branca
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}
