#include "Game.h"

Game::Game() {

    if (currentScene.initializeScene()) {

    }
}

void Game::run() {
    // 2. Pixel Perfect Renderer (256x240)
    pixelRenderer = PixelPerfectRenderer(&currentScene.gl, currentScene.window, 256.00f, 224.00f);
    if (!pixelRenderer.Initialize());
    float last = (float)glfwGetTime();

    while (!currentScene.gl.WindowShouldClose()) {
        float now = (float)glfwGetTime();
        float dt = now - last;
        last = now;
        //glClearColor(0.f, 0.f, 0.f, 1.f);
        //glClear(GL_COLOR_BUFFER_BIT);
        pixelRenderer.Begin();
        currentScene.drawAll(dt);
        pixelRenderer.End();
        glfwSwapBuffers(currentScene.gl.GetWindow());
        glfwPollEvents();
    }
    currentScene.liberarMemoria();
}