#include "Personaje.h"
#include <GLFW/glfw3.h>

Personaje::Personaje(
    const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection_)
    : Model(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection_) {

    hitbox.width = sz.x;
    hitbox.height = sz.y;
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}


void Personaje::update(float delta) {
    // Por ahora solo mueves con teclas
    //GLFWwindow* window = glfwGetCurrentContext();
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    //    position.y -= 20.0f * delta;
    //}
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    //    position.y += 20.0f * delta;
    //}
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    //    position.x -= 20.0f * delta;
    //}
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    //    position.x += 20.0f * delta;
    //}

    updateHitbox();
}






void Personaje::updateHitbox() {
    hitbox.x = position.x;
    hitbox.y = position.y;
    hitbox.width = size.x;
    hitbox.height = size.y;
}