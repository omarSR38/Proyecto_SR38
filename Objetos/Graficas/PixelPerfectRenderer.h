// PixelPerfectRenderer.h

#ifndef _PIXEL_PERFECT_RENDERER_H_
#define _PIXEL_PERFECT_RENDERER_H_
#include <algorithm>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Shader2D.h"
#include <iostream>

class OpenGLClass; // forward

class PixelPerfectRenderer {
public:
    // Constructor: recibe puntero a OpenGLClass, ventana y dimensiones lógicas
    PixelPerfectRenderer(OpenGLClass* opengl, GLFWwindow* window, int virtualWidth, int virtualHeight);
    ~PixelPerfectRenderer();
    PixelPerfectRenderer();

    // Configura FBO, quad y shader de blit
    bool Initialize();
    // Inicia render a FBO
    void Begin();
    // Termina render: blit del FBO a ventana escalada
    void End();

    // Devuelve la textura del FBO (si la necesitas)
    GLuint GetFramebufferTexture() const;

private:
    OpenGLClass* m_opengl;       // Wrapper de OpenGL con funciones cargadas
    GLFWwindow* m_window;        // Contexto de GLFW
    int virtualWidth;            // Anchura lógica
    int virtualHeight;           // Altura lógica

    // Recursos del FBO
    GLuint fbo;
    GLuint textura;
    GLuint rbo;

    // Quad para blit
    GLuint quadVAO;
    GLuint quadVBO;

    // Shader para dibujar el FBO
    Shader2D blitShader;
};

#endif // _PIXEL_PERFECT_RENDERER_H_

