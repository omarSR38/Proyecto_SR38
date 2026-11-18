#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Objetos/Graficas/OpenGLClass.h"
#include "Objetos/Graficas/PixelPerfectRenderer.h"
#include "Objetos/Entidades/Personaje.h"
#include "Objetos/Graficas/Shader2D.h"
#include <glm/gtc/matrix_transform.hpp>

class Game {
public:
    Scene currentScene;
    PixelPerfectRenderer pixelRenderer;

    Game();

    bool initializeGame();

    void run();
};

#endif // GAME_H


//Game::Game() {
    // Aquí puedes dejarlo vacío o inicializar cosas si necesitas
//}
