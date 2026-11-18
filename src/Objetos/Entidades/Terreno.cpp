// Terreno.cpp
#include "Terreno.h"

///////////////////////////
////////CONSTRUCTORES//////
Terreno::Terreno(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : Model(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection)
{}

////////////////////////
////////METODOS/////////
void Terreno::update(float delta) {
    // terreno estático: nada que actualizar por defecto
}

void Terreno::addWall(float x, float y, float w, float h) {
    walls.emplace_back(x, y, w, h);
}

const std::vector<CollRect>& Terreno::getWalls() const {
    return walls;
}

void Terreno::setDebugWalls(bool v) {
    debugWalls = v;
}

void Terreno::drawWalls(const glm::mat4& projection) {
    if (!debugWalls) return;

    auto renderer = ResourceManager::GetRenderer("outline");
    if (!renderer) return;

    for (const auto& w : walls) {
        renderer->DrawRect(
            glm::vec2(w.x, w.y),
            glm::vec2(w.width, w.height),
            glm::vec4(1.0f, 0.2f, 0.2f, 1.0f),   // rojo
            projection,
            false
        );
    }
}



