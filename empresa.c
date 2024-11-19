// Estructuras de Datos y Algoritmos - Curso 2024
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// empresa.c
// Modulo de Implementacion de la Empresa

#include "empresa.h"
#include "cargo.h"
#include "persona.h"
#include <string.h>
#include <iostream>

using namespace std;

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
    // buscamos el cargo padre
    Cargo padre = GetCargo(e->cargo_maximo, cargoPadre);
    if (padre != NULL) {
        if (GetCargo(e->cargo_maximo, nuevoCargo) != NULL) {
            // si el cargo ya existe entonces retornamos error
            return ERROR;
        } else {
            // creamos el cargo
            Cargo cargoCreado = CrearCargo(nuevoCargo);

            if (cargoCreado == NULL) {
                return ERROR;
            } else {
                // si el primer hijo del cargo padre esta vacio, entonces lo asignamos
                if (padre->primer_subcargo == NULL) {
                    padre->primer_subcargo = cargoCreado;
                } else {
                    // si el padre ya tenía un hijo, entonces vamos hasta el ultimo hijo del padre y lo agregamos como hermano
                    Cargo hermano = padre->primer_subcargo;
                    while (hermano->cargo_hermano != NULL) {
                        hermano = hermano->cargo_hermano;
                    }
                    hermano->cargo_hermano = cargoCreado;
                }
                return OK;
            }

        }


    } else {
        return ERROR;
    }
}

TipoRet EliminarCargo(Empresa &e, Cadena cargo){
    // buscamos el cargo a eliminar
    Cargo cargoEncontrado = GetCargo(e->cargo_maximo, cargo);

    if (cargoEncontrado == NULL) {
        // no se encontro el cargo
        return ERROR;
    } else {
        // si el cargo a eliminar es el cargo maximo de la empresa, entonces limpiamos recursivamente todos los cargos hijos/hermanos
        // y por ultimo apuntamos el cargo maximo a null
        if (cargoEncontrado == e->cargo_maximo) {
            LimpiarCargo(cargoEncontrado);
            e->cargo_maximo = NULL;
            return OK;
        } else {
            // si el cargo para eliminar no es el cargo maximo, entonces buscamos al padre del cargo a eliminar
            Cargo padre = GetCargoPadre(e->cargo_maximo, cargoEncontrado);
            if (padre == NULL) {
                // no se encontro el padre y no se puede hacer nada
                return ERROR;
            } else {
                // si encontramos el padre del cargo, entonces apuntamos el primer subcargo al hermano del cargo que vamos a eliminer
                if (padre->primer_subcargo == cargoEncontrado) {
                    padre->primer_subcargo = cargoEncontrado->cargo_hermano;
                } else {
                    // si no logramos encontrar al cargo a eliminar por una relacion de padre/hijo, entonces vamos a buscar por sus hermanos
                    // y si encontramos al cargo a eliminar entre los hermanos, entonces apuntamos al cargo al primer hermano del cargo que vamos a eliminar y asi lo sacamos del nivel de hermanos
                    Cargo hermano = padre->primer_subcargo;
                    while (hermano->cargo_hermano != cargoEncontrado) {
                        hermano = hermano->cargo_hermano;
                    }
                    hermano->cargo_hermano = cargoEncontrado->cargo_hermano;
                }
                // al final limpiamos el cargo liberando la memoria que ocupaba y a la persona (si habia) que ocupaba el cargo
                LimpiarCargo(cargoEncontrado);

                return OK;

            }
        }
    }
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
        ListarJerarquiaDeCargos(e->cargo_maximo, 0);  
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
    if (LimpiarPersonaDelCargo(e->cargo_maximo, ci)) {
        // la persona se encontro en la funcion y fue eliminada de sus cargos y finalmente liberado el nodo de persona
        return OK;
    } else {
        // no se encontro la persona por su ci
        return ERROR;
    }
}

TipoRet ReasignarPersona(Empresa &e, Cadena cargo, Cadena ci){
    // con esta funcion auxiliar buscamos el cargo al que la persona esta asignada por su cedula
    Cargo cargoActual = BuscarCargoPorCI(e->cargo_maximo, ci);
    if (cargoActual == NULL) {
        // si no se encontro el cargo entonces la persona no estaba asignada o no existia
        return ERROR;
    } else {
        // buscamos el cargo al que vamos a reasignar a la persona
        Cargo cargoEncontrado = GetCargo(e->cargo_maximo, cargo);
        if (cargoEncontrado == NULL) {
            return ERROR;
        } else {
            // nos fijamos si la persona ya no esta asignada al cargo
            Persona persona = cargoEncontrado->personas;
            while (persona != NULL) {
                if (strcmp(persona->ci, ci) == 0) {
                    // la persona ya estaba asignadaal cargo
                    return ERROR;
                }
                persona = persona->sig;
            }

            // eliminamos a la persona del cargo con esta funcion auxiliar, con esta funcion si se encuentra a la persona entonces liberamos la memoria de los dato de la persona
            // la funcion retorna falso si por alguna razon no se pudo eliminar a la persona
            if (!LimpiarPersonaDelCargo(cargoActual, ci)) {
                return ERROR;  
            } else {
                // si se logro limpiar a la persona del cargo actual, entonces creamos otra persona con sus mismos datos de la que borramos
                Persona nuevaPersona = CrearPersona(cargoActual->personas->nom, ci);
                if (nuevaPersona == NULL) {
                    return ERROR;
                } else {
                    // aca apuntamos el nodo de personas a la persona que acabamos de crear
                    nuevaPersona->sig = cargoEncontrado->personas;
                    cargoEncontrado->personas = nuevaPersona;

                    return OK;
                }
            }
        }
    }
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

TipoRet ListarSuperCargos(Empresa e, Cadena cargo){
    if (e == NULL || e->cargo_maximo == NULL) {
        return ERROR;
    } else {
        // buscamos el cargo por su nombre
        Cargo cargoParaListar = GetCargo(e->cargo_maximo, cargo);
        if (cargoParaListar == NULL) {
            return ERROR;
        } else {
            // usamos esta funcion auxiliar para ir recursivamente a los padres del cargo que pasaron
            ListarCargosPadres(e->cargo_maximo, cargoParaListar);
            return OK;
        }
    }

}