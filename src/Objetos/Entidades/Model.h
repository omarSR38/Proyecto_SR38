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
#include "ResourceManager.h"

class Model {
public:
///////////////////////////
////////ATRIBUTOS/////////
    glm::vec2 position;
    glm::vec2 size;
    float rotation = 0.0f;
    Texture2D texture;
    Shader2D spriteShader;
    //std::shared_ptr<Renderer2D> rendererPtr;
    //NOTA:   paths (opcional)
    std::string VSPath, FSPath, imagenPath;

    bool debugHitbox = false;
    glm::vec3 debugHitboxColor = glm::vec3(0.0f, 1.0f, 1.0f);
    void setDebugHitbox(bool v) { debugHitbox = v; }
    void setDebugHitboxColor(const glm::vec3& c) { debugHitboxColor = c; }

///////////////////////////
////////CONSTRUCTORES//////
    Model(const glm::vec2& pos,
        const glm::vec2& sz,
        OpenGLClass* og,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const glm::mat4& projection);
    virtual ~Model() = default;

///////////////////////////
/////SETTERS Y GETTERS/////

////////////////////////
////////METODOS/////////
    virtual void liberarMemoria();
    virtual void update(float delta) = 0;
    virtual void draw(const glm::mat4& projection);

protected:
////////////////////////
////////METODOS --/////
    GLuint quadVAO = 0;
    GLuint VBO = 0;
    void initRenderData();
};

#endif // MODEL_H




