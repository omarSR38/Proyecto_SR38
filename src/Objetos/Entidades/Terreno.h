// Terreno.h
#ifndef TERRENO_H
#define TERRENO_H
#include "Model.h"

class Terreno : public Model {
public:
    Terreno(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);

    void update(float delta) override; // normalmente vacío
};
#endif


