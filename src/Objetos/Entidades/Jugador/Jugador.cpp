#include "Jugador.h"
#include <GLFW/glfw3.h>

// Constructor: delega en Personaje
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

// Destructor
Jugador::~Jugador() {
    // si Personaje/Model liberan recursos, aquí no hace falta mucho más.
}

// Update: ejemplo básico con WASD
void Jugador::update(float delta) {
    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) position.y -= SpeedCaminar * delta;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) position.y += SpeedCaminar * delta;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) position.x -= SpeedCaminar * delta;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) position.x += SpeedCaminar * delta;

    updateHitbox();
}

