#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <string>

#include "Text/AlfabetoGlyphs.h"
#include "Terreno.h"
#include "Jugador/Jugador.h"
#include "PersonajeNpc.h"
#include <ResourceManager.h>
#include "DialogueBox.h"

//SIN USAR (PARA REGISTRO):
//#include "InputClass.h"
//#include "Model.h"
//#include "Personaje.h"

class Scene {
public:
    //CONSTANTES:
    //NOTA: Resolución lógica (SNES)
    float LOGICAL_WIDTH = 256.00f;
    float LOGICAL_HEIGHT = 224.00f;
    // Tamaño de ventana física (Undertale-style)
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;

///////////////////////////
////////ATRIBUTOS/////////
    //NOTA: gl variable original de OpenGLClass
    OpenGLClass gl;
    //NOTA: proyection matriz original de proyeccion
    glm::mat4 proyection;
    //NOTA: listado variable de personajesNPC en la escena
    std::vector<std::unique_ptr<PersonajeNpc>> entities;
    //NOTA: listado variable de fondos para un mismo terreno
    std::vector<std::unique_ptr<Terreno>> terrenos;
    //NOTA: jugador manejador
    //Jugador* jugador01;
    std::unique_ptr<Jugador> jugador01;
    //NOTA: Objeto dependiente de GLFW
    GLFWwindow* window;
    //NOTA: Objeto para mantener imagen en cambio de ventana
    PixelPerfectRenderer pixelRenderer;
    //InputClass* input;
    std::unique_ptr<InputClass> input;
    std::unique_ptr<TextRenderer> textRenderer;

    bool debugHitboxes = false;
    bool prevF1 = false;

    // Sistema de diálogo
    DialogueBox dialogueBox;

    // Control de clic
    bool prevMouseLeft = false;

    // Control de teclado
    bool prevEnter = false;
    bool prevEscape = false;

    // Interacción por tecla
    bool prevInteract = false;
    float INTERACT_RANGE = 12.0f;   // margen alrededor del NPC, en px lógicos

    bool npcsSolid = true;        // los NPC también bloquean el paso

///////////////////////////
////////CONSTRUCTORES//////
    Scene() {
        //gl = OpenGLClass();
        jugador01 = nullptr;
        window = nullptr;
        proyection = glm::mat4(1.0f);
    }
    ~Scene() {
        liberarMemoria();
    }

///////////////////////////
/////SETTERS Y GETTERS/////
    //GLFWwindow getwindow() {
    //    return window;
    //}

    //OpenGLClass getgl() {
    //    return gl;
    //}
////////////////////////
////////METODOS/////////
    bool initializeScene() {
        // 1. Inicializar OpenGL y ventana
        if (!gl.InitializeGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "Proyecto SR38", false)) return false;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ResourceManager::LoadTexture(
            "font",
            "assets/alfabeto_blanco.png",
            &gl,
            false
        );
        auto font = ResourceManager::GetTexture("font");

        if (font) {
            std::cout << "Atlas cargado correctamente: "
                << font->GetWidth() << " x "
                << font->GetHeight() << std::endl;
        }
        else {
            std::cout << "ERROR: No se pudo cargar el atlas" << std::endl;
        }



        //LoadTexture(const std::string& key, const std::string& path, OpenGLClass* ogl, bool flipVertical)
        //input = (new InputClass(LOGICAL_WIDTH, LOGICAL_HEIGHT));
        //gl.SetInput(input);
        input = std::make_unique<InputClass>(
            LOGICAL_WIDTH,
            LOGICAL_HEIGHT
        );

        gl.SetInput(input.get());
        window = gl.GetWindow();
        // Proyección ortográfica lógica
        proyection = glm::ortho(0.0f, LOGICAL_WIDTH, LOGICAL_HEIGHT, 0.0f);
        //NOTA: PARA MANTENER RELACION DE IMAGEN
        pixelRenderer = PixelPerfectRenderer(&gl, window, LOGICAL_WIDTH, LOGICAL_HEIGHT);
        if (!pixelRenderer.Initialize()) return false;


        // cargar shaders
        ResourceManager::LoadShader("sprite", "shaders/sprite.vs", "shaders/sprite.fs", &gl);
        ResourceManager::LoadShader("color", "shaders/color.vs", "shaders/color.fs", &gl);

        // crear renderers compartidos (uno para sprites si quieres y otro para outlines)
        auto spriteShader = ResourceManager::GetShader("sprite");
        if (spriteShader) {
            ResourceManager::GetOrCreateRenderer(
                "sprite",
                spriteShader
            );
        }
        if (spriteShader) ResourceManager::GetOrCreateRenderer("spriteRenderer", spriteShader);


