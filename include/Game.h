//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef GAME_CPP_H
#define GAME_CPP_H

#include "Snake.h"
#include "Movement.h"

#include <GLFW/glfw3.h>
#include <vector>
using namespace std;

struct Board {
    float lineWidth = 4.0f;
    float size = 10.0f;
    float zoom = 15.0f;
    vector<vector<float> > board = {
        {size, size},
        {-size, size},
        {-size, -size},
        {size, -size}
    };
};

struct Config {
    bool gameStart = false;
    bool gameOver = false;
};







class Game {
    static Snake snake;

    static Board board;
    static Config config;
    static Movement movement;
    int points = 0;

    static void drawBoard();

public:
    void render();
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    [[nodiscard]] Config getConfig() const {
      return this->config;
    }
};

#endif //GAME_CPP_H
