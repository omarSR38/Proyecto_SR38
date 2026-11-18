// Renderer2D.cpp
#include "Renderer2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

///////////////////////////
////////CONSTRUCTORES//////

Renderer2D::~Renderer2D() {

    if (rectVAO) glDeleteVertexArrays(1, &rectVAO);


    if (rectLineVAO) glDeleteVertexArrays(1, &rectLineVAO);


    if (rectVBO) glDeleteBuffers(1, &rectVBO);


    if (rectLineVBO) glDeleteBuffers(1, &rectLineVBO);

    if (quadVAO)
        glDeleteVertexArrays(1, &quadVAO);

    if (quadVBO)
        glDeleteBuffers(1, &quadVBO);
}
Renderer2D::Renderer2D(std::shared_ptr<Shader2D> shaderPtr_) : shaderPtr(shaderPtr_) {
    initRenderData(); // crea VAO/VBO una sola vez
    initRectData();
}
/*Renderer2D::Renderer2D(Shader2D& shader)
{
    shaderPtr = std::make_shared<Shader2D>(shader); // o copiar si es necesario
    initRenderData();
    initRectData();
}*/

////////////////////////
////////METODOS/////////
void Renderer2D::initRenderData() {
    // configure VAO/VBO for a quad
    if (!shaderPtr || quadVAO != 0 || quadVBO != 0)
        return;

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
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Renderer2D::DrawSprite(Texture2D* texture, const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec3& color) {
    if (!shaderPtr || !texture || quadVAO == 0 || quadVBO == 0)
        return;

    float vertices[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
    texture->Bind(0);
    shaderPtr->Pon1Entero("image", 0);

    // 4. Dibujar
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void Renderer2D::Init() {

    if (quadVAO == 0) {
        initRenderData();
    }

    if (rectVAO == 0 || rectLineVAO == 0) {
        initRectData();
    }
}
void Renderer2D::DrawFullscreenQuad(GLuint textureID) {
    // Dibuja quad que cubre toda la pantalla, usando la textura del framebuffer
    // Puedes usar una VAO fija y un shader simple que toma una textura
}

void Renderer2D::initRectData() {
    // VBO para rect (dos triángulos)
    float quadVerts[] = {
        // pos   // tex (ignored)
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    //GLuint VBO;
    glGenVertexArrays(1, &rectVAO);
    glGenBuffers(1, &rectVBO);
    glBindVertexArray(rectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // VAO para linea (4 vertices)
    float lineVerts[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };
    GLuint lineVBO;
    glGenVertexArrays(1, &rectLineVAO);
    glGenBuffers(1, &rectLineVBO);
    glBindVertexArray(rectLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectLineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVerts), lineVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const glm::mat4& projection, bool filled) {
    if (!shaderPtr) return;
    shaderPtr->Use();

    // shader espera punteros float* (tu Shader2D tiene PonMatriz4x4 que espera float*),
    // así que copiamos las matrices a arrays modificables
    //float projArr[16];
    //std::memcpy(projArr, (const float*)&projection[0][0], sizeof(projArr));
    //shaderPtr->PonMatriz4x4("projection", projArr);
    shaderPtr->PonMatriz4x4("projection", (float*)&projection[0][0]);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    float modelArr[16];
    std::memcpy(modelArr, (const float*)&model[0][0], sizeof(modelArr));
    shaderPtr->PonMatriz4x4("model", modelArr);

    // color: si tu shader usa 'uColor' o 'spriteColor' ajusta aquí.
    // con el shader sprite.vs/fs se usa "spriteColor" (vec3) — si usas color shader con "uColor" usa PonVec4.
    // Vamos a intentar PonVec4 (asegúrate que Shader2D::PonVec4 existe).
    shaderPtr->PonVec4("uColor", (float*)&color);

    if (filled) {
        glBindVertexArray(rectVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else {
        glBindVertexArray(rectLineVAO);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
    glBindVertexArray(0);
}

void Renderer2D::DrawRectOutline(
    const glm::vec2& pos,
    const glm::vec2& size,
    const glm::vec4& color,
    const glm::mat4& projection)
{
    DrawRect(pos, size, color, projection, false);
}




void Renderer2D::DrawSpriteRegion(
    Texture2D* texture,
    const glm::vec2& position,
    const glm::vec2& size,
    float rotation,
    const glm::vec2& uvOffset,
    const glm::vec2& uvSize,
    const glm::vec3& color)
{
    if (!shaderPtr || !texture || quadVAO == 0 || quadVBO == 0)
        return;

    float u0 = uvOffset.x;
    float v0 = uvOffset.y;
    float u1 = u0 + uvSize.x;
    float v1 = v0 + uvSize.y;

    float vertices[] = {
        0.0f, 1.0f, u0, v1,
        1.0f, 0.0f, u1, v0,
        0.0f, 0.0f, u0, v0,

        0.0f, 1.0f, u0, v1,
        1.0f, 1.0f, u1, v1,
        1.0f, 0.0f, u1, v0
    };

    shaderPtr->Use();

    shaderPtr->PonVec3("spriteColor", (float*)&color);
    shaderPtr->Pon1Entero("image", 0);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(
        model,
        glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)
    );

    model = glm::rotate(
        model,
        glm::radians(rotation),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    model = glm::translate(
        model,
        glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)
    );

    model = glm::scale(model, glm::vec3(size, 1.0f));

    shaderPtr->PonMatriz4x4("model", &model[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    texture->Bind(0);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

//*********SIN USAR*********
//Renderer2D::Renderer2D(Shader2D& shader) : shader(shader) {
//    initRenderData();
//}
