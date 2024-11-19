// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// cargo.c
// Modulo de Implementacion de Cargos

#include "cargo.h"
#include "persona.h"
#include <string.h>
#include <iostream>

using namespace std;

Cargo CrearCargo(Cadena nombre) {
    Cargo cargo = new(nodo_cargo);

    if (cargo != NULL) {
        cargo->nombre = strdup(nombre);
        if (cargo->nombre == NULL) {
            free(cargo);
            return NULL;
        } else {
            cargo->cargo_hermano = NULL;
            cargo->primer_subcargo = NULL;
            cargo->personas = NULL;
            return cargo;
        }
    } else {
        return NULL;
    }
}

Cargo GetCargo(Cargo cargo, Cadena nombre) {
    if (cargo != NULL) {
        // se compara si las cadenas son iguales independientemente de si estan en mayusculas o minusculas
        if (strcasecmp(cargo->nombre, nombre) == 0) {
            return cargo;
        }

        // recursivamente se recorre el primer subcargo y los cargos hermanos
        Cargo cargoEncontrado = GetCargo(cargo->primer_subcargo, nombre);

        if (cargoEncontrado != NULL) {
            return cargoEncontrado;
        } else {
            return GetCargo(cargo->cargo_hermano, nombre);
        }
    }
    return NULL;
}

void LimpiarCargo(Cargo cargo) {
    if (cargo == NULL) {
        return;
    } else {
        // se limpian a los subcargos o a los cargos hermanos
        LimpiarCargo(cargo->primer_subcargo);
        LimpiarCargo(cargo->cargo_hermano);

        // inicialmente si hay un cargo se limpian a las personas en ese cargo
        LimpiarPersona(cargo->personas);

        // al final se libera de memoria el valor del nodo cargo (el nombre) y por ultimo el nodo mismo
        free(cargo->nombre);
        free(cargo);
    }
}

Cargo GetCargoPadre(Cargo cargoPadre, Cargo cargoBuscado) {
    if (cargoPadre == NULL) {
        // caso base, el arbol esta vacio
        return NULL;
    } else {
        if (cargoPadre->primer_subcargo == cargoBuscado || cargoPadre->cargo_hermano == cargoBuscado) {
            // se encontro al padre si el hijo o el hermano tienen a su descendiente como el cargo buscado
            return cargoPadre; 
        } else {

            // como en las demas recursiones de los cargos, vamos por los hijos y los hermanos
            Cargo padre = GetCargoPadre(cargoPadre->primer_subcargo, cargoBuscado);

            if (padre == NULL) {
                return GetCargoPadre(cargoPadre->cargo_hermano, cargoBuscado);
            } else {
                return padre;
            }
        }
    }
}

Cargo BuscarCargoPorCI(Cargo cargo, Cadena ci) {
    if (cargo == NULL) {
        // caso base: ya no hay cargos para buscar
        return NULL;
    } else {
        // nos fijamos si la persona a la que apunta el cargo tiene el mismo ci del que pasamos por parametro, sino lo tiene, entonces vamos a la siguiente persona
        Persona persona = cargo->personas;
        while (persona != NULL) {
            if (strcmp(persona->ci, ci) == 0) {
                return cargo;
            }
            persona = persona->sig;
        }

        // vamos recursivamente por los hijos y los hermanos
        Cargo cargoEncontrado = BuscarCargoPorCI(cargo->primer_subcargo, ci);
        if (cargoEncontrado != NULL) {
            return cargoEncontrado;
        } else {
            return BuscarCargoPorCI(cargo->cargo_hermano, ci);
        }
    }
}

bool LimpiarPersonaDelCargo(Cargo cargo, Cadena ci) {
    Persona ant = NULL;
    Persona sig = cargo->personas;
    // recorremos las personas que estan en el cargo
    while (sig != NULL) {
        if (strcmp(sig->ci, ci) == 0) {
            if (ant == NULL) {
                cargo->personas = sig->sig;
            } else {
                ant->sig = sig->sig;
            }
            // limpiamos los datos del nodo y el nodo al final
            free(sig->nom);
            free(sig->ci);
            free(sig);
            return true;
        }
        ant = sig;
        sig = sig->sig;
    }
    // no se encontró la persona
    return false;
}

void ListarCargosPadres(Cargo cargoMaximo, Cargo cargo) {
    if (cargoMaximo == NULL || cargo == NULL) {
        // caso base, no hay mas cargos padres
        return;
    } else {
        // buscamos el cargo padre del cargo al que queremos listarle los supercargos
        Cargo padre = GetCargoPadre(cargoMaximo, cargo);
        if (padre == NULL) {
            return;
        } else {
            // listamos recursivamente los padres del cargo padre si tiene
            ListarCargosPadres(cargoMaximo, padre);
            cout << padre->nombre << "\n";
        }
    }
}

void ListarJerarquiaDeCargos(Cargo cargo, int profundidad) {
    if (cargo != NULL)  {
        // identa segun la profundidad, mientras mas profundo sea el cargo mas identacion hay
        for (int i = 0; i < profundidad; i++) {
            cout << "      ";
        }
        cout << cargo->nombre << endl;
        // se imprimen los subcargos y los cargos hermanos
        ListarJerarquiaDeCargos(cargo->primer_subcargo, profundidad + 1);
        ListarJerarquiaDeCargos(cargo->cargo_hermano, profundidad);
    }
}