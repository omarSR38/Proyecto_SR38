#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <glad/glad.h>
#include "Texture2D.h"
#include "Shader2D.h"
#include "Renderer2D.h"
#include "OpenGLClass.h"

class Model {
public:
    glm::vec2 position;
    glm::vec2 size;
    float rotation = 0.0f;

    // recursos (pueden venir de ResourceManager más adelante)
    Texture2D texture;
    Shader2D spriteShader;
    std::shared_ptr<Renderer2D> rendererPtr;

    // paths (opcional)
    std::string VSPath, FSPath, imagenPath;

    Model(const glm::vec2& pos,
        const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);

    virtual ~Model() = default;

    virtual void liberarMemoria();

    virtual void update(float delta) = 0;
    virtual void draw(const glm::mat4& projection);

protected:
    GLuint quadVAO = 0;
    void initRenderData();
};

#endif // MODEL_H




