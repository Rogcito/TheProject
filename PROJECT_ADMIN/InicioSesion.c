/*
    var = camelCase
    struct = camelCase
    function = snake_case
    definition = Upper Case
    FILES = Upper Case
*/
#include "InicioSesion.h"

User* crear_usuario( const char* user, const char* password ){
    User* newU = (User*)malloc(sizeof(User));

    strcpy(newU->user, user);
    strcpy(newU->password, password);

    return newU;
}

//--------------------------------------------

void cargar_usuarios( Mapa* Usuarios ){
    FILE* USERS = fopen( "USUARIOS.csv", "r" );

    char linea[1024];
    while( fgets( linea, 1023, USERS) != NULL ){
        const char* user = get_csv_field( linea, 0);
        const char* password = get_csv_field( linea, 1);
        User* newU = crear_usuario( user, password);
        insert_map( Usuarios, newU->user, newU );
    }
    fclose(USERS);
}

void* iniciar_sesion( Mapa* Usuarios ){
    int intentos = 3, ind = 0;
    char user[MAX], password[MAX];

    do{
        system("cls");
        printf("\n\tINICIAR SESION\n\n");

        if( ind == 1){
            printf("    *Usuario NO Existe\n");
        }else if( ind == 2){
            printf("    *Contrasena Incorrecta\n");
        }

        printf("   Intentos     : %d\n", intentos);

        printf("\n   -USUARIO     : ");
        gets(user);
        printf("   -CONTRASENA  : ");
        gets(password);

        User* auxU = search_map(Usuarios, user);

        if( auxU != NULL ){
            if( strcmp(password, auxU->password) == 0 ){
                return auxU;
            }else{
                ind = 2;
            }
        }else{
            ind = 1;
        }

        intentos--;

    }while( intentos > 0 );
    return NULL;
}

void* crear_cuenta( Mapa* Usuarios ){
    char user[MAX], password[MAX], verPassword[MAX];
    int ind = 0;

    do{
        system("cls");
        printf("\n\tCREAR CUENTA\n");

        if(ind == 1){
            printf("\n    *Usuario Existente\n");
        }else if(ind == 2){
            printf("\n    *Contrasenas NO Coinciden\n");
        }

        printf("\n   USUARIO         : ");
        gets(user);
        printf("   CONTRASENA      : ");
        gets(password);
        printf("   Ver. CONTRASENA : ");
        gets(verPassword);

        User* auxU = search_map(Usuarios, user);
        if(auxU != NULL){
            ind = 1;
        }else{
            if( strcmp( password, verPassword) == 0 ){
                User* newU = crear_usuario(user, password);
                FILE* USERS = fopen( "USUARIOS.csv", "a" );
                fprintf( USERS, "%s,%s\n", user, password);
                fclose(USERS);
                return newU;
            }else{
                ind = 2;
            }
        }
    }while(true);
}

//--------------------------------------------

void* inicio_sesion(){
    int opc = 0;
    char text[MAX];
    User* auxU = NULL;
    Mapa* Usuarios = crear_mapa(5);

    cargar_usuarios(Usuarios);

    do{
        system("cls");
        printf("\n\tBIENVENIDO\n\n");

        printf("   1-.INICIAR SESION\n");
        printf("   2-.CREAR CUENTA\n");
        printf("   3-.SALIR\n");
        printf("   Opcion : ");
        scanf("%d", &opc);
        gets(text);

        switch(opc){
            case 1:
                auxU = iniciar_sesion( Usuarios );
                if( auxU != NULL ){
                    return auxU;
                }
            break;
            case 2:
                return crear_cuenta( Usuarios );
            break;
        }

        if(opc != 3){ opc = 0; }

    }while( opc != 3 );
    return NULL;
}
