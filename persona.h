#ifndef PERSONA_H
#define PERSONA_H

#include "definiciones.h"
#include "cargo.h"

typedef struct tipo_persona * Persona;

struct tipo_persona {
    Cadena ci;
    Cadena nom;
    struct tipo_persona* sig;
};

Persona CrearPersona(Cadena nombre, Cadena ci);
// crea una persona y la inicializa con el nombre y la cedula pasada por parametros, luego la retorna

void LimpiarPersona(Persona per);
// Limpia a la persona si existe (libera de la memoria la información del nodo y finalmente el nodo en si)

bool PersonaAsignada(Cargo cargo, Cadena ci);
// retorna verdadero si la persona con cedula "ci" fue asignada al cargo "cargo"

#endif