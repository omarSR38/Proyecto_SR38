#include "Personaje.h"
#include <GLFW/glfw3.h>

///////////////////////////
////////CONSTRUCTORES//////
Personaje::Personaje(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : Model(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection),
    hitbox(pos.x, pos.y, sz.x, sz.y)
{}

////////////////////////
////////METODOS/////////
void Personaje::update(float delta) {
    // lógica por defecto (puedes override en Jugador)
    updateHitbox();
}
void Personaje::updateHitbox() {
    hitbox.x = position.x;
    hitbox.y = position.y;
    hitbox.width = size.x;
    hitbox.height = size.y;
}

void Personaje::drawHitbox(const glm::mat4& projection)
{
    auto outline = ResourceManager::GetRenderer("outline");
    if (!outline) return;

    outline->DrawRectOutline(
        glm::vec2(hitbox.x, hitbox.y),
        glm::vec2(hitbox.width, hitbox.height),
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        projection
    );
}


