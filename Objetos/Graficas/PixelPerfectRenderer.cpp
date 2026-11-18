// PixelPerfectRenderer.cpp

#include "PixelPerfectRenderer.h"
//#include <glad/glad.h>
//#include <iostream>



PixelPerfectRenderer::PixelPerfectRenderer(OpenGLClass* opengl, GLFWwindow* window, int vw, int vh)
    : m_opengl(opengl)
    , m_window(window)
    , virtualWidth(vw)
    , virtualHeight(vh)
    , fbo(0)
    , textura(0)
    , rbo(0)
    , quadVAO(0)
    , quadVBO(0)
    , blitShader(opengl)
{}


PixelPerfectRenderer::~PixelPerfectRenderer() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &textura);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
}

bool PixelPerfectRenderer::Initialize() {
    // 1) Setup FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Attach texture
    glGenTextures(1, &textura);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, virtualWidth, virtualHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textura, 0);

    // Depth + stencil
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, virtualWidth, virtualHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "ERROR: FBO incomplete";
            return false;
    }
    // Unbind FBO to restore default
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2) Initialize blit shader
    if (!blitShader.Initialize("shaders/blit.vs", "shaders/blit.fs")) {
        std::cerr << "ERROR: Failed to initialize blit shader\n";
        return false;
    }
    blitShader.Use();
    blitShader.SetInt("screenTex", 0);

    // 3) Prepare full-screen quad for blit
    float quadVerts[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    return true;
}

void PixelPerfectRenderer::Begin() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, virtualWidth, virtualHeight);
}

void PixelPerfectRenderer::End() {
    // Restore default framebuffer and compute scaled viewport
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    int w, h;
    glfwGetFramebufferSize(m_window, &w, &h);
    float sx = w / (float)virtualWidth;
    float sy = h / (float)virtualHeight;
    float scale = (sx < sy) ? sx : sy;
    int sw = (int)(virtualWidth * scale);
    int sh = (int)(virtualHeight * scale);
    int ox = (w - sw) / 2;
    int oy = (h - sh) / 2;
    glViewport(ox, oy, sw, sh);

    // Perform blit: draw full-screen quad with FBO texture
    blitShader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


GLuint PixelPerfectRenderer::GetFramebufferTexture() const {
    return textura;
}

PixelPerfectRenderer::PixelPerfectRenderer() {

}
