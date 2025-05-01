#include <iostream>
#include <../include/Renderer.h>
#include <../include/Game.h>
#include <functional>
#include <GLFW/glfw3.h>

using namespace std;

int main() {

    Game game;
    Renderer renderer;
    renderer.render(game);

    return 0;
}

