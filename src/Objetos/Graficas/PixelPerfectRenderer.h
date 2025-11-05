// PixelPerfectRenderer.h

#ifndef _PIXEL_PERFECT_RENDERER_H_
#define _PIXEL_PERFECT_RENDERER_H_
#include <algorithm>
#include "Shader2D.h"
#include <iostream>
//SIN USAR (PARA REGISTRO):
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <GLFW/glfw3.h>

class OpenGLClass; // forward

class PixelPerfectRenderer {
public:
    //CONTRSTRUCTORES:
    PixelPerfectRenderer(OpenGLClass* opengl, GLFWwindow* window, int virtualWidth, int virtualHeight);
    ~PixelPerfectRenderer();
    PixelPerfectRenderer();

    //SET Y GET:

    //METODOS:
    // NOTA: Configura FBO, quad y shader de blit
    bool Initialize();
    // NOTA: Inicia render a FBO
    void Begin();
    // NOTA: Termina render: blit del FBO a ventana escalada
    void End();
    // NOTA: Devuelve la textura del FBO (si la necesitas)
    GLuint GetFramebufferTexture() const;

private:
    //ATRIBUTOS A USAR:
    //NOTA: APUNTADOR A VARIABLE EXTERNA DE OpenGLClass
    OpenGLClass* m_opengl;       // Wrapper de OpenGL con funciones cargadas
    //NOTA: APUNTADOR A VARIABLE EXTERNA DE OpenGLClass
    GLFWwindow* m_window;        // Contexto de GLFW
    // Nota: Shader para dibujar el FBO
    Shader2D blitShader;
    int virtualWidth;            // Anchura lógica
    int virtualHeight;           // Altura lógica
    // Recursos del FBO
    GLuint fbo;
    GLuint textura;
    GLuint rbo;
    // Quad para blit
    GLuint quadVAO;
    GLuint quadVBO;

};

#endif // _PIXEL_PERFECT_RENDERER_H_

