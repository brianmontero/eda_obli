// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// listaCargo.c
// Modulo de Implementacion de lista de cargos

#include "cargo.h"
#include "listaCargo.h"
#include <string.h>
#include <iostream>

using namespace std;

ListaCargos CrearListaCargos(int capacidadInicial) {
    // inicializamos la lista
    ListaCargos lista = new nodo_lista_cargos;
    if (lista == NULL) {
        return NULL;
    } else {
        // inicializamos el array de cargos, a priori agregamos la capacidad que se nos paso por parametros
        lista->cargos = new Cargo[capacidadInicial];
        if (lista->cargos == NULL) {
            // si hubo un error creando la lista, limpiamos la lista
            delete lista;
            return NULL;
        } else {
            lista->cantCargos = 0;
            lista->capacidad = capacidadInicial;
            return lista;
        }
    }
}

void LimpiarListaCargos(ListaCargos lista) {
    if (lista == NULL) {
        return;
    } else {
        // liberamos el arreglo de cargos
        delete[] lista->cargos;
        // liberamos la lista
        delete lista;
    }
}

void AgregarCargoALista(ListaCargos lista, Cargo cargo) {
    if (lista == NULL || cargo == NULL) {
        return;
    } else {
        // verificamos si tenemos que agrandar la capacidad del array
        if (lista->cantCargos >= lista->capacidad) {
            int nuevaCapacidad = lista->capacidad * 2;
            Cargo* nuevosCargos = new Cargo[nuevaCapacidad];
            for (int i = 0; i < lista->cantCargos; i++) {
                nuevosCargos[i] = lista->cargos[i];
            }
            delete[] lista->cargos;
            lista->cargos = nuevosCargos;
            lista->capacidad = nuevaCapacidad;
        }

        // Agregar el nuevo cargo
        lista->cargos[lista->cantCargos++] = cargo;
    }

}

void RecolectarCargos(Cargo cargo, ListaCargos lista) {
    if (cargo == NULL) {
        return;
    } else {
        // Agregar el cargo actual a la lista
        AgregarCargoALista(lista, cargo);

        // Recursivamente recolectar subcargos e hijos
        RecolectarCargos(cargo->primer_subcargo, lista);
        RecolectarCargos(cargo->cargo_hermano, lista);
    }
}

int CompararCargos(const void* a, const void* b) {
    // funcion requerida para el qsort en empresa
    Cargo cargoA = *(Cargo*)a;
    Cargo cargoB = *(Cargo*)b;
    return strcasecmp(cargoA->nombre, cargoB->nombre);
}

void ListarCargosOrdenados(ListaCargos lista) {
    if (lista == NULL) {
        return;
    } else {
        for (int i = 0; i < lista->cantCargos; i++) {
            cout << lista->cargos[i]->nombre << "\n";
        }
    }

}