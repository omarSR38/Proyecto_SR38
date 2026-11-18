// Terreno.h
#ifndef TERRENO_H
#define TERRENO_H
#include <vector>
#include "Model.h"
#include "CollRect.h"      // ajusta la ruta si está en otra carpeta

class Terreno : public Model {
public:
    Terreno(const glm::vec2& pos, const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);

    void update(float delta) override; // normalmente vacío

    // Paredes (coordenadas lógicas absolutas)
    void addWall(float x, float y, float w, float h);
    const std::vector<CollRect>& getWalls() const;
    void setDebugWalls(bool v);
    void drawWalls(const glm::mat4& projection);

private:
    std::vector<CollRect> walls;
    bool debugWalls = false;
};
#endif


