#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <memory>
//#include <glm/glm.hpp>
//#include <GLFW/glfw3.h>

#include "Texture2D.h"
#include "Renderer2D.h"
#include "CollRect.h"
#include "ResourceManager.h"

class MenuScene {
public:
    ///////////////////////////
    ////////ATRIBUTOS/////////

    bool shouldStartGame = false;
    bool shouldExit = false;

    ///////////////////////////
    ////////CONSTRUCTORES//////
    MenuScene();
    MenuScene(GLFWwindow* win);

    ///////////////////////////
    /////SETTERS Y GETTERS/////

    ////////////////////////
    ////////METODOS/////////

    bool initialize();
    void update(float dt);
    void draw();

private:
    ///////////////////////////
    ////////ATRIBUTOS -///////

    GLFWwindow* window;

    std::shared_ptr<Texture2D> background;
    std::shared_ptr<Texture2D> btnStart;
    std::shared_ptr<Texture2D> btnExit;

    std::shared_ptr<Renderer2D> renderer;

    glm::vec2 bgPos;
    glm::vec2 bgSize;

    glm::vec2 startPos;
    glm::vec2 startSize;

    glm::vec2 exitPos;
    glm::vec2 exitSize;

    CollRect startHitbox;
    CollRect exitHitbox;

    bool prevMouse = false;
};

#endif // MENUSCENE_H