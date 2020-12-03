#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Nodo.h"
#include "Lista.h"

Lista* crear_lista(){
    Lista* newL = (Lista*)malloc(sizeof(Lista));
    newL->head = NULL;
    newL->current = NULL;
    newL->last = NULL;
    newL->total = 0;
    return newL;
}

void push_back_L(Lista* L, void* data){
    Nodo* nuevoNodo = crearNodo( data );

    if(L->head == NULL){
        L->head = nuevoNodo;
    }else{
        nuevoNodo->prev = L->last;
        L->last->next = nuevoNodo;
    }
    L->last = nuevoNodo;
    L->total++;
}

void push_current_L(Lista* L, void* data){
    Nodo* newN = crearNodo( data);
    Nodo* auxN = L->current;
    Nodo* Acurr = auxN->prev;

    if(auxN->prev == NULL){
        auxN->prev = newN;
        newN->next = auxN;
        L->head = newN;
    }else{
        Acurr->next = newN;
        newN->prev = Acurr;
        auxN->prev = newN;
        newN->next = auxN;
    }
    L->total++;
}

void* first_L ( Lista* L ){
    if(L->head == NULL){
        return NULL;
    }
    L->current = L->head;
    return L->current->data;
}

void* last_L( Lista* L ){
    if(L->last == NULL){
        return NULL;
    }
    L->current = L->last;
    return L->current->data;
}

void* next_L ( Lista* L ){
    if(L->current == NULL || L->current->next == NULL){
        return NULL;
    }
    L->current = L->current->next;
    return L->current->data;
}

void* prev_L ( Lista* L ){
    if(L->current == NULL || L->current->prev == NULL){
        return NULL;
    }
    L->current = L->current->prev;
    return L->current->data;
}

void delete_current_L( Lista* L){
    Nodo* auxN = L->current;
    if( auxN->prev == NULL){
        if(L->total == 1){
            L->head = NULL;
            L->current = NULL;
            L->last = NULL;
        }else{
            L->head = auxN->next;
            L->head->prev = NULL;
        }
    }else if( auxN->next == NULL){
        L->last = auxN->prev;
        L->last->next = NULL;
    }else{
        L->current = auxN->prev;
        L->current->next = auxN->next;
        L->current = auxN->next;
        L->current->prev = auxN->prev;
    }
    free( auxN );
    L->total--;
}

void delete_back_L( Lista* L ){
    if( L->last != NULL ){
        Nodo* auxN = L->last;
        L->last = auxN->prev;
        L->last->next = NULL;
        free( auxN );
        L->total--;
    }
}


void delete_L ( Lista *L ){
    Nodo* auxN = NULL;
    while( L->last != NULL ){
    	auxN = L->last;
    	L->last = auxN->prev;
    	free(auxN);
	}
	L->head = NULL;
	L->current = NULL;
	L->total = 0;
}
















