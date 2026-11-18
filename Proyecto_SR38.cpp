// Resolución lógica (SNES)
constexpr float LOGICAL_WIDTH = 256.00f;
constexpr float LOGICAL_HEIGHT = 224.00f;

// Tamaño de ventana física (Undertale-style)
constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

#include "Game.h"

//SIN USAR (PARA REGISTRO):
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "OpenGLClass.h"
//#include "Shader2D.h"
//#include "Texture2D.h"
//#include "Renderer2D.h"
//#include "PixelPerfectRenderer.h"

int main() {
    Game juego1;
    juego1.run();

    //EJEMPLO HOLA MUNDO HOLA TRIANGULO
    //
    
    //// 1. Inicializar OpenGL y ventana
    //OpenGLClass opengl;
    //if (!opengl.InitializeGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "Proyecto SR38", false)) {
    //    return -1;
    //}
    //InputClass* input = new InputClass(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    //opengl.SetInput(input);
    //GLFWwindow* window = opengl.GetWindow();

    //// 2. Pixel Perfect Renderer (256x240)
    //PixelPerfectRenderer pixelRenderer(&opengl,window, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    //if (!pixelRenderer.Initialize()) {
    //    return -1;
    //}

    //// 3. Shader y proyección ortográfica
    //std::string basePath = "C:/Users/eduar/source/repos/Proyecto_SR38/";  // o relativa a ejecutable
    //std::string vsPath = basePath + "shaders/sprite.vs";
    //std::string fsPath = basePath + "shaders/sprite.fs";
    //std::string BlitvsPath = basePath + "shaders/blit.vs";
    ////std::string BlitfsPath = basePath + "shaders/blit.fs";
    //Shader2D spriteShader(&opengl);
    //if (!spriteShader.Initialize(vsPath.c_str(), fsPath.c_str())) {
    //    return -1;
    //}
    //glm::mat4 projection = glm::ortho(0.0f, LOGICAL_WIDTH, LOGICAL_HEIGHT, 0.0f); // y al revés para estilo top-down
    //spriteShader.Use();
    //spriteShader.PonMatriz4x4("projection", &projection[0][0]);
    //Renderer2D renderer(spriteShader);

    //// 4. Cargar textura de jugador (esto es un ejemplo, implementa LoadTexture)
    //std::string imagenPath = basePath + "assets/player.png";
    //Texture2D miTextura(&opengl);
    //if (!miTextura.LoadFromFile(imagenPath.c_str())) {
    //    std::cerr << "Fallo al cargar textura: " << imagenPath << "\n";
    //}
    //std::string fondoPath = basePath + "assets/house.png";
    //Texture2D fondo(&opengl);
    //if (!fondo.LoadFromFile(fondoPath.c_str())) {
    //    std::cerr << "Fallo al cargar textura: " << fondoPath << "\n";
    //}

    //// 5. Posición y velocidad
    //glm::vec2 position(110.0f, 110.0f);
    //glm::vec2 size(22.0f, 22.0f);
    //float speed = 40.0f;
    //// 6. Timer
    //float lastTime = (float)glfwGetTime();

    //// 7. Game Loop
    //while (!opengl.WindowShouldClose()) {
    //    float currentTime = glfwGetTime();
    //    float deltaTime = currentTime - lastTime;
    //    lastTime = currentTime;
    //    // INPUT
    //    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    //        position.y -= speed * deltaTime; // subir
    //    }
    //    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    //        position.y += speed * deltaTime;  // bajar
    //    }
    //    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    //        position.x -= speed * deltaTime;  // izquierda
    //    }
    //    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    //        position.x += speed * deltaTime;  // derecha
    //    }

    //    //pixelRenderer.Begin();
    //    // Limpia el FBO
    //    glClearColor(0.f, 0.f, 0.f, 1.f);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    //spriteShader.SetInt("image", 0);        // slot de textura
    //    //spriteShader.Use();                // indica el uso del shader
    //    //miTextura.Bind();                // enlaza la textura
    //    //std::cout << "Drawing at " << position.x << "," << position.y << "\n";
    //    //renderer.DrawFullscreenQuad(pixelRenderer.GetFramebufferTexture());
    //    renderer.DrawSprite(&fondo,
    //        glm::vec2(0.0f, 0.0f),
    //        glm::vec2(LOGICAL_WIDTH, LOGICAL_HEIGHT),
    //        0.0f,
    //        glm::vec3(1.0f));
    //    renderer.DrawSprite(&miTextura,
    //        position,
    //        size,
    //        0.0f,
    //        glm::vec3(1.0f));
    //    //pixelRenderer.End();
    //    glfwSwapBuffers(window);
    //    glfwPollEvents();
    //    //glActiveTexture(GL_TEXTURE0);
    //    //glBindTexture(GL_TEXTURE_2D, pixelRenderer.GetFramebufferTexture());
    //    //glBindVertexArray(quadVAO);
    //    //glDrawArrays(GL_TRIANGLES, 0, 6);
    //}
    //// Cierre
    //spriteShader.Shutdown();
    ////shaderBlit.Shutdown();
    //opengl.Shutdown();

    return 0;
}
