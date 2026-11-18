#ifndef NIVELMENU_H
#define NIVELMENU_H

#include "Nivel.h"
#include "MenuScene.h"


class NivelMenu : public Nivel {
public:
    ///////////////////////////
    ////////ATRIBUTOS/////////

    ///////////////////////////
    ////////CONSTRUCTORES//////

    NivelMenu(OpenGLClass* ogl, GLFWwindow* win);

    ///////////////////////////
    /////SETTERS Y GETTERS/////

    ////////////////////////
    ////////METODOS/////////

    bool init() override;
    void update(float dt) override;
    void draw() override;
    void unload() override;

    bool isFinished() const override;
    int nextLevel() const override;

private:
    ///////////////////////////
    ////////ATRIBUTOS -///////

    OpenGLClass* gl;
    GLFWwindow* window;

    MenuScene menu;

    bool finished = false;
    int next = 0;
};

#endif // NIVELMENU_H