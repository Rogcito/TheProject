/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
*/

#ifndef FUNMAIN_H
#define FUNMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"
#include "Platillo.h"

#define MAX 100

/* toma el texto y elimina los espacios extras que puedan existir, y a cada palabra luego de un espacio su primera letra la ppone en mayuscula */
void arreglar_string( char* str);

void* vectorizar_tipos( const char* str);

//----------------------------------------

void agregar_platillo( Mapa* Platillos );




#endif // FUNMAIN_H