        auto colorShader = ResourceManager::GetShader("color");
        if (colorShader) ResourceManager::GetOrCreateRenderer("outline", colorShader);



        auto spriteRenderer = ResourceManager::GetRenderer("sprite");
        if (font && spriteRenderer) {
            textRenderer = std::make_unique<TextRenderer>(spriteRenderer, font);
            RegisterAlfabetoGlyphs(*textRenderer);
        }

        return true;
    }
    void agregaJugador(const glm::vec2& pos, const glm::vec2& sz,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_) {
        jugador01 = std::make_unique<Jugador>(
            pos, sz, &gl,
            VSPath_, FSPath_, imagenPath_,
            proyection
        );
    }




    //void agregarEntidad(const glm::vec2& pos, const glm::vec2& sz,
    //    const std::string& VSPath_, const std::string& FSPath_,
    //    const std::string& imagenPath_) {
    //    entities.emplace_back(std::make_unique<PersonajeNpc>(
    //        pos, sz,
    //        &gl,
    //        VSPath_,
    //        FSPath_,
    //        imagenPath_,
    //        proyection
    //    ));
    //}

    void agregarEntidad(
        const glm::vec2& pos,
        const glm::vec2& sz,
        const std::string& VSPath_,
        const std::string& FSPath_,
        const std::string& imagenPath_,
        const std::vector<std::string>& dialogue = {}
    ) {

        auto npc = std::make_unique<PersonajeNpc>(
            pos,
            sz,
            &gl,
            VSPath_,
            FSPath_,
            imagenPath_,
            proyection
        );

        npc->setDialogue(dialogue);

        entities.emplace_back(std::move(npc));
    }








    void agregarTerreno(const glm::vec2& pos,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_) {
        terrenos.emplace_back(std::make_unique<Terreno>(
            pos, glm::vec2(LOGICAL_WIDTH, LOGICAL_HEIGHT),
            &gl,
            VSPath_,
            FSPath_,
            imagenPath_,
            proyection
        ));
    }

    //NOTA:PARA GRAFICAR
    //NOTA: PARA CARGAR TODOS LOS ELEMENTOS EN EL CICLO





    //void updateAll(float delta) {
    //    for (auto& e : entities) e->update(delta);
    //    // detección simple de colisiones
    //    for (size_t i = 0; i < entities.size(); ++i) {
    //        for (size_t j = i + 1; j < entities.size(); ++j) {
    //            if (entities[i]->hitbox.intersects(entities[j]->hitbox)) {
    //                // manejar colisión (por simplicidad, solo reportar)
    //                // could call onCollision
    //            }
    //        }
    //    }
    //    jugador01->update(delta);

    //    GLFWwindow* w = gl.GetWindow();
    //    bool f1now = (glfwGetKey(w, GLFW_KEY_F1) == GLFW_PRESS);
    //    if (f1now && !prevF1) {
    //        debugHitboxes = !debugHitboxes;
    //        for (auto& e : entities) e->setDebugHitbox(debugHitboxes);
    //        for (auto& t : terrenos) t->setDebugHitbox(debugHitboxes);
    //        if (jugador01) jugador01->setDebugHitbox(debugHitboxes);
    //    }
    //    prevF1 = f1now;
    //}



    void updateAll(float delta) {

        if (!window) return;

        // Detectar mouse
        bool mouseNow =
            glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
        bool mousePressed = mouseNow && !prevMouseLeft;

        // Detectar teclado
        bool enterNow =
            glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
        bool escapeNow =
            glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

        bool enterPressed = enterNow && !prevEnter;
        bool escapePressed = escapeNow && !prevEscape;

        // Debug F1
        bool f1now = glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS;

        if (f1now && !prevF1) {

            debugHitboxes = !debugHitboxes;

            for (auto& e : entities) {
                e->setDebugHitbox(debugHitboxes);
            }

            if (jugador01) {
                jugador01->setDebugHitbox(debugHitboxes);
            }

            for (auto& t : terrenos) {
                t->setDebugWalls(debugHitboxes);
            }
        }

        prevF1 = f1now;
        bool interactNow = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
        bool interactPressed = interactNow && !prevInteract;
        // Si hay diálogo activo, el jugador no se mueve.
        if (dialogueBox.isActive()) {

            if (escapePressed) {
                dialogueBox.close();
            }
            else if (mousePressed || enterPressed || interactPressed) {
                dialogueBox.advance();
            }

            prevMouseLeft = mouseNow;
            prevEnter = enterNow;
            prevEscape = escapeNow;
            prevInteract = interactNow;     // <-- nuevo

            return;
        }




        // Actualización normal del mundo
        for (auto& e : entities) {
            e->update(delta);
        }

        if (jugador01) {
            glm::vec2 oldPos = jugador01->position;
            jugador01->update(delta);
            resolvePlayerCollisions(oldPos);
        }


        // Interacción con tecla: abrir el diálogo del NPC más cercano
        if (interactPressed && jugador01) {

            CollRect p = jugador01->getHitbox();

            glm::vec2 playerCenter(
                p.x + p.width * 0.5f,
                p.y + p.height * 0.5f
            );

            PersonajeNpc* nearest = nullptr;
            float bestDist = 1e9f;

            for (const auto& npc : entities) {

                PersonajeNpc* npcPtr = npc.get();

                if (!npcPtr || npcPtr->getDialogue().empty())
                    continue;

                CollRect hb = npcPtr->getHitbox();

                // Zona de interacción ampliada
                CollRect zone(
                    hb.x - INTERACT_RANGE,
                    hb.y - INTERACT_RANGE,
                    hb.width + 2.0f * INTERACT_RANGE,
                    hb.height + 2.0f * INTERACT_RANGE
                );

                if (!zone.intersects(p))
                    continue;

                glm::vec2 npcCenter(
                    hb.x + hb.width * 0.5f,
                    hb.y + hb.height * 0.5f
                );

                float d = glm::distance(playerCenter, npcCenter);

                if (d < bestDist) {
                    bestDist = d;
                    nearest = npcPtr;
                }
            }

            if (nearest) {
                dialogueBox.open(nearest->getDialogue());
            }
        }


        // Evento de clic sobre NPC
        if (mousePressed) {

            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            glm::vec2 logicalMouse;

            if (windowToLogical(mouseX, mouseY, logicalMouse)) {

                // Revisar desde el último NPC agregado
                // para priorizar los que se dibujan encima
                for (auto it = entities.rbegin(); it != entities.rend(); ++it) {

                    PersonajeNpc* npc = it->get();

                    if (!npc) continue;

                    if (npc->getHitbox().contains(logicalMouse.x, logicalMouse.y)) {

                        const auto& lines = npc->getDialogue();

                        if (!lines.empty()) {
                            dialogueBox.open(lines);
                        }

                        break;
                    }
                }
            }
        }

        prevMouseLeft = mouseNow;
        prevEnter = enterNow;
        prevEscape = escapeNow;
        prevInteract = interactNow;
    }


    //NOTA: PARA DIBUJAR TODOS LOS ELEMENTOS EN EL CICLO
    void drawAll() {
        for (auto& g : terrenos) {
            g->draw(proyection);
        }

        for (auto& e : entities) {
            // cada entidad podría traer su propia textura
            // aquí asumimos que Model almacena o referencia su textura
            e->draw(proyection);
            //e->drawHitbox(proyection);
        }

        // Dibujar jugador
        if (jugador01) {
            jugador01->draw(proyection);
        }


        for (auto& t : terrenos) {
            t->drawWalls(proyection);
        }












        // --- DIÁLOGO ---
        auto spriteShader = ResourceManager::GetShader("sprite");

        if (dialogueBox.isActive() && textRenderer && spriteShader) {
            dialogueBox.draw(proyection, *textRenderer);
        }




        
        
        //// --- PRUEBA DE TEXTO ---

        //auto outlineRenderer = ResourceManager::GetRenderer("outline");
        //auto spriteShader = ResourceManager::GetShader("sprite");

        //if (textRenderer && spriteShader) {

        //    // Fondo oscuro para que el texto blanco se vea sobre cualquier terreno.
        //    if (outlineRenderer) {
        //        outlineRenderer->DrawRect(
        //            glm::vec2(8.0f, 8.0f),
        //            glm::vec2(240.0f, 50.0f),
        //            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        //            proyection,
        //            true
        //        );
        //    }

        //    spriteShader->Use();
        //    spriteShader->PonMatriz4x4("projection", &proyection[0][0]);


        //    //if (dialogueBox.isActive() && textRenderer) {
        //    //    dialogueBox.draw(proyection, *textRenderer);
        //    //}
        //    textRenderer->DrawText(
        //        "Hola Mundo!\nABC abc 0123456789",
        //        glm::vec2(16.0f, 16.0f),
        //        10.0f,                 // alto de línea (~tamaño nativo)
        //        0.0f,                  // espaciado extra
        //        glm::vec3(1.0f)        // blanco
        //    );
        //}




        /*
        auto font = ResourceManager::GetTexture("font");
        auto spriteRenderer = ResourceManager::GetRenderer("sprite");
        auto spriteShader = ResourceManager::GetShader("sprite");

        if (!font) {
            std::cout << "No existe la textura font" << std::endl;
        }

        if (!spriteRenderer) {
            std::cout << "No existe el renderer sprite" << std::endl;
        }

        if (!spriteShader) {
            std::cout << "No existe el shader sprite" << std::endl;
        }
        //std::cout << "Textura, renderer y shader encontrados\n";
            spriteShader->Use();

            spriteShader->PonMatriz4x4(
                "projection",
                &proyection[0][0]
            );
            spriteRenderer->DrawSpriteRegion(
                font.get(),
                glm::vec2(50.0f, 40.0f),
                glm::vec2(100.0f, 115.0f),
                0.0f,
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec3(1.0f)
            );*/
            
        








        //std::cout << "posicion Jugador: X = "<< jugador01->position.x << "Y = " << jugador01->position.y << '\n';
        //std::cout << "posicion box: X = " << jugador01->hitbox.x << "Y = " << jugador01->hitbox.y << '\n';
        //std::cout << "size Jugador: size X = " << jugador01->size.x << " size Y = " << jugador01->size.y << '\n';
        //std::cout << "size box: size X = " << jugador01->hitbox.width << " size Y = " << jugador01->hitbox.height << '\n';
        //system("cls");
        //jugador01->drawHitbox(proyection);


    }
    //NOTA: LIBERA MEMORIA DE HEAP (new)
    void liberarMemoria() {

        for (auto& e : entities) {
            e->liberarMemoria();
        }
        if (jugador01) {
        jugador01->liberarMemoria();
        }

        for (auto& t : terrenos) {
            t->liberarMemoria();
        }
        //delete input;
    }






    // Añade una pared al último terreno agregado.
    void agregarPared(float x, float y, float w, float h) {
        if (!terrenos.empty()) terrenos.back()->addWall(x, y, w, h);
    }

    bool isBlocked(const CollRect& r) {
        for (auto& t : terrenos) {
            for (const auto& w : t->getWalls()) {
                if (r.overlaps(w)) return true;
            }
        }
        if (npcsSolid) {
            for (auto& e : entities) {
                if (r.overlaps(e->getHitbox())) return true;
            }
        }
        return false;
    }


    // Corrige la posición del jugador si el movimiento lo metió en una pared.
