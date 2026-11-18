#ifndef GAME_H
#define GAME_H

#include "PixelPerfectRenderer.h"
#include "Scene.h"
#include "NivelMenu.h"
//#include "Personaje.h"
//#include "Shader2D.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include "OpenGLClass.h"

class Game {
public:
    //ATRIBUTOS A USAR:
    Scene currentScene;
    //NivelMenu menuLevel;

    //CONTRSTRUCTORES:
    Game();

    //SET Y GET:

    //METODOS:
    void run();

    //SIN USAR (PARA REGISTRO):
    //bool initializeGame();
};

#endif // GAME_H

