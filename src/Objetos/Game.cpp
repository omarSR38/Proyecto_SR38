#include "Game.h"
#include "NivelMenu.h"

///////////////////////////
////////CONSTRUCTORES//////
Game::Game() {

    if (currentScene.initializeScene()) {
        currentScene.agregarEntidad(
            glm::vec2(30, 30), glm::vec2(22, 26),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/npc.png",
            {
                "Hola Rex, bienvenido a mi casa.",
                "Cuidado con el buzon, a veces muerde.",
                "¿cuando va a ser la proxima tocada de ROVINS?"
            }
        );


        currentScene.agregarTerreno(
            glm::vec2(0, 0),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/house.png");
        currentScene.agregarPared(0, 0, 256, 8);       // borde superior
        currentScene.agregarPared(0, 216, 256, 8);     // borde inferior
        currentScene.agregarPared(0, 0, 8, 224);       // borde izquierdo
        currentScene.agregarPared(248, 0, 8, 224);     // borde derecho
        currentScene.agregarPared(96, 58, 82, 66);     // casa (ajustar)

        currentScene.agregarPared(8, 158, 78, 16);     // valla inferior izquierda
        currentScene.agregarPared(120, 158, 62, 16);   // valla inferior derecha
        currentScene.agregarPared(119, 136, 14, 12);   // buzón
        currentScene.agregarPared(220, 160, 28, 26);   // letrero

        currentScene.agregaJugador(
            glm::vec2(100, 175), glm::vec2(22, 26),
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/player2.png");




        







    }
    //menuLevel.gl = currentScene.gl;
    //menuLevel.window = currentScene.window
    //menuLevel-init();


}

////////////////////////
////////METODOS/////////
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
        currentScene.drawAll();
        currentScene.updateAll(dt);
        currentScene.pixelRenderer.End();
        glfwSwapBuffers(currentScene.gl.GetWindow());
        glfwPollEvents();
    }
    //currentScene.liberarMemoria();
}