/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
*/
#ifndef PLATILLO_H
#define PLATILLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct{
    char nombre[MAX];
}NombreTipos;

typedef struct{
    char nombre[MAX];          //nombre del platillo
    void* tipos;               //cereales, masas, tuberculos, carnes, legumbres, vegetales, lacteos, frutas, grasas, azucares;
    char clasificacion[MAX];   //desayuno, almuerzo , cena, bebida, alcohol, etc.
    int kiloCalorias;          //calorias del platillo
    long precio;               //precio
}Platillo;

Platillo* crear_platillo(const char* nombre, void* tipos, const char* clasificacion, int kiloCalorias, long precio);

NombreTipos* crear_nombre_tipos( const char* nombre);

#endif // PLATILLO_H
