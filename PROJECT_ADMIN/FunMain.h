/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/

#ifndef FUNMAIN_H
#define FUNMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"
#include "TDA&CSV/CSV.h"
#include "Platillo.h"
#include "InicioSesion.h"

#define MAX 100

/* toma el texto y elimina los espacios extras que puedan existir, y a cada palabra luego de un espacio su primera letra la ppone en mayuscula */
void arreglar_string( char* str);

/* toma el texto y crea una lista enlazada con sus datos separados por comas */
void* vectorizar_tipos( const char* str);

/* pasa todos los platillos del menu.csv al mapa Platillos */
void cargar_menu( Mapa* Platillos );

/* reescribe todos los platillos del mapa Platillos al menu.csv */
void actualizar_menu( Mapa* Platillos );

/* escribe en el historial */
void escribir_historial( User* usuario, char* opcion, char* cambiado );

/* pasa los pedidos de las mesas al programa */
void cargar_lista_mesas( Lista* listaEspera );

/* actualiza los pedidos del programa en el archivo de texto */
void actualizar_lista_mesas( Lista* ListaEspera );

//----------------------------------------

void mostrar_lista_espera( Lista* ListaEspera );

void agregar_platillo( Mapa* Platillos, User* usuario );

void agregar_lista( Mapa* Platillos, User* usuario );

void modificar_platillo( Mapa* Platillos, User* usuario );

void eliminar_Platillo( Mapa* Platillos, User* usuario );

void sugerencias_historial( int opcion );

#endif // FUNMAIN_H
