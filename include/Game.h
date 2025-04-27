//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef GAME_CPP_H
#define GAME_CPP_H

#include <GLFW/glfw3.h>
#include <vector>

#include "Snake.h"
#include "Food.h"
#include "struct/Movement.h"

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
    float gameSpeed = 1.0f;
};

class Game {
    static Snake snake;
    static Food food;
    static Board board;
    static Config config;
    static Movement movement;
    int points = 0;

    static void drawBoard();

public:
    void render();
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static bool snakeEatedFood();
    [[nodiscard]] Config getConfig() const {
      return this->config;
    }


};

#endif //GAME_CPP_H
