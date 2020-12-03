/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/CSV.h"

#define MAX 100

typedef struct{
    char user[MAX];
    char password[MAX];
}User;

User* crear_usuario( const char* user, const char* password );

//----------------------------------------

void cargar_usuarios( Mapa* Usuarios );

void* iniciar_sesion( Mapa* Usuarios );

void* crear_cuenta( Mapa* Usuarios );

//----------------------------------------

void* inicio_sesion();

#endif // INICIOSESION_H
