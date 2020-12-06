/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#ifndef FUNMAIN_H
#define FUNMAIN_H

#include "Librerias.h"

#include "TDA&CSV/CSV.h"
#include "TDA&CSV/Lista.h"
#include "TDA&CSV/Mapa.h"
#include "Platillo.h"

/* toma el texto y elimina los espacios extras que puedan existir, y a cada palabra luego de un espacio su primera letra la ppone en mayuscula */
void arreglar_string( char* str);

/* toma el texto y crea una lista enlazada con sus datos separados por comas */
void* vectorizar_tipos( const char* str);

//----------------------------------------------

/* inserta listas enlazadas de algo en un mapa */
void insertar_lista_mapa( Mapa* mapa, void* key, void* value );

/* ordena una lista enlazada de mayor a menor, el ind es para diferenciar si es para kilocalorias o precios */
void lista_ordenada_kilo_precio( Lista* L, Platillo* P, int ind );

//----------------------------------------------

/* pasa todos los platillos del menu.csv a los mapa para sus busquedas correspondientes */
void cargar_menu( Mapa* MapaClasificacion, Mapa* MapaNombre, Mapa* MapaTipo, Lista* ListaKiloCalorias, Lista* ListaPrecios );

//----------------------------------------------

/* muesta el menu con todos sus platillos separados por su clasificacion */
void mostrar_menu( Mapa* MapaClasificacion );

/* pide un nombre y lo busca */
void buscar_nombre( Mapa* MapaNombre );

/* pide un tipo y muestra todos los platillos que contengan dicho tipo */
void buscar_tipo( Mapa* MapaTipo );

/* pide el minimo y el maximo y mostrara todos los platillos con el rango, el ind ve si es a kilocalorias o precios */
void buscar_rango( Lista* ListaOrdenada, int ind );

/* pide el numero de mesa, y el platillo que se agregara */
void agregar_platillo_pedido( Mapa* MapaNombre, Mapa* MapaPedidos );

/* pide el numero de mesa y el platillo para eliminarlo del pedido */
void eliminar_platillo_pedido( Mapa* MapaPedidos );

/* pide el numero de mesa y muestra todos los platillos */
void mostrar_pedido( Mapa* MapaPedidos );

/* pide el numero de mesa y la elimina complatamente */
void eliminar_pedido( Mapa* MapaPedidos );

/* pide el numero de mesa, muestra por pantalla el pedido mas el total de la compra y lo inserta en archivo PEDIDOS.csv */
void concretar_pedido( Mapa* MapaPedidos );

/* permite escribir una sugerencia y la importa a SUGERENCIAS.csv*/
void escribir_sugerencia();

#endif // FUNMAIN_H
