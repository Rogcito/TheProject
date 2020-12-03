/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"

#include "InicioSesion.h"
#include "FunMain.h"

#define MAX 100
#define MIN 20

int main(){

    system("COLOR A");

    User* usuario = inicio_sesion();
    if( usuario == NULL ){
        return 0;
    }

    int opc;
    char text[MAX];

    Mapa* Platillos = crear_mapa(MIN);
    Lista* ListaEspera = crear_lista();

    cargar_menu(Platillos);
    cargar_lista_mesas(ListaEspera);

    do{
        system("cls");
        printf("\n\tRESTAURANTE EL ORIGEN\n");
        printf("   *Usuario   : %s\n\n", usuario->user);

        printf("   1-.Mostrar Lista de Espera\n");
        printf("   2-.Agregar Platillo Manualmente\n");
        printf("   3-.Agregar Lista de Platillos\n");
        printf("   4-.Modificar Platillo\n");
        printf("   5-.Eliminar Platillo\n");
        printf("   6-.Revisar Sugerencias\n");
        printf("   7-.Historial\n");
        printf("   8-.Salir\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:
                mostrar_lista_espera( ListaEspera );
            break;
            case 2:
                agregar_platillo( Platillos, usuario );
            break;
            case 3:
                agregar_lista( Platillos, usuario );
            break;
            case 4:
                modificar_platillo( Platillos, usuario );
            break;
            case 5:
                eliminar_Platillo( Platillos, usuario );
            break;
            case 6:
                sugerencias_historial( 1 );
            break;
            case 7:
                sugerencias_historial( 2 );
            break;
        }

        if(opc != 8){ opc = 0; }

    }while(opc != 8);

    return 0;
}
