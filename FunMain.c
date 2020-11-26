/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
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

//--------------------------------------------

void agregar_platillo( Mapa* Platillos ){
    system("cls");

    char nombre[MAX], tipos[MAX], clasificacion[MAX];
    int kiloCalorias;
    long precio;

    printf("\n\t\tAGREGAR PLATILLO\n\n");

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
    getchar();

    arreglar_string(nombre);
    arreglar_string(clasificacion);
    Lista* listaTipos = vectorizar_tipos(tipos);

    Platillo* plat = crear_platillo(nombre, listaTipos, clasificacion, kiloCalorias, precio);

    printf("\n%s\n", plat->nombre);

    NombreTipos* tipo = first_L(plat->tipos);
    while(tipo != NULL){
        printf("%s", tipo->nombre);
        tipo = next_L(listaTipos);
        if(tipo == NULL){
            printf(".\n");
        }else{
            printf(", ");
        }
    }

    printf("%s\n", plat->clasificacion);
    printf("%d\n", plat->kiloCalorias);
    printf("%ld\n", plat->precio);

    system("pause");
}

