#include "ConjuntoPersonajesNpc.h"

ConjuntoPersonajesNpc::ConjuntoPersonajesNpc() {
	INICIO = nullptr;
}

ConjuntoPersonajesNpc::~ConjuntoPersonajesNpc() {}



void ConjuntoPersonajesNpc::agregarNodoPNpc(PersonajeNpc* newPersonajeNpc) {
	if (INICIO == nullptr) {
		nodoPersonajeNpc* nuevoNpc = new nodoPersonajeNpc;
		nuevoNpc->PersonajeNpc = newPersonajeNpc;
		nuevoNpc->nodoAnterior = nullptr;
		nuevoNpc->nodoSiguiente = nullptr;
		INICIO = nuevoNpc;
	}else {
		nodoPersonajeNpc* nuevoNpc = new nodoPersonajeNpc;
		nuevoNpc->PersonajeNpc = newPersonajeNpc;
		nuevoNpc->nodoAnterior = nullptr;
		nuevoNpc->nodoSiguiente = nullptr;

		nodoPersonajeNpc* guardia = INICIO;
		while (guardia->nodoSiguiente != nullptr) {
			guardia = guardia->nodoSiguiente;
		}
		nuevoNpc->nodoAnterior = guardia;


	}
}


