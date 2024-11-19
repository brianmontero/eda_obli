#ifndef CARGO_H
#define CARGO_H

#include "definiciones.h"

typedef struct nodo_cargo * Cargo;

struct nodo_cargo {
    Cadena nombre;
    struct tipo_persona* personas;
    struct nodo_cargo* primer_subcargo;
    struct nodo_cargo* cargo_hermano;
};

Cargo CrearCargo(Cadena nombre);
// función que toma un nombre y crea el cargo con ese nombre

Cargo GetCargo(Cargo cargo, Cadena nombre);
// se le pasa un cargo y el nombre del cargo y se fija recursivamente en sus subcargos y cargos hermanos si existe

bool PersonaAsignada(Cargo cargo, Cadena ci);
// chequea que la CI de la persona se encuentre (o no) en el cargo que le pasamos

void LimpiarCargo(Cargo cargo);
// con esta funcion vamos recusivamente primero limpiando a las personas de los cargos de la empresa
// luego se limpian los cargos

Cargo GetCargoPadre(Cargo cargoPadre, Cargo cargoBuscado);
// a esta funcion le pasamos un cargo padre y busca recursivamente el padre del cargoBuscado para retornarlo

bool LimpiarPersonaDelCargo(Cargo cargo, Cadena ci);
// busca a la persona por su cédula en el arbol de cargo y libera la memoria si la encuentra, retorna true si logró eliminarla o false en el caso contrario

void ListarCargosPadres(Cargo cargoMaximo, Cargo cargo);
// funcion auxiliar para buscar los padres e imprimirlos 

void ListarJerarquiaDeCargos(Cargo cargo, int profundidad);
// funcion auxiliar para listar la jerarquia de la empresa, va recursivamente por todos los hijos y hermanos y los identa segun su descendencia (la profundidad)

Cargo BuscarCargoPorCI(Cargo cargo, Cadena ci);
// busca un cargo por el ci de una persona (si hay una persona con la cedula "ci" ocupando el cargo)

#endif