// Se resuelve por ejes, así que puede deslizarse a lo largo de la pared.
    void resolvePlayerCollisions(const glm::vec2& oldPos) {
        if (!jugador01) return;

        glm::vec2 newPos = jugador01->position;
        if (newPos == oldPos) return;

        // Eje X
        jugador01->position = glm::vec2(newPos.x, oldPos.y);
        jugador01->updateHitbox();
        if (isBlocked(jugador01->getHitbox())) {
            jugador01->position.x = oldPos.x;
        }

        // Eje Y
        jugador01->position.y = newPos.y;
        jugador01->updateHitbox();
        if (isBlocked(jugador01->getHitbox())) {
            jugador01->position.y = oldPos.y;
        }

        jugador01->updateHitbox();
    }


    bool windowToLogical(
        double mouseX,
        double mouseY,
        glm::vec2& logicalPosition
    ) const {

        int windowWidth, windowHeight;

        glfwGetWindowSize(
            window,
            &windowWidth,
            &windowHeight
        );

        if (windowWidth <= 0 || windowHeight <= 0) {
            return false;
        }

        float scale = std::floor(std::min(
            windowWidth / LOGICAL_WIDTH,
            windowHeight / LOGICAL_HEIGHT
        ));

        if (scale < 1.0f) {
            scale = std::min(
                windowWidth / LOGICAL_WIDTH,
                windowHeight / LOGICAL_HEIGHT
            );
        }

        float viewportWidth = LOGICAL_WIDTH * scale;
        float viewportHeight = LOGICAL_HEIGHT * scale;

        float offsetX = (windowWidth - viewportWidth) * 0.5f;
        float offsetY = (windowHeight - viewportHeight) * 0.5f;

        // Ignorar clics fuera del área del juego
        if (mouseX < offsetX || mouseX >= offsetX + viewportWidth ||
            mouseY < offsetY || mouseY >= offsetY + viewportHeight) {
            return false;
        }

        logicalPosition.x = (float)(mouseX - offsetX) / scale;
        logicalPosition.y = (float)(mouseY - offsetY) / scale;

        return true;
    }

    //*********SIN USAR*********
    //InputClass* input;
    //Model* personaje1;

};

#endif // SCENE_H










//void addEntity(std::unique_ptr<Personaje> m) {
    //entities.emplace_back(std::move(m));
//}