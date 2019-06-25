// Se importan las cosas que ayudaran al funcionamiento del codigo 
#include <stdio.h>
#include <string.h>
#include <locale.h>

// Definimos las estructuras a ocupar dentro de la aplicacion

typedef struct Marco
{
	int contador;
	int pagina;
} Marco;


typedef struct Cache
{
	Marco* marco;
	int numeroDeMarco;
	int hit;
	int miss;
} Cache;


//Funciones a utilizar dentor del programa

void Fifo(int* listaPaginas, int numeroMarcos, char nombreArchivo[], int largo);
Cache* iniciarCache(int numeroMarcos);
int contarPaginas(char nombreArchivo[]);
int* leerArchivo(Cache* cache, char nombreArchivo[], int largo);
int estaEnCache(Cache* cache, int pagina);
int llenaCache(Cache* cache);
void insertarPagina(Cache* cache, int pagina);
void colocarPagina(Cache* cache, int pagina);
void reemplazo(Cache* cache, int pagina);
void mostrarCache(Cache* cache);