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

void cargar_menu( Mapa* Platillos ){
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
            insert_map(Platillos, newP->nombre, newP);
        }
    }
    fclose(MENU);
}

void actualizar_menu( Mapa* Platillos ){
    FILE* MENU = fopen("MENU.csv","w");

    Platillo* auxP = first_map(Platillos);
    while(auxP != NULL){

        fprintf(MENU, "%s,%c", auxP->nombre,34);

        NombreTipos* tipo = first_L(auxP->tipos);
        while(tipo != NULL){
            fprintf(MENU,"%s", tipo->nombre);
            tipo = next_L(auxP->tipos);
            if(tipo != NULL){
                fprintf(MENU,",");
            }
        }

        fprintf(MENU, "%c,%s,%d,%ld\n", 34, auxP->clasificacion, auxP->kiloCalorias, auxP->precio);
        auxP = next_map(Platillos);
    }
    fclose(MENU);
}

void escribir_historial( User* usuario, char* opcion, char* cambiado ){
    time_t t;
    struct tm *tm;
    char fechaHora[MAX];

    t = time(NULL);
    tm = localtime(&t);
    strftime(fechaHora, 100, "%d/%m/%Y | HORA : %I:%M%p |", tm);

    FILE* HISTORIAL = fopen("HISTORIAL.csv","a");
    fprintf( HISTORIAL, "| USUARIO : %s | OPCION : %s | ALTERADO : %s | FECHA : %s\n", usuario->user, opcion, cambiado, fechaHora );
    fclose(HISTORIAL);

}

void cargar_lista_mesas( Lista* ListaEspera ){
    FILE* PEDIDOS = fopen("PEDIDOS.csv","r");
    int numero;

    char linea[1024];
    while( fgets(linea, 1023, PEDIDOS) != NULL ){
        numero = atoi(get_csv_field(linea, 0));
        const char* platillos = get_csv_field(linea, 1);

        Lista* listaPlatillos = vectorizar_tipos(platillos);

        if( (listaPlatillos->head != NULL) && (numero > 0) ){
            Mesa* newM = crear_mesa(numero, listaPlatillos);
            push_back_L(ListaEspera, newM);
        }

    }
    fclose(PEDIDOS);
}

void actualizar_lista_mesas( Lista* ListaEspera ){
    FILE* PEDIDOS = fopen("PEDIDOS.csv", "w");

    Mesa* mesa = first_L(ListaEspera);
    while(mesa != NULL){
        fprintf(PEDIDOS,"%d,%c", mesa->numero,34);

        NombreTipos* platillo = first_L(mesa->listaPlatillos);
        while(platillo != NULL){
            fprintf(PEDIDOS, "%s", platillo->nombre);

            platillo = next_L(mesa->listaPlatillos);
            if(platillo != NULL){
                fprintf(PEDIDOS, ",");
            }else{
                fprintf(PEDIDOS, "%c",34);
            }
        }

        mesa = next_L(ListaEspera);
    }
    fclose(PEDIDOS);
}

//--------------------------------------------

void mostrar_lista_espera( Lista* ListaEspera ){
    int nMesa;
    char texto[MAX], eleccion[MAX];

    do{
        system("cls");

        printf("\n\tLISTA DE MESAS EN ESPERA\n\n");

        Mesa* mesa = first_L(ListaEspera);

        if(mesa == NULL){
            printf("   *Sin Mesas en Espera\n\n");
            system("pause");
            return;
        }

        while(mesa != NULL){
            printf("   MESA NUMERO %d",mesa->numero);

            NombreTipos* platillo = first_L(mesa->listaPlatillos);
            while( platillo != NULL ){
                printf("\n    -%s",platillo->nombre);
                platillo = next_L(mesa->listaPlatillos);
            }
            printf("\n\n");
            mesa = next_L(ListaEspera);
        }

        printf("\n   Mesa Concluida (0 en caso de ninguna) : ");
        scanf("%d", &nMesa);
        gets(texto);

        if( (nMesa > 0) && (strcmp(texto,"") == 0) ){

            mesa = first_L(ListaEspera);
            while(mesa != NULL){

                if( mesa->numero == nMesa ){
                    delete_current_L(ListaEspera);
                    break;
                }

                mesa = next_L(ListaEspera);
            }

            actualizar_lista_mesas(ListaEspera);
        }else if( (nMesa == 0) && (strcmp(texto,"") == 0) ){
            printf("\n   Salir (SI/NO) : ");
            gets(eleccion);

            arreglar_string(eleccion);
            if( strcmp(eleccion,"Si") == 0 ){
                return;
            }
        }
    }while(true);
}

