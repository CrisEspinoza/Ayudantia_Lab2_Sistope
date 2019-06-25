#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "funciones.c"

// Funcion que contiene el menu del programa.

void menu(int numeroDeMarco, char archivoEntrada[], char archivoSalida[]){

	int opcion,largo;

    Cache* cache = (Cache*)malloc(sizeof(Cache));
    int* listaPaginas;

	do
    {
        printf( "\n   1. Leer archivo de entrada");
        printf( "\n   2. Realizar ejecución del programa");
        printf( "\n   3. Creditos");
        printf( "\n   4. Salir" );
        printf( "\n\n   Introduzca opcion (1-4): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: printf("Leyendo archivo de entrada ... \n");
            		largo = contarPaginas(archivoEntrada);
            		listaPaginas = (int*)malloc(sizeof(int)*largo);
            		listaPaginas = leerArchivo(cache,archivoEntrada,largo);	
                    break;

            case 2: printf("Realizando traza ... \n");
            		Fifo(listaPaginas,numeroDeMarco,archivoSalida,largo);
                    break;

            case 3: printf("\n");
            		printf("\n");
            		printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
                    printf(" * Universidad santiago de chile \n");
                    printf("\n");
                    printf("\n");
                    break;
        }

    }while(opcion!=4);
}