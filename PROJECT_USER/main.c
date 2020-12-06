/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#include "Librerias.h"

#include "TDA&CSV/Mapa.h"
#include "TDA&CSV/Lista.h"
#include "FunMain.h"

void menu_buscar( Mapa* MapaNombre, Mapa* MapaTipo, Lista* ListaKiloCalorias, Lista* ListaPrecios );
void menu_pedido( Mapa* MapaNombre, Mapa* MapaPedidos );

int main(){

    system("COLOR A");

    int opc;
    char text[MAX];

    Mapa* MapaClasificacion = crear_mapa(MIN);
    Mapa* MapaNombre = crear_mapa(MIN);
    Mapa* MapaTipo = crear_mapa(MIN);
    Lista* ListaKiloCalorias = crear_lista();
    Lista* ListaPrecios = crear_lista();

    cargar_menu(MapaClasificacion, MapaNombre, MapaTipo, ListaKiloCalorias, ListaPrecios);

    Mapa* MapaPedidos = crear_mapa(MIN);

    do{
        system("cls");
        printf("\n\tRESTAURANTE EL ORIGEN\n\n");

        printf("   1-.Mostrar MENU del Restaurante\n");
        printf("   2-.Buscar Platillos\n");
        printf("   3-.Pedido\n");
        printf("   4-.Escribir Sugerencia\n");
        printf("   5-.Salir\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:
                mostrar_menu( MapaClasificacion );
            break;
            case 2:
                menu_buscar( MapaNombre, MapaTipo, ListaKiloCalorias, ListaPrecios );
            break;
            case 3:
                menu_pedido( MapaNombre, MapaPedidos);
            break;
            case 4:
                escribir_sugerencia();
            break;
        }

        if(opc != 5){ opc = 0; }

    }while(opc != 5);

    return 0;
}

void menu_buscar( Mapa* MapaNombre, Mapa* MapaTipo, Lista* ListaKiloCalorias, Lista* ListaPrecios ){

    int opc;
    char text[MAX];

    do{
        system("cls");

        printf("\n\tBUSCAR PLATILLO\n\n");

        printf("   1-.Busqueda por Nombre\n");
        printf("   2-.Busqueda por Tipo\n");
        printf("   3-.Busqueda por Rango de KiloCalorias\n");
        printf("   4-.Busqueda por Rango de Precios\n");
        printf("   5-.Atras\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:
                buscar_nombre( MapaNombre );
            break;
            case 2:
                buscar_tipo( MapaTipo );
            break;
            case 3:
                buscar_rango( ListaKiloCalorias, 1 );
            break;
            case 4:
                buscar_rango( ListaPrecios, 2 );
            break;
        }

        if( opc != 5 ){ opc = 0; }

    }while( opc != 5);
}

void menu_pedido( Mapa* MapaNombre, Mapa* MapaPedidos ){
    int opc;
    char text[MAX];

    do{
        system("cls");

        printf("\n\tMENU PEDIDO\n\n");

        printf("   1-.Agregar un Platillo al Pedido\n");
        printf("   2-.Eliminar un Platillo del Pedido\n");
        printf("   3-.Mostrar Platillos del Pedido\n");
        printf("   4-.Eliminar Pedido\n");
        printf("   5-.Concretar Pedido\n");
        printf("   6-.Atras\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:
                agregar_platillo_pedido( MapaNombre, MapaPedidos );
            break;
            case 2:
                eliminar_platillo_pedido( MapaPedidos );
            break;
            case 3:
                mostrar_pedido( MapaPedidos );
            break;
            case 4:
                eliminar_pedido( MapaPedidos );
            break;
            case 5:
                concretar_pedido( MapaPedidos );
            break;
        }

        if( opc != 6 ){ opc = 0; }

    }while( opc != 6);
}

