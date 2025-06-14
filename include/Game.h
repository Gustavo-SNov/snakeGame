//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef GAME_CPP_H
#define GAME_CPP_H

#include <algorithm>
#include <GLFW/glfw3.h>
#include <vector>

#include "Snake.h"
#include "Food.h"
#include "struct/Movement.h"

using namespace std;

struct Board {
    float lineSize = 4.0f;
    float height = 20.0f;
    float width = 20.0f;
    float size = 20.0f;
    vector<vector<float> > board = {
        {width, height},
        {-width, height},
        {-width, -height},
        {width, -height}
    };
};

struct Config {
    bool gameStart = false;
    bool gameOver = false;
    float gameSpeed = 1.0f;
    float timeSpeed = 0.08f;
};

class Game {
    static Snake snake;
    static Food food;
    static Board board;
    static Config config;
    static Movement movement;
    static int points;

    static void drawBoard();

public:
    void render();
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static bool snakeEatedFood();
    static void resetGame();
    static void drawScore();
    static void drawRank();
    [[nodiscard]] static Config getConfig() {
      return config;
    }
    static int getPoints() {
        return static_cast<int>(snake.getBody().size()-1);
    }
    static void moreSpeed() {
        config.timeSpeed -= 0.005f;
    }

};

#endif //GAME_CPP_H
