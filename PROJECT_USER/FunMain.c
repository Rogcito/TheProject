/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#include "FunMain.h"

void arreglar_string( char* str){

    char result[MAX];    //nuevo texto
    int p = 0, text = 0; //el text es para que no escriva un espacio antes de la primera letra del texto
    bool flag = true;    //para que la primera palabra despues de un espacio sea mayuscula

    //copia en result el str sin espacios innecesarios
    for(int i=0; str[i] != '\0'; i++){
        str[i] = tolower(str[i]);

        if( (str[i] != ' ') || ( (str[i] == ' ') && (str[i-1] != ' ') && (text > 0) ) ){
            if(flag){
                result[p] = toupper(str[i]);
                flag = false;
            }else{
                result[p] = str[i];
            }

            if(str[i] == ' '){
                flag = true;
            }

            text++;
            p++;
        }

    }

    //se pone el simbolo que termina el string
    result[p] = '\0';

    for(int i=0; result[i] != '\0'; i++){
        str[i] = result[i];
    }

    //se verifica que no exista un espacio al final del nuevo texto, si existe se cambia por el simbolo final.
    if(str[p-1] == ' '){
        str[p-1] = '\0';
    }else{
        str[p] = '\0';
    }

}

void* vectorizar_tipos( const char* str){
    Lista* newL = crear_lista();

    if( strcmp(str, "") == 0 ){
        return newL;
    }

    char texto[MAX];
    strcpy( texto, str);
    char delimitador[] = ",";

    char* token = strtok( texto, delimitador);
    if(token != NULL){
        while( token != NULL){
            arreglar_string(token);
            NombreTipos* newNT = crear_nombre_tipos( token );
            push_back_L(newL, newNT);
            token = strtok(NULL, delimitador);
        }
    }

    return newL;
}

//----------------------------------------------

void insertar_lista_mapa( Mapa* mapa, void* key, void* value ){
    Lista* auxL = search_map(mapa, key);
    if( auxL == NULL ){
        Lista* newL = crear_lista();
        push_back_L(newL, value);
        insert_map(mapa, key, newL);
    }else{
        push_back_L(auxL, value);
    }
}

void lista_ordenada_kilo_precio( Lista* L, Platillo* P, int ind ){
    Platillo* auxP = first_L( L );
    while( auxP != NULL ){
        if(ind == 1){
            if( P->kiloCalorias < auxP->kiloCalorias ){
                push_current_L( L, P );
                return;
            }
        }else{
            if( P->precio < auxP->precio ){
                push_current_L( L, P );
                return;
            }
        }
        auxP = next_L( L );
    }
    push_back_L( L, P);
}

//----------------------------------------------

void cargar_menu( Mapa* MapaClasificacion, Mapa* MapaNombre, Mapa* MapaTipo, Lista* ListaKiloCalorias, Lista* ListaPrecios ){
    FILE* MENU = fopen("MENU.csv", "r");
    char nombre[MAX], clasificacion[MAX];
    int kiloCalorias;
    long precio;

    char linea[MAX];

    while( fgets(linea, 1023, MENU) != NULL ){
        const char* name = get_csv_field(linea, 0);
        const char* tipos = get_csv_field(linea, 1);
        const char* clas = get_csv_field(linea, 2);
        kiloCalorias = atoi( get_csv_field(linea, 3));
        precio = atol( get_csv_field(linea, 4));

        strcpy(nombre, name);
        strcpy(clasificacion, clas);

        arreglar_string(nombre);
        arreglar_string(clasificacion);
        Lista* listaTipos = vectorizar_tipos(tipos);

        if( (strcmp(nombre,"") != 0) && (strcmp(clasificacion,"") != 0) && (kiloCalorias >= 0) && (precio >= 0) && (listaTipos->head != NULL)){
            Platillo* newP = crear_platillo(nombre, listaTipos, clasificacion, kiloCalorias, precio);

            //insertar en MapaNombre
            insert_map(MapaNombre, newP->nombre, newP);

            //insertar en MapaClasificacion
            insertar_lista_mapa(MapaClasificacion, newP->clasificacion, newP);

            //insert en MapaTipo
            Lista* auxL = newP->tipos;
            NombreTipos* tipo = first_L(auxL);
            while(tipo != NULL){
                insertar_lista_mapa(MapaTipo, tipo->nombre, newP);
                tipo = next_L(auxL);
            }

            //insertar en ListaKiloCalorias
            lista_ordenada_kilo_precio(ListaKiloCalorias, newP, 1);

            //insertar en ListaPrecios
            lista_ordenada_kilo_precio(ListaPrecios, newP, 2);

        }
    }
    fclose(MENU);
}

