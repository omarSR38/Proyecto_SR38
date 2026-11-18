#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "CollRect.h"
#include "Objetos/Graficas/Texture2D.h"
#include "Objetos/Graficas/Shader2D.h"
//#include "Renderer2D.h"
#include "Objetos/Graficas/OpenGLClass.h"



class Model {
public:
    glm::vec2 position;
    glm::vec2 size;

    Texture2D textura;
    Shader2D spriteShader;
    //Renderer2D* renderer;      // ahora es puntero

    std::string imagenPath;
    std::string VSPath;
    std::string FSPath;
    OpenGLClass* ogl;

    GLuint quadVAO;

    /// @param og          puntero a tu wrapper OpenGLClass
    /// @param rend        puntero a tu Renderer2D (ya inicializado)
    Model(const glm::vec2& pos,
        const glm::vec2& sz,
        OpenGLClass* og, 
        std::string VSPath_, 
        std::string FSPath_, 
        std::string imagenPath_, 
        glm::mat4 projection_);
    virtual ~Model() {}
    virtual void liberarMemoria();
    virtual void update(float delta) = 0;
    void draw(glm::mat4 projection_);
    void initRenderData();
};

#endif // MODEL_H


