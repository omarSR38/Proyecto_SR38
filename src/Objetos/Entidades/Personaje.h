#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Model.h"
#include "CollRect.h"

class Personaje : public Model {
public:
    CollRect hitbox;

    Personaje(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);

    virtual ~Personaje() = default;

    void update(float delta) override;
    void updateHitbox();
};

#endif // PERSONAJE_H


