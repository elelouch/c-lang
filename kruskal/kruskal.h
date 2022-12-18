#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define VERTICES 5
#define NIL 0

typedef int vertice;
typedef int tipo_nombre;

typedef struct _ARISTA{
    vertice vertice_u;
    vertice vertice_v;
    int costo;
    struct _ARISTA *sig;
}arista;

//typedef struct _RAMA{
//    arista lado;
//    struct _RAMA *sig;
//}rama;

typedef struct _ENCABEZADO{ //encabezado es el "comienzo" del conjunto
    int cuenta;            //cuenta es la cantidad de vertices que "absorbio" un conjunto
    int primer_elemento;   //los primeros elementos de los conjuntos se pondran en 0 cuando el conjunto sea "absorbido"
}encabezado;

typedef struct _NOMBRE{
    tipo_nombre nombre_conjunto; //nombre del conjunto al que pertenece el vertice, cambiara al conjunto que lo absorba
    // Si ambos vertices de un lado pertenecen al mismo conjunto, no tomo en cuenta el lado
    int siguiente_elemento;      //
}nombre;

// Si se recibe un lado (x-y,w) con w siendo el peso del mismo.
// Para nombre x: El nombre_conjunto de x seguira intacto. El siguiente_elemento de x sera y
// Para nombre y: El nombre_conjunto de y sera el de x. El siguiente_elemento de y seguira intacto.

// conjunto combina encuentra = disjoint-set data structure

typedef struct _CONJUNTO_CE{ // conjunto combina-encuentra, las operaciones son en este conjunto
    nombre nombres[VERTICES]; //nombre de cada conjunto al que pertenece el vertice, [v]
    encabezado encabezamientos[VERTICES]; // array con los miembros del conjunto combina-encuentra
}conjunto_CE;

void inicial(tipo_nombre, conjunto_CE*); // nombre de un componente que pertenece al conjunto ce que inicialmente tiene al vertice tipo_elemento
void combina(tipo_nombre,tipo_nombre,conjunto_CE*); //combina las componentes conexas de un grafo
tipo_nombre encuentra(vertice,conjunto_CE*);
void kruskal(arista**);

void inserta(vertice,vertice,int,arista**);
arista *sacar_min(arista**);
void lista(arista*);