//----------------------------------------------

void mostrar_menu( Mapa* MapaClasificacion ){
    system("cls");

    printf("\n\tMENU\n");
    Platillo* auxP;

    Lista* auxL = first_map( MapaClasificacion );
    while(auxL != NULL){
        auxP = first_L(auxL);
        printf("\n  -%s-\n\n", auxP->clasificacion );
        while(auxP != NULL){
            printf("    Nombre       : %s\n", auxP->nombre );
            printf("    KiloCalorias : %d\n", auxP->kiloCalorias );
            printf("    Precio       : %ld\n\n", auxP->precio);

            auxP = next_L(auxL);
        }
        auxL = next_map(MapaClasificacion);
    }

    printf("\n");
    system("pause");
}

//--------

void buscar_nombre( Mapa* MapaNombre ){
    system("cls");

    char nombre[MAX];

    printf("\n\tBUSCAR PLATILLO POR NOMBRE\n\n");

    printf("   Nombre del Platillo : ");
    gets(nombre);

    arreglar_string(nombre);

    Platillo* auxP = search_map(MapaNombre, nombre);

    if( auxP == NULL ){
        printf("\n   *ERROR::Platillo NO Existente\n\n");
    }else{
        printf("\n    Nombre        : %s", auxP->nombre);
        printf("\n    Tipos         : ");

        NombreTipos* tipo = first_L(auxP->tipos);
        while(tipo != NULL){
            printf("%s", tipo->nombre);
            tipo = next_L(auxP->tipos);
            if( tipo != NULL ){
                printf(", ");
            }
        }
        printf("\n    Clasificacion : %s", auxP->clasificacion);
        printf("\n    KiloCalorias  : %d", auxP->kiloCalorias);
        printf("\n    Precio        : %ld\n\n", auxP->precio);
    }

    system("pause");
}

void buscar_tipo( Mapa* MapaTipo ){
    system("cls");

    char tipo[MAX];

    printf("\n\tBUSCAR PLATILLOS POR TIPO\n\n");

    printf("   Tipos : ");
    char* auxC = first_key_map(MapaTipo);
    while( auxC != NULL ){
        printf("%s", auxC);
        auxC = next_key_map(MapaTipo);
        if( auxC != NULL){
            printf(", ");
        }
    }

    printf("\n\n   Tipo del Platillo : ");
    gets(tipo);

    arreglar_string(tipo);

    Lista* auxL = search_map( MapaTipo, tipo);
    if( auxL == NULL){
        printf("\n   *ERROR::Tipo de Platillo NO Existente\n\n");
    }else{
        printf("\n");
        Platillo* auxP = first_L(auxL);
        while(auxP != NULL){
            printf("    Nombre        : %s\n", auxP->nombre );
            printf("    Clasificacion : %s\n", auxP->clasificacion );
            printf("    KiloCalorias  : %d\n", auxP->kiloCalorias );
            printf("    Precio        : %ld\n\n", auxP->precio);

            auxP = next_L(auxL);
        }
    }

    system("pause");
}

