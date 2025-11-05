#include "Game.h"

Game::Game() {

    if (currentScene.initializeScene()) {
        currentScene.agregarEntidad(
            glm::vec2(30, 30), glm::vec2(22, 26),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/npc.png");


        currentScene.agregarTerreno(
            glm::vec2(0, 0),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/house.png");

        currentScene.agregaJugador(
            glm::vec2(100, 100), glm::vec2(22, 26),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/player.png");












    }
}

void Game::run() {
    // 2. Pixel Perfect Renderer (256x240)
    //pixelRenderer = PixelPerfectRenderer(&currentScene.gl, currentScene.window, 256.00f, 224.00f);
    //if (!pixelRenderer.Initialize());
    float last = (float)glfwGetTime();

    while (!currentScene.gl.WindowShouldClose()) {
        float now = (float)glfwGetTime();
        float dt = now - last;
        last = now;
        currentScene.pixelRenderer.Begin();
        currentScene.drawAll(dt);
        currentScene.pixelRenderer.End();
        glfwSwapBuffers(currentScene.gl.GetWindow());
        glfwPollEvents();
    }
    //currentScene.liberarMemoria();
}