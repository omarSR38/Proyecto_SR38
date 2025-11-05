#ifndef JUGADOR_H
#define JUGADOR_H

#include "Personaje.h"
#include <string>

class Jugador : public Personaje {
public:
    float SpeedCaminar;

    // Constructor: la firma debe coincidir exactamente con la que uses al crear el objeto
    Jugador(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection_);

    virtual ~Jugador();

    void update(float delta) override;
};

#endif // JUGADOR_H

