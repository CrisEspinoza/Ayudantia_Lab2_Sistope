#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "struct.h"

// Algoritmos de reemplazo

void Fifo(int* listaPaginas, int numeroMarcos, char nombreArchivo[], int largo){

    int i,j;

    FILE *archivo;
    float tasaHit,tasaMiss;

    printf("El nombre del archivo de salida es: %s\n", nombreArchivo);
    nombreArchivo = strcat(nombreArchivo,".out");
    archivo = fopen(nombreArchivo, "w"); 
    
    fprintf(archivo,"\n");
  

    // Iniciar cache

    Cache* cache = iniciarCache(numeroMarcos);

    for(i = 0 ; i < largo ; i++){

        //printf("Numero de pagina es: %d \n" , listaPaginas[i]);

        if (estaEnCache(cache,listaPaginas[i])){
            cache->hit++;
        }
        else{
            colocarPagina(cache,listaPaginas[i]);
            cache->miss++;
        }

        for (j = 0; j < numeroMarcos; j++)
        {
            if (j == (numeroMarcos-1)){
                
                if(cache->marco[j].pagina == -1)
                    fprintf(archivo, "  \n");
                else        
                    fprintf(archivo, "%d \n", cache->marco[j].pagina);
            }
            else{

                if(cache->marco[j].pagina == -1)
                    fprintf(archivo, "  - ", cache->marco[j].pagina);
                else    
                    fprintf(archivo, "%d - ", cache->marco[j].pagina);
            }
        }

    }

    fprintf(archivo,"\n");
    fprintf(archivo,"\n");
    fprintf(archivo,"Las estadisticas del cache realizado: \n");
    fprintf(archivo,"\n");

    tasaHit = ( ( (float) cache->hit) / (cache->miss + cache->hit) ) * 100;
    tasaMiss = ( ( (float) cache->miss) / (cache->miss + cache->hit) ) * 100; 

    fprintf(archivo,"Cantidad de Hit obtenidos: %d \n", cache->hit );
    fprintf(archivo,"Cantidad de Miss obtenidos: %d \n", cache->miss );
    fprintf(archivo,"Tasa de Hit: %f \n", tasaHit);
    fprintf(archivo,"Tasa de Miss: %f ", tasaMiss);     

    fclose(archivo);
}

// Funciones auxiliares

void mostrarCache(Cache* cache){

    printf("\n");
    printf("INICIO DE UNA NUEVA CONSULTA\n");
    printf("\n");

    int i;
    for (i = 0; i < cache->numeroDeMarco; i++)
    {
        printf("El numero de la cache es: %d y contiene un tiempo de: %d \n", cache->marco[i].pagina,cache->marco[i].contador );
    }

    printf("\n");
    printf(" FIN DE ESTA NUEVA CONSULTA \n");
    printf("\n");

}

void colocarPagina(Cache* cache, int pagina){

    //printf("Aca\n");
    if (llenaCache(cache))
        reemplazo(cache,pagina);
    else{
        //printf("No esta llena \n");
        insertarPagina(cache,pagina);
    }
}

void insertarPagina(Cache* cache, int pagina){

    int i;
    for (i = 0; i < cache->numeroDeMarco; i++)
    {
        cache->marco[i].contador++;
        if (cache->marco[i].pagina == -1){
            cache->marco[i].pagina = pagina;
            break;
        }
    }
}

void reemplazo(Cache* cache, int pagina){

    int reemplazo = 0,i;

    for (i = 1; i < cache->numeroDeMarco; i++)
    {
        if (cache->marco[reemplazo].contador < cache->marco[i].contador)
            reemplazo = i;
        cache->marco[i].contador++;
    }

    printf("Indice elegido es: %d\n", reemplazo);
    printf("Mostrando cache \n");
    printf("\n");
    mostrarCache(cache);
    printf("\n");

    cache->marco[reemplazo].contador = 0;
    cache->marco[reemplazo].pagina = pagina;
}

int llenaCache(Cache* cache){

    int i;
    for (i = 0; i < cache->numeroDeMarco; i++)
    {
        if(cache->marco[i].pagina == -1)
            return 0;
    }
    return 1;
}

int estaEnCache(Cache* cache, int pagina){

    int i;

    for (i = 0; i < cache->numeroDeMarco; i++)
    {
        //printf("La cache tiene las paginas: %d\n", cache->marco[i].pagina);
        if (pagina == cache->marco[i].pagina)
            return 1;
    }

    return 0;
}

Cache* iniciarCache(int numeroMarcos){

    Cache* cache = (Cache*)malloc(sizeof(Cache));

    cache->marco = (Marco*)malloc(sizeof(Marco)*numeroMarcos);
    cache->numeroDeMarco = numeroMarcos;
    cache->hit = 0;
    cache->miss = 0;

    int i;
    for(i = 0; i < numeroMarcos; i++){
        cache->marco[i].contador = 0;
        cache->marco[i].pagina = -1;
    }

    return cache;
}

// Funciones encargadas de leer y escribir archivos

int contarPaginas(char nombreArchivo[]){

    printf("El nombre del archivo es: %s \n", nombreArchivo );
    FILE* archivo = fopen(nombreArchivo,"r");

    int numero,contador = 0;

    while (!feof(archivo))
    {  
        fscanf(archivo,"%d\n",&numero);
        contador++;
    }

    fclose(archivo);

    return contador;
}

int* leerArchivo(Cache* cache, char nombreArchivo[], int largo){

    int* listaPaginas = (int*)malloc(sizeof(int)*largo);

    printf("El nombre del archivo es: %s \n", nombreArchivo );
    FILE* archivo = fopen(nombreArchivo,"r");

    int contador = 0,numero;

    while (!feof(archivo))
    {  
        fscanf(archivo,"%d\n",&numero);
        printf("%d\n", numero);
        listaPaginas[contador] = numero;
        contador++;
    }

    fclose(archivo);

    return listaPaginas;
}