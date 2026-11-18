// Renderer2D.h
#ifndef RENDERER2D_H
#define RENDERER2D_H
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader2D.h"
#include "Texture2D.h"

class Renderer2D {
public:
    Renderer2D();
    Renderer2D(Shader2D& shader);
    //Renderer2D();
    ~Renderer2D();

    // Initialize quad for sprite rendering
    void Init();

    // Draw a textured quad at position with size and rotation
    void DrawSprite(Texture2D* texture, 
        const glm::vec2& position, 
        const glm::vec2& size, 
        float rotation, 
        const glm::vec3& color);



    void DrawFullscreenQuad(GLuint textureID);

private:
    Shader2D& shader;
    GLuint quadVAO;
    void initRenderData();
};
#endif // RENDERER2D_H
