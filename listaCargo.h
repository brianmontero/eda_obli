#ifndef LISTACARGO_H
#define LISTACARGO_H

#include "definiciones.h"

typedef struct nodo_lista_cargos * ListaCargos;

struct nodo_lista_cargos {
    Cargo* cargos;
    int cantCargos;
    int capacidad;
};

ListaCargos CrearListaCargos(int capacidadInicial);
// crea una lista de cargos, la inicializa con la cantidad y cantCargos pasadas por parametros y la retorna

void ListarCargosOrdenados(ListaCargos lista);
// función que lista los cargos una vez fueron ordenados

int CompararCargos(const void* a, const void* b);
// funcion requerida por qsort para comparar los elementos y definir su ordenacion alfabetica

void RecolectarCargos(Cargo cargo, ListaCargos lista);
// a esta funcion se le pasan todos los cargos de la empresa y va añadiendolos al array de cargos

void AgregarCargoALista(ListaCargos lista, Cargo cargo);
// funcion que inserta el cargo en la lista, define la cantidad de cargos dinamicamente y va agrandando el array si es necesario

void LimpiarListaCargos(ListaCargos lista);
// funcion para liberar la memoria de la lista de cargos que creamos

#endif