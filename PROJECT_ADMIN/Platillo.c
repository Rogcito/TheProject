/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#include "Platillo.h"

Platillo* crear_platillo(const char* nombre, void* tipos, const char* clasificacion, int kiloCalorias, long precio){
    Platillo* newP = (Platillo*)malloc(sizeof(Platillo));

    strcpy(newP->nombre, nombre);
    newP->tipos = tipos;
    strcpy(newP->clasificacion, clasificacion);
    newP->kiloCalorias = kiloCalorias;
    newP->precio = precio;

    return newP;
}

NombreTipos* crear_nombre_tipos( const char* nombre){
    NombreTipos* newNL = (NombreTipos*)malloc(sizeof(NombreTipos));

    strcpy( newNL->nombre, nombre);

    return newNL;
}

Mesa* crear_mesa( int numero, void* listaPlatillos ){
    Mesa* newM = (Mesa*)malloc(sizeof(Mesa));

    newM->numero =  numero;
    newM->listaPlatillos = listaPlatillos;

    return newM;
}
