/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
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
    void* tipos;               //cereales, masas, tuberculos, carnes, vegetales, lacteos, frutas, grasas, azucares;
    char clasificacion[MAX];   //desayuno, almuerzo , cena, bebida, alcohol, etc.
    int kiloCalorias;          //calorias del platillo
    long precio;               //precio
}Platillo;

typedef struct{
    int numero;                //numero de la mesa
    void* listaPlatillos;      //lista con los nombres de los platillos
}Mesa;

Platillo* crear_platillo(const char* nombre, void* tipos, const char* clasificacion, int kiloCalorias, long precio);

NombreTipos* crear_nombre_tipos( const char* nombre);

Mesa* crear_mesa( int numero, void* listaPlatillos );

#endif // PLATILLO_H
