// Terreno.cpp
#include "Terreno.h"

Terreno::Terreno(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : Model(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection)
{}

void Terreno::update(float delta) {
    // terreno estático: nada que actualizar por defecto
}



