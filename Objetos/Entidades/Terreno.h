#ifndef TERRENO_H
#define TERRENO_H

#include "Model.h"
#include <string>

/// Un bloque de terreno/mapa estático con su propia textura y colisión
class Terreno : public Model {
public:
    /// @param textureFile ruta al PNG del fondo de esta región
    Terreno(const glm::vec2& pos, const glm::vec2& sz, OpenGLClass* og,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_, const glm::mat4& projection_);


    void update(float delta) override;
    //void draw(glm::mat4 projection_);
    void inicarTerreno(const glm::vec2& pos, const glm::vec2& sz, OpenGLClass* og,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_, const glm::mat4& projection_);
};

#endif // TERRENO_H

