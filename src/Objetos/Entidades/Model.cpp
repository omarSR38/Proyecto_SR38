#include "Model.h"
//#include <iostream>
#include <ResourceManager.h>

///////////////////////////
////////CONSTRUCTORES//////
Model::Model(const glm::vec2& pos,
    const glm::vec2& sz,
    OpenGLClass* og,
    const std::string& VSPath_,
    const std::string& FSPath_,
    const std::string& imagenPath_,
    const glm::mat4& projection)
    : position(pos), size(sz), texture(og), spriteShader(og)
{
    VSPath = VSPath_;
    FSPath = FSPath_;
    imagenPath = imagenPath_;

    // enable blending once (siempre con contexto activo)
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!spriteShader.Initialize(VSPath.c_str(), FSPath.c_str())) {
        std::cerr << "Error inicializando shader: " << VSPath << " / " << FSPath << "\n";
    }

    spriteShader.Use();
    spriteShader.PonMatriz4x4("projection", &projection[0][0]);

    if (!texture.LoadFromFile(imagenPath.c_str())) {
        std::cerr << "Fallo al cargar textura: " << imagenPath << "\n";
    }

    initRenderData();
}

////////////////////////
////////METODOS/////////
void Model::initRenderData() {
    //GLuint VBO;
    float vertices[] = {
        // pos   // tex
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
void Model::draw(const glm::mat4& projection) {
    spriteShader.Use();
    glm::vec3 color(1.0f);
    spriteShader.PonVec3("spriteColor", (float*)&color);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    spriteShader.PonMatriz4x4("model", &model[0][0]);
    if (debugHitbox) {
        auto colorRenderer = ResourceManager::GetRenderer("outline"); // o "color"
        if (colorRenderer) {
            glm::vec4 c = glm::vec4(debugHitboxColor, 1.0f);
            colorRenderer->DrawRect(position, size, c, projection, false); // filled=false -> outline
        }
        else {
            // fallback: intentar crear el renderer (si no lo creaste)
            auto colorShader = ResourceManager::GetShader("color");
            if (colorShader) {
                colorRenderer = ResourceManager::GetOrCreateRenderer("outline", colorShader);
                if (colorRenderer) colorRenderer->DrawRect(position, size, glm::vec4(debugHitboxColor, 1.0f), projection, false);
            }
        }
    }
    texture.Bind();
































    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void Model::liberarMemoria() {
    spriteShader.Shutdown();
    // texture.Release() si lo necesitas
    if (quadVAO) {
        glDeleteVertexArrays(1, &quadVAO);
        quadVAO = 0;
    }

    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
}




