#ifndef PERSONAJENPC_H
#define PERSONAJENPC_H

#include "Personaje.h"


class PersonajeNpc : public Personaje {
public:
    PersonajeNpc(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection_);
    ~PersonajeNpc();
    void update(float delta);

};

#endif // PERSONAJENPC_H