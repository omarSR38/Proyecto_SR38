// Renderer2D.cpp
#include "Renderer2D.h"

//CONTRSTRUCTORES:
//Renderer2D::Renderer2D(Shader2D& shader) : shader(shader) {
//    initRenderData();
//}
Renderer2D::~Renderer2D() {
    glDeleteVertexArrays(1, &quadVAO);
}
Renderer2D::Renderer2D(std::shared_ptr<Shader2D> shaderPtr_) : shaderPtr(shaderPtr_) {
    initRenderData(); // crea VAO/VBO una sola vez
}

Renderer2D::Renderer2D(Shader2D& shader)
{
    shaderPtr = std::make_shared<Shader2D>(shader); // o copiar si es necesario
    initRenderData();
}



//METODOS:
void Renderer2D::initRenderData() {
    // configure VAO/VBO for a quad
    GLuint VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Renderer2D::DrawSprite(Texture2D* texture, const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec3& color) {
    // 1. Activar shader
    shaderPtr->Use();
    shaderPtr->PonVec3("spriteColor", (float*)&color);

    // 2. Calcular modelo
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    shaderPtr->PonMatriz4x4("model", &model[0][0]);

    // 3. Activar y ligar textura
    texture->Bind();

    // 4. Dibujar
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void Renderer2D::Init() {

    initRenderData();
}
void Renderer2D::DrawFullscreenQuad(GLuint textureID) {
    // Dibuja quad que cubre toda la pantalla, usando la textura del framebuffer
    // Puedes usar una VAO fija y un shader simple que toma una textura
}
