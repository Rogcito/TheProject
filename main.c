/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"

#define MAX 100
#define MIN 20

int main(){

    system("COLOR A");

    int opc;
    char text[MAX];

    Mapa* Platillos = crear_mapa(MIN);
    Mapa* ListaEspera = crear_lista();

    do{
        system("cls");
        printf("\n\tRESTAURANT\n\n");

        printf("   1-.Mostrar Lista de Espera\n");
        printf("   2-.Agregar Platillo Manualmente\n");
        printf("   3-.Agregar Lista de Platillos\n");
        printf("   4-.Modificar Platillo\n");
        printf("   5-.Eliminar Platillo\n");
        printf("   6-.Revisar Sugerencias\n");
        printf("   7-.Salir\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:

            break;
            case 2:
                agregar_platillo( Platillos );
            break;
            case 3:

            break;
            case 4:

            break;
            case 5:

            break;
            case 6:

            break;
        }

        if(opc != 7){ opc = 0; }

    }while(opc != 7);

    return 0;
}
