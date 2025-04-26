#include <iostream>
#include <../include/Renderer.h>
#include <../include/Game.h>
#include <functional>
#include <GLFW/glfw3.h>

using namespace std;

void draw() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}


int main() {

    Game game;
    Renderer renderer;
    renderer.render(game);

    return 0;
}

