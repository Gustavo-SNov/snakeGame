
#define STB_EASY_FONT_IMPLEMENTATION

#include "Renderer.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>


using namespace std;

// Em C++, variáveis "static" de classe precisam ser definidas fora da classe também.
float Renderer::x = 0.0f;
float Renderer::y = 0.0f;
float Renderer::step = 1.0f;
float Renderer::zoom = 40.0f;

void Renderer::initialize() {
    // Ajuste de Projeção Ortográfica(2D)
    glMatrixMode(GL_PROJECTION); // Matriz de Projeção: Como a câmera vê a cena
    glLoadIdentity(); // Reseta transformações anteriores
    glOrtho(-zoom, zoom, -zoom, zoom, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, width, height);
}


void Renderer::render(Game& game) {
    // Inicializa a biblioteca GLFW -> Criar Janelas e Gerenciar Contextos
    if (!glfwInit()) {
        cerr << "Erro ao inicializar o GLFW" << endl;
        return;
    }

    // Cria janela 800x600 pixels, com o título "Exemplo - GLFW" sem modo fullscreen(1º nullptr) e sem compartilhamento de contexto com outra janela(2º nullptr)
    GLFWwindow *window = glfwCreateWindow(1200, 800, "Jogo da Cobrinha - GSNOVAUS", nullptr, nullptr);
    if (!window) {
        cerr << "Erro ao criar a janela GLFW" << endl;
        glfwTerminate();
        return;
    }
    // Define contexto atual
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    glfwSetKeyCallback(window, GLFWkeyfun(game.keyCallback));

    glfwSetTime(0.0);
    while (!glfwWindowShouldClose(window)) {

        initialize();

        game.render();
        game.drawScore();
        //game.drawRank();
        if (game.getConfig().gameOver) {
            //glfwSetWindowShouldClose(window, GLFW_TRUE);

            game.resetGame();
        }

        // Resetar transformações para evitar acumulação
        glLoadIdentity();

        // Troca os buffers da janela, exibindo o que foi renderizado na tela
        glfwSwapBuffers(window);

        // Processa eventos da janela. Ex: Teclas pressionadas,Movimento do mouse,Fechamento da janela e etc...
        glfwPollEvents();
    }
    glfwTerminate();
}
