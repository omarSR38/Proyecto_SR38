#ifndef JUGADOR_H
#define JUGADOR_H

#include "Personaje.h"
#include <string>

class Jugador : public Personaje {
public:
///////////////////////////
////////ATRIBUTOS/////////
    float SpeedCaminar;

///////////////////////////
////////CONSTRUCTORES//////
    Jugador(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection_);
    virtual ~Jugador();

///////////////////////////
/////SETTERS Y GETTERS/////

////////////////////////
////////METODOS/////////
    void update(float delta) override;
};

#endif // JUGADOR_H

