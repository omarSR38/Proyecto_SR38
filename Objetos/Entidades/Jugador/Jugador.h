#ifndef JUGADOR_H
#define JUGADOR_H

#include "Objetos/Entidades/Personaje.h"


class Jugador : public Personaje {
public:
    Jugador(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection_);
    ~Jugador();
    void update(float delta);
    float SpeedCaminar;

};

#endif // JUGADOR_H