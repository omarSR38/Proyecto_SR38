#include "Model.h"
#include <iostream>

Model::Model(const glm::vec2& pos,
    const glm::vec2& sz,
    OpenGLClass* og, std::string VSPath_, std::string FSPath_, std::string imagenPath_, glm::mat4 projection_)
    : position(pos),size(sz),textura(og),spriteShader(og), ogl(og)
{
    // Habilita blending para transparencias
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VSPath = VSPath_;
    FSPath = FSPath_;
    imagenPath = imagenPath_;

    // Carga shader
    if (!spriteShader.Initialize(
        VSPath.c_str(),
        FSPath.c_str()))
    {
        std::cerr << "Error al inicializar SpriteShader\n";
    }
    
    spriteShader.Use();
    spriteShader.PonMatriz4x4("projection",&projection_[0][0]);
    if (!textura.LoadFromFile(imagenPath.c_str())) {
        std::cerr << "Fallo al cargar textura: " << imagenPath << "\n";
    }
    initRenderData();
}

void Model::draw(glm::mat4 projection_) {
    // 1. Activar shader
    spriteShader.Use();
    const glm::vec3& color = glm::vec3(1.0f);
    spriteShader.PonVec3("spriteColor", (float*)&color);
    float rotation = 0.0f;

    // 2. Calcular modelo
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    spriteShader.PonMatriz4x4("model", &model[0][0]);

    // 3. Activar y ligar textura
    textura.Bind();

    // 4. Dibujar
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Model::initRenderData() {
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

void Model::liberarMemoria() {

    spriteShader.Shutdown();
}