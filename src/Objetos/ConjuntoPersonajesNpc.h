#ifndef CONJUNTOPERSONAJESNPC_H
#define CONJUNTOPERSONAJESNPC_H

#include "PersonajeNpc.h"


class ConjuntoPersonajesNpc {
public:
    ConjuntoPersonajesNpc();
    ~ConjuntoPersonajesNpc();

    void agregarNodoPNpc(PersonajeNpc* newPersonajeNpc);


private:
    struct nodoPersonajeNpc {
        PersonajeNpc* PersonajeNpc;
        nodoPersonajeNpc* nodoAnterior;
        nodoPersonajeNpc* nodoSiguiente;
    };


    nodoPersonajeNpc* FINAL;
    nodoPersonajeNpc* INICIO;

};

#endif