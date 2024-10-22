// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.c
// Modulo de Implementacion de la Empresa

#include "empresa.h"
#include <string.h>
#include <iostream>

using namespace std;

struct nodo_cargo {
    Cadena nombre;
    struct tipo_persona* personas;
    struct nodo_cargo* primer_subcargo;
    struct nodo_cargo* cargo_hermano;
};

struct nodo_empresa {
    Cargo cargo_maximo;
};

struct tipo_persona {
    Cadena ci;
    Cadena nom;
    struct tipo_persona* sig;
};

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

void ListarJerarquiaAux(Cargo cargo, int profundidad) {
    if (cargo != NULL)  {
        // identa segun la profundidad, mientras mas profundo sea el cargo mas identacion hay
        for (int i = 0; i < profundidad; i++) {
            cout << " " << "\n";
        }
        cout << cargo->nombre << endl;
        // se imprimen los subcargos y los cargos hermanos
        ListarJerarquiaAux(cargo->primer_subcargo, profundidad + 1);
        ListarJerarquiaAux(cargo->cargo_hermano, profundidad);
    }
}

Cargo GetCargo(Cargo cargo, Cadena nombre) {
    if (cargo != NULL) {
        // se compara si las cadenas son iguales independientemente de si estan en mayusculas o minusculas
        if (strcasecmp(cargo->nombre, nombre) == 0) {
            return cargo;
        }

        // recursivamente se recorre el primer subcargo y los cargos hermanos
        Cargo foundCargo = GetCargo(cargo->primer_subcargo, nombre);

        if (foundCargo != NULL) {
            return foundCargo;
        }

        return GetCargo(cargo->cargo_hermano, nombre);
    }
    return NULL;
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

bool EliminarPersonaAux(Cargo cargo, Cadena ci) {
    if (cargo == NULL) {
        return false;
    } else {
        if (LimpiarPersonaDelCargo(cargo, ci)) {
            return true;
        }
        // elimina el primer subcargo y sus hermanos
        if (EliminarPersonaAux(cargo->primer_subcargo, ci)) {
            return true;
        }
        // continua eliminando los cargos hermanos
        return EliminarPersonaAux(cargo->cargo_hermano, ci);
    }
}

TipoRet CrearOrg(Empresa &e, Cadena cargo) {
    // cuando se crea la org, la empresa no esta inicializada, entonces la inicializamos acá
    if (e == NULL) {
        e = new(nodo_empresa);
        if (e == NULL) {
            return ERROR;
        }
        e->cargo_maximo = NULL;
    }

    if (e->cargo_maximo == NULL) {
        Cargo nuevoCargo = new(nodo_cargo);

        // si no se pudo asignar memoria a nuevoCargo, retornar error
        if (nuevoCargo == NULL) {
            return ERROR;
        }

        // con la funcion strdup copiamos los chars que conforman el cargo y se lo asignamos al valor del nodo
        nuevoCargo->nombre = strdup(cargo);

        nuevoCargo->primer_subcargo = NULL;
        nuevoCargo->cargo_hermano = NULL;
        nuevoCargo->personas = NULL;

        e->cargo_maximo = nuevoCargo;

        return OK;
    }

    return ERROR;

}

TipoRet EliminarOrg(Empresa &e){
    if (e == NULL) {
        // no hay org creada todavia
        return ERROR;
    } else {
        // con esta funcion vamos recusivamente primero limpiando a las personas de los cargos de la empresa
        // luego se limpian los cargos
        LimpiarCargo(e->cargo_maximo);

        // por ultimo, se limpia la empresa en si y se setea a null por si se quiere volver a crear
        free(e);
        e = NULL;
    }

    return OK;
}

TipoRet NuevoCargo(Empresa &e, Cadena cargoPadre, Cadena nuevoCargo){
// Insertar un nuevo cargo como dependiente de otro ya existente.
// El nuevo cargo no debe existir en el sistema.
	return NO_IMPLEMENTADA;
}

TipoRet EliminarCargo(Empresa &e, Cadena cargo){
// Eliminar un cargo, junto con sus subcargos y personas asociadas.
// Elimina un cargo en la empresa si cargo ya existe en la misma.
// En otro caso la operación quedará sin efecto.
// Si el cargo a eliminar posee subcargos, éstos deberán ser eliminados también, así como
// las personas asociadas a cada uno de los cargos suprimidos.
	return NO_IMPLEMENTADA;
}

TipoRet ListarCargosAlf(Empresa e){
// Listar todos los cargos ordenados alfabéticamente.
// Lista todos los cargos de la empresa ordenados alfabéticamente por nombre del cargo. 
	return NO_IMPLEMENTADA;
}

TipoRet ListarJerarquia(Empresa e){
    if (e == NULL) {
        cout << "ERROR: empresa vacia" << "\n";
        return ERROR;  // no se creo la empresa todavia
    } else {
        // se ejecuta la funcion auxiliar que recursivamente imprime la jerarquia de la empresa
        // pasamos el nodo cargo raiz (cargo principal de la empresa) para imprimir los hijos
        // por ende arrancamos en profundidad 0
        ListarJerarquiaAux(e->cargo_maximo, 0);  
        return OK;
    }
}

TipoRet AsignarPersona(Empresa &e, Cadena cargo, Cadena nom, Cadena ci){
    // precondición: tanto la empresa como al menos un cargo máximo fueron creados
    Cargo cargo_a_asignar = GetCargo(e->cargo_maximo, cargo);
    if (cargo_a_asignar == NULL) {
        // el cargo no existe
        return ERROR;
    } else {
        // la persona que se iba a ingresar ya estaba en ese carfgo
        if (PersonaAsignada(e->cargo_maximo, ci)) {
            return ERROR;
        } else {
            Persona per = new(tipo_persona);
            // si falla la asignación de memoria:
            if (per == NULL) {
                return ERROR;
            } else {
                // solo asignamos una persona al cargo con esta funcion, por ende el siguiente nodo es null.
                per->sig = NULL;
                // copiamos las Cadenas de ci y nom al nodo de la nueva persona que vamos a asignar al cargo
                per->ci = strdup(ci);
                per->nom = strdup(nom);

                // agregamos a la per creada a la lista de personas que ocupan el cargo
                per->sig = cargo_a_asignar->personas;
                cargo_a_asignar->personas = per;

                return OK;
            }
        }

    }

}

TipoRet EliminarPersona(Empresa &e, Cadena ci){
    // precondicion: la empresa existe
    // funcion auxiliar que busca la parsona entre los cargos de la empresa y elimina la persona con ci en ellos
    // rertorna verdadero si se encontro la persona y se elimino de los cargos
    if (EliminarPersonaAux(e->cargo_maximo, ci)) {
        // la persona se encontro en la funcion y fue eliminada de sus cargos y finalmente liberado el nodo de persona
        return OK;
    } else {
        // no se encontro la persona por su ci
        return ERROR;
    }
}

TipoRet ReasignarPersona(Empresa &e, Cadena cargo, Cadena ci){
// Reasignar una persona a un nuevo cargo.
// Reasigna una persona de la empresa de cédula ci al nuevo cargo de nombre cargo
// siempre que el cargo exista en la empresa y esa persona no este ya asignada a
// dicho cargo. En caso contrario la operación qu|edará sin efecto.
	return NO_IMPLEMENTADA;
}

TipoRet ListarPersonas(Empresa e, Cadena cargo){
    // precondición: la empresa existe y esta inicializada, el cargo tambienn existe

    Cargo cargo_a_listar = GetCargo(e->cargo_maximo, cargo);

    if (cargo_a_listar != NULL) {
        Persona per = cargo_a_listar->personas;

        if (per == NULL) {
            // no hay nodo de personas asignadas a este cargo
            return OK;


        } else {

            cout << "Listado de personas asignadas a " << cargo << ":\n";
            cout << "----------------------------------------------\n";
            while (per != NULL) {
                cout << per->nom << " - " << per->ci << "\n";
                per = per->sig;
            }

            return OK;
        }

    }

    // el cargo no existe
    return ERROR;

}

TipoRet ListarSuperCargos (Empresa e, Cadena cargo){
// Dado un cargo listar los cargos que lo anteceden.
// Lista todas los cargos que anteceden, en la jerarquía, al cargo de nombre cargo.
	return NO_IMPLEMENTADA;
}