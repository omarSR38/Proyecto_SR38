#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Model.h"
#include "Objetos/CollRect.h"

class Personaje : public Model {
public:
    Personaje(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection_);
    ~Personaje() {}

    void update(float delta);
    CollRect hitbox;

    void updateHitbox();
};

#endif // PERSONAJE_H
