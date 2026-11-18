#ifndef NIVELJUEGO_H
#define NIVELJUEGO_H
#include "Scene.h"
#include "Nivel.h"


class NivelJuego : public Nivel {
public:
    ///////////////////////////
    ////////ATRIBUTOS/////////

    ///////////////////////////
    ////////CONSTRUCTORES//////

    NivelJuego();

    ///////////////////////////
    /////SETTERS Y GETTERS/////

    ////////////////////////
    ////////METODOS/////////

    bool init() override;
    void update(float dt) override;
    void draw() override;
    void unload() override;

    void Run() override;

    bool isFinished() const override;
    int nextLevel() const override;

private:
    ///////////////////////////
    ////////ATRIBUTOS -///////

    Scene scene;

    bool finished = false;
    int next = -1;
};

#endif // NIVELJUEGO_H