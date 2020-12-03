#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

typedef struct{
    Nodo* head;
    Nodo* current;
    Nodo* last;
    long total;
}Lista;

Lista* crear_lista();

void push_back_L( Lista* L, void* data );

void* first_L ( Lista* L );

void* last_L ( Lista* L );

void* next_L ( Lista* L );

void* prev_L ( Lista* L );

void push_current_L(Lista* L, void* data);

void delete_current_L( Lista* L );

void delete_back_L( Lista* L );

void delete_L( Lista* L);


#endif // LISTA_H
