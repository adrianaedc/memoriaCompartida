#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define max 100

#ifdef __linux__
    int ingresarChat(int numero);
    int agregar_msg(int numero, char *msg);
    char* consultar_msg(int numero);
    void modificar_msg(int numero,char valor[100]);
    void destruir_msg(int clave);

    int ingresarChat(int numero){
        
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        char *mcompartida = NULL;

        archivocompartido = fopen("/tmp/acompartido","w+");
        clavecompartida = ftok("/tmp/acompartido",numero);

        mem = shmget(clavecompartida,sizeof(char *)*100,0777 | IPC_CREAT);
        mcompartida = (char *) shmat(mem,NULL,0);

 /*       printf ("Creando el segmento %d de memoria compartida\n\n",mem);

        shmctl (mem, IPC_RMID, (struct shmid_ds *)NULL);
        unlink ("/tmp/acompartido");*/
    }//ingresarChat

    int agregar_msg(int numero, char *msg){
        ingresarChat(numero);
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        int contador = 0, valor = 0;
        char *mcompartida = NULL, cadena[500];

        archivocompartido = fopen("/tmp/acompartido","w+");
        clavecompartida = ftok("/tmp/acompartido",numero);

        mem =  shmget(clavecompartida,sizeof(char *)*100,0777 | IPC_CREAT);
        mcompartida = (char *) shmat (mem,NULL,0);
        int result = sprintf (mcompartida,"%s",msg);
        return result;
    }//agregar mensjae

    void modificar_msg(int numero,char valor[100]){
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        char *mcompartida = NULL;

        archivocompartido = fopen("/tmp/acompartido","w+");
        clavecompartida = ftok("/tmp/acompartido",numero);

        mem =  shmget(clavecompartida,sizeof(char *)*100,0777);
        mcompartida = (char *) shmat (mem,NULL,0);
        sprintf (mcompartida,"%s",valor);
    }//modificar mensjae


    char* consultar_msg(int numero){ 
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        char *mcompartida = NULL;

        archivocompartido = fopen("/tmp/acompartido","w+");
        clavecompartida = ftok("/tmp/acompartido",numero);

        mem =  shmget(clavecompartida,sizeof(char *)*100,0777);
        mcompartida = (char *) shmat (mem,NULL,0);
        return mcompartida;
    }//consultar mensaje

    void destruir_msg(int clave){
        FILE *archivocompartido;
        key_t clavecompartida;
        int mem = 0;
        char *mcompartida = NULL;

        archivocompartido = fopen("/tmp/acompartido","w+");
        clavecompartida = ftok("/tmp/acompartido",clave);

        mem =  shmget(clavecompartida,sizeof(char *)*100,0777);
        mcompartida = (char *) shmat (mem,NULL,0);
        sprintf (mcompartida,"%s"," ");
    }//destruir mensaje
#elif _WIN32
    #define SO "Windows"
#endif