void buscar_rango( Lista* ListaOrdenada, int ind ){
    system("cls");

    int cont = 0;
    long minimo, maximo;
    char text[MAX];

    if( ind == 1 ){
        printf("\n\tBUSCAR POR RANGO DE KILOCALORIAS\n\n");
    }else{
        printf("\n\tBUSCAR POR RANGO DE PRECIOS\n\n");
    }

    printf("   Minimo : ");
    scanf("%ld", &minimo );
    printf("   Maximo : ");
    scanf("%ld", &maximo );
    gets(text);

    if( (strcmp(text, "") != 0) || (minimo < 0) || (maximo < 0) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }else if( minimo > maximo ){
        printf("\n   *ERROR::Minimo mayor que el Maximo\n\n");
        system("pause");
        return;
    }

    Platillo* auxP = first_L(ListaOrdenada);
    while( auxP != NULL ){

        if( ( (auxP->kiloCalorias >= minimo) && (auxP->kiloCalorias <= maximo) && (ind == 1) ) || ( (auxP->precio >= minimo) && (auxP->precio <= maximo) && (ind == 2) ) ){
            cont++;
            printf("\n    Nombre        : %s", auxP->nombre);
            printf("\n    Tipos         : ");

            NombreTipos* tipo = first_L(auxP->tipos);
            while(tipo != NULL){
                printf("%s", tipo->nombre);
                tipo = next_L(auxP->tipos);
                if( tipo != NULL ){
                    printf(", ");
                }
            }

            printf("\n    Clasificacion : %s", auxP->clasificacion);
            printf("\n    KiloCalorias  : %d", auxP->kiloCalorias);
            printf("\n    Precio        : %ld\n", auxP->precio);
        }
        auxP = next_L(ListaOrdenada);
    }

    if( cont == 0 ){
        if( ind == 1 ){
            printf("\n   Sin Platillos en este Rango de KiloCalorias\n");
        }else{
            printf("\n   Sin Platillos en este Rango de Precios\n");
        }
    }

    printf("\n");
    system("pause");
}

//--------

void agregar_platillo_pedido( Mapa* MapaNombre, Mapa* MapaPedidos ){
    system("cls");

    char nombre[MAX], text[MAX], nMesa[MAX];
    int numeroMesa;

    printf("\n\tAGREGAR UN PLATILLO AL PEDIDO\n\n");

    printf("   Numero de la Mesa (1-30) : ");
    scanf("%d", &numeroMesa);
    gets(text);

    if( (strcmp(text,"") != 0) || (numeroMesa < 1) || (numeroMesa > 30) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }

    printf("   Nombre del Platillo      : ");
    gets(nombre);

    arreglar_string(nombre);

    Platillo* auxP = search_map(MapaNombre, nombre);

    if( auxP == NULL ){
        printf("\n   *ERROR::Platillo NO Existe\n\n");
    }else{
        sprintf(nMesa, "%d", numeroMesa);
        Mesa* auxM = search_map( MapaPedidos, nMesa);

        if( auxM == NULL ){
            Lista* newL = crear_lista();
            push_back_L(newL, auxP);
            Mesa* newM = crear_mesa( numeroMesa, newL );
            insert_map( MapaPedidos, newM->codigo, newM);
        }else{
            Lista* auxL = auxM->listaPlatillos;
            push_back_L( auxL, auxP);
        }

        printf("\n   *Platillo Agregado Correctamente al Pedido\n\n");
    }

    system("pause");
}

void eliminar_platillo_pedido( Mapa* MapaPedidos ){
    system("cls");

    char nombre[MAX], text[MAX], nMesa[MAX];
    int numeroMesa, cont = 0;

    printf("\n\tELIMINAR UN PLATILLO AL PEDIDO\n\n");

    printf("   Numero de la Mesa (1-30) : ");
    scanf("%d", &numeroMesa);
    gets(text);

    sprintf(nMesa, "%d", numeroMesa);
    Mesa* auxM = search_map( MapaPedidos, nMesa);

    if( (strcmp(text,"") != 0) || (numeroMesa < 1) || (numeroMesa > 30) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }else if( auxM == NULL ){
        printf("\n   *Mesa Sin Pedidos\n\n");
        system("pause");
        return;
    }

    printf("   Nombre del Platillo      : ");
    gets(nombre);

    arreglar_string(nombre);

    Lista* auxL = auxM->listaPlatillos;
    Platillo* auxP = first_L( auxL );
    while(auxP != NULL){
        if( strcmp(auxP->nombre, nombre) == 0 ){
            cont++;
            delete_current_L( auxL );
            printf("\n   *Platillo Eliminado Correctamente del Pedido\n\n");
            break;
        }
        auxP = next_L( auxL );
    }

    if( cont == 0 ){
        printf("\n   *Platillo NO existe en el Pedido\n\n");
    }else if( auxL->total == 0 ){
        delete_key_map( MapaPedidos, nMesa);
    }

    system("pause");
}

