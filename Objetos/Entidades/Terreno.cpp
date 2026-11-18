#include "Terreno.h"
#include <iostream>

Terreno::Terreno(const glm::vec2& pos, const glm::vec2& sz, OpenGLClass* og,
    const std::string& VSPath_, const std::string& FSPath_,
    const std::string& imagenPath_, const glm::mat4& projection_)
    : Model(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection_)
{

}

void Terreno::update(float /*delta*/) {
    // Terreno estático, no hace nada
}



void Terreno::inicarTerreno(const glm::vec2& pos, const glm::vec2& sz, OpenGLClass* og,
    const std::string& VSPath_, const std::string& FSPath_,
    const std::string& imagenPath_, const glm::mat4& projection_) {

}