void agregar_platillo( Mapa* Platillos, User* usuario ){
    system("cls");

    char nombre[MAX], tipos[MAX], clasificacion[MAX], texto[MAX];
    int kiloCalorias;
    long precio;

    printf("\n\tAGREGAR PLATILLO\n\n");

    printf("   Nombre del Platillo        : ");
    gets(nombre);
    printf("   Tipos (separar por comas)  : ");
    gets(tipos);
    printf("   Clasificacion              : ");
    gets(clasificacion);
    printf("   KiloCalorias del Platillo  : ");
    scanf("%d", &kiloCalorias);
    printf("   Precio del Platillo        : ");
    scanf("%ld", &precio);
    gets(texto);

    arreglar_string(nombre);
    arreglar_string(tipos);
    arreglar_string(clasificacion);
    Lista* listaTipos = vectorizar_tipos(tipos);

    Platillo* auxP = search_map(Platillos, nombre);

    if( auxP != NULL ){
        printf("\n   *ERROR::Platillo Existente\n\n");

    }else if( (strcmp(nombre,"") != 0) && (strcmp(clasificacion,"") != 0) && (kiloCalorias >= 0) && (precio >= 0) && (listaTipos->head != NULL) && (strcmp(texto,"") == 0) ){
        Platillo* newP = crear_platillo(nombre, listaTipos, clasificacion, kiloCalorias, precio);
        insert_map(Platillos, newP->nombre, newP);

        //agregar el nuevo platillo al csv
        FILE* MENU = fopen("MENU.csv", "a");
        fprintf(MENU, "%s,%c", newP->nombre,34);

        NombreTipos* tipo = first_L(newP->tipos);
        while(tipo != NULL){
            fprintf(MENU,"%s", tipo->nombre);
            tipo = next_L(newP->tipos);
            if(tipo != NULL){
                fprintf(MENU,",");
            }
        }

        fprintf(MENU, "%c,%s,%d,%ld\n", 34, newP->clasificacion, newP->kiloCalorias, newP->precio);
        fclose(MENU);

        escribir_historial(usuario, "Agregar Platillo", newP->nombre);

        printf("\n   *Platillo Agregado Correctamente\n\n");
    }else{
        printf("\n   *ERROR::Datos Incorrectos\n\n");
    }

    system("pause");
}

void agregar_lista( Mapa* Platillos, User* usuario ){
    system("cls");

    char archivo[MAX], nombre[MAX], clasificacion[MAX];
    int kiloCalorias;
    float precio;

    printf("\n\tAGREGAR LISTA DE PLATILLOS\n\n");

  	printf("   Nombre del archivo(sin.csv): ");
  	gets( archivo );
  	strcat(archivo,".csv");

  	FILE* LISTAPLATILLOS = fopen( archivo, "r");

  	if( LISTAPLATILLOS == NULL ){
        printf("\n   *ERROR::Archivo NO Existe\n\n");
  	}else{
        char linea[1024];

        while( fgets(linea, 1023, LISTAPLATILLOS) != NULL ){
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

            Platillo* auxP = search_map(Platillos, nombre);

            if( auxP == NULL){
                if( (strcmp(nombre,"") != 0) && (strcmp(clasificacion,"") != 0) && (kiloCalorias >= 0) && (precio >= 0) && (listaTipos->head != NULL)){
                    Platillo* newP = crear_platillo(nombre, listaTipos, clasificacion, kiloCalorias, precio);
                    insert_map(Platillos, newP->nombre, newP);

                    escribir_historial(usuario, "Agregar Lista De Platillos", newP->nombre);
                }
            }
        }
        fclose(LISTAPLATILLOS);

        actualizar_menu(Platillos);

        printf("\n   *Lista Agregada Correctamente\n\n");
  	}

  	system("pause");
}