void mostrar_pedido( Mapa* MapaPedidos ){
    system("cls");

    char nMesa[MAX], text[MAX];
    int numeroMesa;

    printf("\n\tMOSTRAR PEDIDO\n\n");

    printf("   Numero de la Mesa (1-30) : ");
    scanf("%d", &numeroMesa);
    gets(text);

    sprintf(nMesa, "%d", numeroMesa);
    Mesa* auxM = search_map( MapaPedidos, nMesa);

    if( (strcmp(text,"") != 0) || (numeroMesa < 1) || (numeroMesa > 30) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }else if( auxM == NULL ){
        printf("\n   *Mesa Sin Pedidos\n\n");
        system("pause");
        return;
    }

    printf("\n   MESA NUMERO %d\n",auxM->numero);

    Lista* auxL = auxM->listaPlatillos;
    Platillo* auxP = first_L(auxL);
    while(auxP != NULL){
        printf("\n    -%s.......%ld",auxP->nombre, auxP->precio);
        auxP = next_L(auxL);
    }

    printf("\n\n");
    system("pause");
}

void eliminar_pedido( Mapa* MapaPedidos ){
    system("cls");

    char nMesa[MAX], text[MAX];
    int numeroMesa;

    printf("\n\tELIMINAR PEDIDO\n\n");

    printf("   Numero de la Mesa (1-30) : ");
    scanf("%d", &numeroMesa);
    gets(text);

    sprintf(nMesa, "%d", numeroMesa);
    Mesa* auxM = search_map( MapaPedidos, nMesa);

    if( (strcmp(text,"") != 0) || (numeroMesa < 1) || (numeroMesa > 30) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }else if( auxM == NULL ){
        printf("\n   *Mesa Sin Pedidos\n\n");
        system("pause");
        return;
    }

    delete_key_map( MapaPedidos, nMesa);
    printf("\n   *Pedido Eliminado Correctamente\n\n");

    system("pause");
}

void concretar_pedido( Mapa* MapaPedidos ){
    system("cls");

    FILE* PEDIDOS = fopen("PEDIDOS.csv","a");

    char nMesa[MAX], text[MAX];
    int numeroMesa;
    long total = 0;

    printf("\n\tCONCRETAR PEDIDO\n\n");

    printf("   Numero de la Mesa (1-30) : ");
    scanf("%d", &numeroMesa);
    gets(text);

    sprintf(nMesa, "%d", numeroMesa);
    Mesa* auxM = search_map( MapaPedidos, nMesa);

    if( (strcmp(text,"") != 0) || (numeroMesa < 1) || (numeroMesa > 30) ){
        printf("\n   *ERROR::Datos Incorrectos\n\n");
        system("pause");
        return;
    }else if( auxM == NULL ){
        printf("\n   *Mesa Sin Pedidos\n\n");
        system("pause");
        return;
    }

    printf("\n   MESA NUMERO %d\n",auxM->numero);
    fprintf(PEDIDOS,"%d,%c", auxM->numero, 34);

    Lista* auxL =  auxM->listaPlatillos;
    Platillo* auxP = first_L(auxL);
    while( auxP != NULL ){
        printf("\n    -%s.......%ld",auxP->nombre, auxP->precio);
        total = total + auxP->precio;

        fprintf(PEDIDOS,"%s", auxP->nombre);
        auxP = next_L(auxL);
        if( auxP != NULL ){
            fprintf(PEDIDOS,",");
        }else{
            fprintf(PEDIDOS,"%c\n",34);
        }
    }

    printf("\n\n   TOTAL.............%ld\n\n",total);
    fclose(PEDIDOS);

    system("pause");
}

//--------

void escribir_sugerencia(){
    system("cls");

    FILE* SUGERENCIAS = fopen("SUGERENCIAS.csv","a");

    char texto[1023];

    printf("\n\tESCRIBIR SUGERENCIA\n\n");

    printf("   Sugerencia : ");
    gets(texto);

    fprintf(SUGERENCIAS, "-%s\n", texto);

    fclose(SUGERENCIAS);

    printf("\n   *Sugerencia Agregada Correctamente\n\n");
    system("pause");
}



































