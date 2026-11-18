#include "NivelMenu.h"

//#include <GLFW/glfw3.h>
#include <ResourceManager.h>

///////////////////////////
////////CONSTRUCTORES//////

NivelMenu::NivelMenu(OpenGLClass* ogl, GLFWwindow* win)
    : gl(ogl),
    window(win),
    menu(win)
{
}

////////////////////////
////////METODOS/////////

bool NivelMenu::init()
{
    ///////////////////////////////////////////////////////
    // SHADERS
    ///////////////////////////////////////////////////////

    ResourceManager::LoadShader(
        "sprite",
        "shaders/sprite.vs",
        "shaders/sprite.fs",
        gl
    );

    ///////////////////////////////////////////////////////
    // TEXTURAS MENU
    ///////////////////////////////////////////////////////

    ResourceManager::LoadTexture(
        "menu_bg",
        "assets/menu/fondo.png",
        gl
    );

    ResourceManager::LoadTexture(
        "menu_start",
        "assets/menu/boton_iniciar.png",
        gl
    );

    ResourceManager::LoadTexture(
        "menu_exit",
        "assets/menu/boton_salir.png",
        gl
    );

    return menu.initialize();
}

void NivelMenu::update(float dt)
{
    menu.update(dt);

    if (menu.shouldStartGame) {
        finished = true;
        next = 1;
    }

    if (menu.shouldExit) {
        glfwSetWindowShouldClose(window, true);
    }
}

void NivelMenu::draw()
{
    menu.draw();
}

void NivelMenu::unload()
{
}

bool NivelMenu::isFinished() const
{
    return finished;
}

int NivelMenu::nextLevel() const
{
    return next;
}