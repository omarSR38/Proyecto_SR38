#include "Jugador.h"
#include <GLFW/glfw3.h>

///////////////////////////
////////CONSTRUCTORES//////
Jugador::Jugador(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection_)
    : Personaje(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection_)
{
    SpeedCaminar = 60.0f; // ejemplo: 60 unidades/segundo
}
Jugador::~Jugador() {
    // si Personaje/Model liberan recursos, aquí no hace falta mucho más.
}

////////////////////////
////////METODOS/////////

void Jugador::update(float delta) {

    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) return;

    glm::vec2 direccion(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        direccion.y -= 1.0f;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        direccion.y += 1.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        direccion.x -= 1.0f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        direccion.x += 1.0f;

    // Evitar que el movimiento diagonal sea más rápido
    if (glm::length(direccion) > 0.0f) {
        direccion = glm::normalize(direccion);
    }

    position += direccion * SpeedCaminar * delta;

    updateHitbox();
}

