// PersonajeNpc.cpp
#include "PersonajeNpc.h"
PersonajeNpc::PersonajeNpc(const glm::vec2& pos, const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : Personaje(pos, sz, og, VSPath_, FSPath_, imagenPath_, projection) {}

void PersonajeNpc::update(float delta) {
    // IA simple o comportamiento
    updateHitbox();
}