void modificar_platillo( Mapa* Platillos, User* usuario ){
    system("cls");

    char nombre[MAX];

    printf("\n\tMODIFICAR PLATILLO\n\n");

    printf("   Nombre del Platillo        : ");
    gets(nombre);

    arreglar_string(nombre);

    Platillo* auxP = search_map(Platillos, nombre);

    if( auxP != NULL ){

        delete_key_map(Platillos, nombre);

        char tipos[MAX], clasificacion[MAX], texto[MAX];
        int kiloCalorias;
        long precio;

        printf("\n\tMODIFICAR\n\n");

        printf("   Nombre del Platillo        : ");
        gets(nombre);
        printf("   Tipos (separar por comas)  : ");
        gets(tipos);
        printf("   Clasificacion              : ");
        gets(clasificacion);
        printf("   KiloCalorias del Platillo  : ");
        scanf("%d", &kiloCalorias);
        printf("   Precio del Platillo        : ");
        scanf("%ld", &precio);
        gets(texto);

        arreglar_string(nombre);
        arreglar_string(tipos);
        arreglar_string(clasificacion);
        Lista* listaTipos = vectorizar_tipos(tipos);

        Platillo* auxP = search_map(Platillos, nombre);

        if( auxP != NULL ){
            printf("\n   *ERROR::Platillo Existente\n\n");
        }else if( (strcmp(nombre,"") != 0) && (strcmp(clasificacion,"") != 0) && (kiloCalorias >= 0) && (precio >= 0) && (listaTipos->head != NULL) && (strcmp(texto,"") == 0) ){
            Platillo* newP = crear_platillo(nombre, listaTipos, clasificacion, kiloCalorias, precio);
            insert_map(Platillos, newP->nombre, newP);

            actualizar_menu( Platillos );

            escribir_historial(usuario, "Modificar Platillo", newP->nombre);

            printf("\n   *Platillo Modificado Correctamente\n\n");
        }else{
            printf("\n   *ERROR::Datos Incorrectos\n\n");
        }
    }else{
        printf("\n   *ERROR::Platillo NO Existente\n\n");
    }

    system("pause");
}

void eliminar_Platillo( Mapa* Platillos, User* usuario ){
    system("cls");

    char nombre[MAX];

    printf("\n\tELIMINAR PLATILLO\n\n");

    printf("   Nombre del Platillo        : ");
    gets(nombre);

    arreglar_string(nombre);

    Platillo* auxP = search_map(Platillos, nombre);

    if( auxP != NULL ){
        delete_key_map(Platillos, nombre);

        actualizar_menu(Platillos);

        escribir_historial(usuario, "Eliminar Platillo", nombre);

        printf("\n   *Platillo Eliminado Correctamente\n\n");
    }else{
        printf("\n   *ERROR::Platillo NO Existente\n\n");
    }

    system("pause");
}

void sugerencias_historial( int opcion ){
    system("cls");
    bool flag = true;
    FILE* ARCHIVO;

    if( opcion == 1 ){
        printf("\n\tSUGERENCIAS\n\n");
        ARCHIVO = fopen("SUGERENCIAS.csv","r");
    }else{
        printf("\n\tHISTORIAL\n\n");
        ARCHIVO = fopen("HISTORIAL.csv","r");
    }

    char linea[1024];

    while( fgets(linea, 1023, ARCHIVO) != NULL ){
        flag = false;
        printf("%s\n", linea);
    }

    if( flag ){
        if( opcion == 1 ){
            printf("   *Sin Sugerencias\n\n");
        }else{
            printf("   *Historial Vacio\n\n");
        }
    }

    system("pause");
}

