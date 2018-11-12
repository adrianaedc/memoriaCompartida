#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memcomp.h"

void menu(int pasw, int opcion);
int opciones();

int main(int argc, char const *argv[])
{
    int password = 0, ascii, id;
    char letra = ' ',clave[5];
 
    do{
        printf("Ingrese el nombre del Chat: ");
        scanf("%s",clave);
        //gets(clave);
        if (strlen(clave)>4)
            printf("El nombre del chat no puede tener más de 4 caracteres\n");        
    }while(strlen(clave)>4); 
    
    for(int i = 0; i < strlen(clave); i++){
        letra = clave[i];
        ascii = (int)toupper(letra);
        password = (password*100)+ascii;
    }//for
    printf("passw: %i",password);
    menu(password, opciones());
    return 0;
}//main
int opciones(){
    int opcion = 0;
    do{
        opcion = 0;
        printf("\n\n----------------------------------\n");
        printf("1.- Agregar Mensaje\n");
        printf("2.- Modificar Mensaje\n");
        printf("3.- Consultar Mensaje\n");
        printf("4.- Destruir Mensaje\n");
        printf("5.- Salir\n");
        printf("Opcion: ");
        scanf("%i",&opcion);
        printf("\n\n----------------------------------\n");
        
        if (opcion>5 || opcion<0)
            printf("Ingrese una opción valida\n");        
    }while(opcion>5 || opcion<0); 
    return opcion;
}
void menu(int psw, int opcion){
    int password = 0, ascii, id, add;
    char letra = ' ',clave[5], cadena[500];
    
    switch (opcion){
        case 1:
            printf ("--> Ingrese un Mensaje: ");
            fflush(stdin);
            while(getchar()!='\n');
            fgets(cadena,500,stdin);
            printf("%s",cadena);
            agregar_msg(psw, cadena)>-1?printf("\nMensaje agregado con éxito\n"):printf("\nEl mensaje no se pudo enviar\n");
            menu(psw,opciones());
            break;
        case 2:                
            do{
                printf ("--> Ingrese la sala de chat a modificar: ");
                scanf("%s",clave);
                if (strlen(clave)>4)
                    printf("El nombre del chat no puede tener más de 4 caracteres\n");        
            }while(strlen(clave)>4); 
            
            for(int i = 0; i < strlen(clave); i++){
                letra = clave[i];
                ascii = (int)toupper(letra);
                password = (password*100)+ascii;
            }//for
            printf ("--> Ingrese un Mensaje: ");
            fflush(stdin);
            while(getchar()!='\n');
            fgets(cadena,500,stdin);
            modificar_msg(password,cadena);
            menu(psw,opciones());
            break;
        case 3:
            printf ("\n\n--> Mensaje Recibido: %s\n", consultar_msg(psw));
            menu(psw,opciones());
            break;
        case 4:                
            do{
                printf ("--> Ingrese la sala de chat a limpiar: ");
                scanf("%s",clave);
                if (strlen(clave)>4)
                    printf("El nombre del chat no puede tener más de 4 caracteres\n");        
            }while(strlen(clave)>4); 
            
            for(int i = 0; i < strlen(clave); i++){
                letra = clave[i];
                ascii = (int)toupper(letra);
                password = (password*100)+ascii;
            }//for
            destruir_msg(password);
            menu(psw,opciones());
            break;
        default:
            break;
    }//switch
}