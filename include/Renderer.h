//
// Created by Gustavo Novais on 26/04/2025.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <GLFW/glfw3.h>
#include <functional>
#include <Game.h>
using namespace std;

class Renderer {
    static float x;
    static float y;
    static float step;
    static float zoom;

  public:
    static void initialize();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode,int action, int mods);
    //void render(function<void()> draw);
    void render(Game& game);
};

#endif //RENDERER_H
