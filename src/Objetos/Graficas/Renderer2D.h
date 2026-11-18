// Renderer2D.h
#ifndef RENDERER2D_H
#define RENDERER2D_H
#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>
#include "Shader2D.h"
#include "Texture2D.h"

class Renderer2D {
public:
///////////////////////////
////////CONSTRUCTORES//////
    Renderer2D() = default;
    //Renderer2D(Shader2D& shader);
    ~Renderer2D();
    Renderer2D(std::shared_ptr<Shader2D> shaderPtr_);

///////////////////////////
/////SETTERS Y GETTERS/////

////////////////////////
////////METODOS/////////
    //NOTA: Initialize quad for sprite rendering
    void Init();
    //NOTA:  Draw a textured quad at position with size and rotation
    void DrawSprite(Texture2D* texture, 
        const glm::vec2& position, 
        const glm::vec2& size, 
        float rotation, 
        const glm::vec3& color);
    void DrawFullscreenQuad(GLuint textureID);
    void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::mat4& projection, bool filled = true);
    //void initRectData();
    void DrawRectOutline(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const glm::mat4& projection);




    void DrawSpriteRegion(
        Texture2D* texture,
        const glm::vec2& position,
        const glm::vec2& size,
        float rotation,
        const glm::vec2& uvOffset,
        const glm::vec2& uvSize,
        const glm::vec3& color
    );
private:
///////////////////////////
////////ATRIBUTOS -///////
    GLuint quadVBO = 0;
    std::shared_ptr<Shader2D> shaderPtr;
    GLuint quadVAO = 0;
    GLuint rectVAO = 0;      // VAO para rect relleno (6 vertices)
    GLuint rectLineVAO = 0;  // VAO para linea (4 vertices)

    GLuint rectVBO = 0;
    GLuint rectLineVBO = 0;
    //std::shared_ptr<Shader2D> colorShader; // shader para dibujar color (inyectado desde ResourceManager)

////////////////////////
////////METODOS/////////
    void initRenderData();
    void initRectData();

//*********SIN USAR*********
    //Shader2D shader;
};
#endif // RENDERER2D_H
