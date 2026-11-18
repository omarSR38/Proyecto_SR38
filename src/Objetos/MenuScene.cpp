#include "MenuScene.h"

#include <iostream>

///////////////////////////
////////CONSTRUCTORES//////

MenuScene::MenuScene(GLFWwindow* win)
    : window(win),

    bgPos(0.0f, 0.0f),
    bgSize(256.0f, 224.0f),

    startPos(80.0f, 110.0f),
    startSize(96.0f, 24.0f),

    exitPos(80.0f, 150.0f),
    exitSize(96.0f, 24.0f),

    startHitbox(startPos.x, startPos.y, startSize.x, startSize.y),
    exitHitbox(exitPos.x, exitPos.y, exitSize.x, exitSize.y)
{
}

MenuScene::MenuScene()
{
}

////////////////////////
////////METODOS/////////

bool MenuScene::initialize()
{
    if (!window) {
        std::cerr << "ERROR: window nullptr\n";
        return false;
    }

    ///////////////////////////////////////////////////////
    // TEXTURAS
    ///////////////////////////////////////////////////////

    background = ResourceManager::GetTexture("menu_bg");
    btnStart = ResourceManager::GetTexture("menu_start");
    btnExit = ResourceManager::GetTexture("menu_exit");

    if (!background) {
        std::cerr << "ERROR: menu_bg no cargada\n";
        return false;
    }

    if (!btnStart) {
        std::cerr << "ERROR: menu_start no cargada\n";
        return false;
    }

    if (!btnExit) {
        std::cerr << "ERROR: menu_exit no cargada\n";
        return false;
    }

    ///////////////////////////////////////////////////////
    // RENDERER
    ///////////////////////////////////////////////////////

    renderer = ResourceManager::GetRenderer("spriteRenderer");

    if (!renderer) {

        auto spriteShader = ResourceManager::GetShader("sprite");

        if (!spriteShader) {
            std::cerr << "ERROR: shader sprite no cargado\n";
            return false;
        }

        renderer = ResourceManager::GetOrCreateRenderer(
            "spriteRenderer",
            spriteShader
        );
    }

    if (!renderer) {
        std::cerr << "ERROR: renderer null\n";
        return false;
    }

    shouldStartGame = false;
    shouldExit = false;

    prevMouse = false;

    return true;
}

void MenuScene::update(float dt)
{
    (void)dt;

    if (!window) return;

    ///////////////////////////////////////////////////////
    // MOUSE
    ///////////////////////////////////////////////////////

    double mx = 0.0;
    double my = 0.0;

    glfwGetCursorPos(window, &mx, &my);

    ///////////////////////////////////////////////////////
    // CLICK
    ///////////////////////////////////////////////////////

    bool mouseNow =
        (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)
            == GLFW_PRESS);

    CollRect mouseRect(
        (float)mx,
        (float)my,
        1.0f,
        1.0f
    );

    ///////////////////////////////////////////////////////
    // DETECTAR CLICK
    ///////////////////////////////////////////////////////

    if (mouseNow && !prevMouse) {

        if (mouseRect.intersects(startHitbox)) {
            shouldStartGame = true;
        }

        if (mouseRect.intersects(exitHitbox)) {
            shouldExit = true;
        }
    }

    prevMouse = mouseNow;
}

void MenuScene::draw()
{
    if (!renderer) return;

    ///////////////////////////////////////////////////////
    // FONDO
    ///////////////////////////////////////////////////////

    if (background) {
        renderer->DrawSprite(
            background.get(),
            bgPos,
            bgSize,
            0.0f,
            glm::vec3(1.0f)
        );
    }

    ///////////////////////////////////////////////////////
    // BOTON START
    ///////////////////////////////////////////////////////

    if (btnStart) {
        renderer->DrawSprite(
            btnStart.get(),
            startPos,
            startSize,
            0.0f,
            glm::vec3(1.0f)
        );
    }

    ///////////////////////////////////////////////////////
    // BOTON EXIT
    ///////////////////////////////////////////////////////

    if (btnExit) {
        renderer->DrawSprite(
            btnExit.get(),
            exitPos,
            exitSize,
            0.0f,
            glm::vec3(1.0f)
        );
    }
}