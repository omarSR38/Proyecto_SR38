#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Entidades/Model.h"
#include "Entidades/Personaje.h"
#include "Entidades/Terreno.h"
#include "Entidades/Jugador/Jugador.h"
#include "Entidades/PersonajeNpc.h"

class Scene {
public:
    // Resolución lógica (SNES)
    float LOGICAL_WIDTH = 256.00f;
    float LOGICAL_HEIGHT = 224.00f;
    // Tamaño de ventana física (Undertale-style)
    int WINDOW_WIDTH = 640;
    int WINDOW_HEIGHT = 480;
    // apuntador inicial original<------
    OpenGLClass gl;
    GLFWwindow* window;
    InputClass* input;
    //Model* personaje1;
    glm::mat4 proyection;
    std::vector<std::unique_ptr<PersonajeNpc>> entities;
    std::vector<std::unique_ptr<Terreno>> terrenos;
    Jugador* jugador01;
    Scene() {}

    ~Scene() {}

    bool initializeScene() {
        // 1. Inicializar OpenGL y ventana
        if (!gl.InitializeGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "Proyecto SR38", false)) return false;
        input = new InputClass(LOGICAL_WIDTH, LOGICAL_HEIGHT);
        gl.SetInput(input);
        window = gl.GetWindow();
        // Proyección ortográfica lógica
        proyection = glm::ortho(0.0f, LOGICAL_WIDTH, LOGICAL_HEIGHT, 0.0f);

        terrenos.emplace_back(std::make_unique<Terreno>(
            glm::vec2(0, 0), glm::vec2(LOGICAL_WIDTH, LOGICAL_HEIGHT),
            &gl,
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/house.png",
            proyection
        ));

        entities.emplace_back(std::make_unique<PersonajeNpc>(
            glm::vec2(30, 30), glm::vec2(22, 26),
            &gl,
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/npc.png",
            proyection
        ));


        jugador01 = new Jugador(
            glm::vec2(100, 100), glm::vec2(22, 26),
            &gl,
            "shaders/sprite.vs",
            "shaders/sprite.fs",
            "assets/player.png",
            proyection
        
        );

        //entities.emplace_back(std::make_unique<Personaje>(
//    glm::vec2(0, 0), glm::vec2(LOGICAL_WIDTH, LOGICAL_HEIGHT),
//    &gl,
//    "C:/Users/eduar/source/repos/Proyecto_SR38/shaders/sprite.vs",
//    "C:/Users/eduar/source/repos/Proyecto_SR38/shaders/sprite.fs",
//    "C:/Users/eduar/source/repos/Proyecto_SR38/assets/house.png",
//    proyection
//));

        //terrenos.emplace_back(std::make_unique<Terreno>(
        //    glm::vec2(0, 0), glm::vec2(LOGICAL_WIDTH, LOGICAL_HEIGHT),
        //    &gl,
        //    "C:/Users/eduar/source/repos/Proyecto_SR38/shaders/sprite.vs",
        //    "C:/Users/eduar/source/repos/Proyecto_SR38/shaders/sprite.fs",
        //    "C:/Users/eduar/source/repos/Proyecto_SR38/assets/house.png",
        //    proyection
        //));

        return true;
    }

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


    void liberarMemoria() {
        for (auto& e : entities) {
            e->liberarMemoria();
        }
        jugador01->liberarMemoria();

        for (auto& t : terrenos) {
            t->liberarMemoria();
        }
    }
};

#endif // SCENE_H










//void addEntity(std::unique_ptr<Personaje> m) {
    //entities.emplace_back(std::move(m));
//}