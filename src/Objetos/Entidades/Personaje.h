#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Model.h"
#include "CollRect.h"



class Personaje : public Model {
public:
///////////////////////////
////////ATRIBUTOS/////////
    CollRect hitbox;
///////////////////////////
////////CONSTRUCTORES//////
    Personaje(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);
    virtual ~Personaje() = default;

///////////////////////////
/////SETTERS Y GETTERS/////
    const CollRect& getHitbox() const { return hitbox; }
////////////////////////
////////METODOS/////////
    void update(float delta) override;
    void updateHitbox();

    void drawHitbox(const glm::mat4& projection);

protected:
///////////////////////////
////////ATRIBUTOS/////////


};

#endif // PERSONAJE_H


