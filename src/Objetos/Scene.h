#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Terreno.h"
#include "Jugador/Jugador.h"
#include "PersonajeNpc.h"
//SIN USAR (PARA REGISTRO):
//#include "InputClass.h"
//#include "Model.h"
//#include "Personaje.h"

class Scene {
public:
    //CONSTANTES:
    // Resolución lógica (SNES)
    float LOGICAL_WIDTH = 256.00f;
    float LOGICAL_HEIGHT = 224.00f;
    // Tamaño de ventana física (Undertale-style)
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;

    // ATRIBUTOS A USAR:
    //NOTA: gl variable original de OpenGLClass
    OpenGLClass gl;
    //NOTA: proyection matriz original de proyeccion
    glm::mat4 proyection;
    //NOTA: listado variable de personajesNPC en la escena
    std::vector<std::unique_ptr<PersonajeNpc>> entities;
    //NOTA: listado variable de fondos para un mismo terreno
    std::vector<std::unique_ptr<Terreno>> terrenos;
    //NOTA: jugador manejador
    Jugador* jugador01;
    //NOTA: Objeto dependiente de GLFW
    GLFWwindow* window;
    //NOTA: Objeto para mantener imagen en cambio de ventana
    PixelPerfectRenderer pixelRenderer;
    InputClass* input;

    //CONTRSTRUCTORES:
    Scene() {
        gl = OpenGLClass();
        jugador01 = nullptr;
        window = nullptr;
        proyection = NULL;
    }
    ~Scene() {
        liberarMemoria();
    }

    //SET Y GET:

    //METODOS:
    bool initializeScene() {
        // 1. Inicializar OpenGL y ventana
        if (!gl.InitializeGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "Proyecto SR38", false)) return false;
        input = (new InputClass(LOGICAL_WIDTH, LOGICAL_HEIGHT));
        gl.SetInput(input);
        window = gl.GetWindow();
        // Proyección ortográfica lógica
        proyection = glm::ortho(0.0f, LOGICAL_WIDTH, LOGICAL_HEIGHT, 0.0f);
        //NOTA: PARA MANTENER RELACION DE IMAGEN
        pixelRenderer = PixelPerfectRenderer(&gl, window, LOGICAL_WIDTH, LOGICAL_HEIGHT);
        if (!pixelRenderer.Initialize());
        return true;
    }

    void agregaJugador(const glm::vec2& pos, const glm::vec2& sz,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_) {
        jugador01 = new Jugador(
            pos, sz,
            &gl,
            VSPath_,
            FSPath_,
            imagenPath_,
            proyection
        );
    }

    void agregarEntidad(const glm::vec2& pos, const glm::vec2& sz,
        const std::string& VSPath_, const std::string& FSPath_,
        const std::string& imagenPath_) {
        entities.emplace_back(std::make_unique<PersonajeNpc>(
            pos, sz,
            &gl,
            VSPath_,
            FSPath_,
            imagenPath_,
            proyection
        ));
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

    //PARA GRAFICAR
    //NOTA: PARA CARGAR TODOS LOS ELEMENTOS EN EL CICLO
    void updateAll(float delta) {
        for (auto& e : entities) e->update(delta);
        // detección simple de colisiones
        for (size_t i = 0; i < entities.size(); ++i) {
            for (size_t j = i + 1; j < entities.size(); ++j) {
                if (entities[i]->hitbox.intersects(entities[j]->hitbox)) {
                    // manejar colisión (por simplicidad, solo reportar)
                    // could call onCollision
                }
            }
        }
        jugador01->update(delta);
    }

    //NOTA: PARA DIBUJAR TODOS LOS ELEMENTOS EN EL CICLO
    void drawAll(float delta) {
        for (auto& g : terrenos) {
            g->draw(proyection);
        }
        updateAll(delta);
        for (auto& e : entities) {
            // cada entidad podría traer su propia textura
            // aquí asumimos que Model almacena o referencia su textura
            e->draw(proyection);
        }
        jugador01->draw(proyection);


    }

    //NOTA: LIBERA MEMORIA DE HEAP (new)
    void liberarMemoria() {

        for (auto& e : entities) {
            e->liberarMemoria();
        }
        jugador01->liberarMemoria();

        for (auto& t : terrenos) {
            t->liberarMemoria();
        }
        //delete input;
    }

    //SIN USAR (PARA REGISTRO):
    //InputClass* input;
    //Model* personaje1;

};

#endif // SCENE_H










//void addEntity(std::unique_ptr<Personaje> m) {
    //entities.emplace_back(std::move(m));
//}