
// Bibliotecas a utilizar
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "menu.c"

int main(int argc, char *argv[])
{  
    char archivoEntrada[50];
    char archivoSalida[50];
    int numeroDeMarco,c;

    // Recibiendo parametros por consola
    opterr = 0;

    while ((c = getopt(argc, argv, "m:e:o:")) != -1) switch (c) {

        case 'm':
            sscanf(optarg, "%d", &numeroDeMarco);
            printf("Numero de marcos: %d \n", numeroDeMarco);
            break;

        case 'e':
            sscanf(optarg, "%s", archivoEntrada);
            printf("Nombre de archivo de entrada: %s \n", archivoEntrada);
            break;

        case 'o':
            sscanf(optarg, "%s", archivoSalida);
            printf("Nombre de archivo de entrada: %s \n", archivoSalida);
            break;

        case '?':
        if (optopt == 'm' || optopt == 'e' ||   optopt == 'o'){
            fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
            return 0;
        }
    }

    menu(numeroDeMarco,archivoEntrada,archivoSalida);

    return 0;
}