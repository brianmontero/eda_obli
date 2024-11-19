// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// persona.c
// Modulo de Implementacion de Persona

#include "persona.h"
#include "cargo.h"
#include <string.h>
#include <iostream>

using namespace std;

Persona CrearPersona(Cadena nombre, Cadena ci) {
    Persona persona = new(tipo_persona);
    if (persona == NULL) {
        return NULL;  // Return NULL if memory allocation fails
    }

    // Allocate memory for the name and ID, and copy the values
    persona->nom = strdup(nombre);
    persona->ci = strdup(ci);
    if (persona->nom == NULL || persona->ci == NULL) {
        // Free allocated memory if any allocation fails
        free(persona->nom);
        free(persona->ci);
        free(persona);
        return NULL;
    }

    // Initialize the next pointer
    persona->sig = NULL;

    return persona;  // Return the pointer to the new Persona
}

void LimpiarPersona(Persona per) {
    if (per == NULL) {
        return;
    } else {
        // liberamos a la memoria de los datos del nodo persona
        free(per->nom);
        free(per->ci);

        // va al siguiente nodo y limpia la siguiente persona si hay
        LimpiarPersona(per->sig);

        // finalmente se libera al nodo entero
        free(per);
    }
}

bool PersonaAsignada(Cargo cargo, Cadena ci) {
    if (cargo != NULL) {
        Persona per = cargo->personas;
        // iteramos la lista de personas asignadas al cargo hasta encontrarla por su ci
        while (per != NULL) {
            // si la ci de la persona es igual a la ci del parametro entonces la encontramos
            if (strcmp(per->ci, ci) == 0) {
                return true;
            }
            per = per->sig;
        }

        // se chequea si la persona esta asignada tanto para el primer subcargo del cargo y para los cargos hermanos
        if (PersonaAsignada(cargo->primer_subcargo, ci)) {
            return true;
        }

        return PersonaAsignada(cargo->cargo_hermano, ci);
    }

    return false;

}
