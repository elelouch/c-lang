#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAVORABLE 1
#define DESFAVORABLE 0
#define PERTENECE 1
#define NO_PERTENECE 0
#define TAMANIO_NOMBRE 10

typedef struct legislador{
    char nombre[TAMANIO_NOMBRE];
    struct legislador *siguiente;
}legislador;

void inserta(legislador**,char*);
void mostrar(legislador*);
int miembro(legislador*, char *);
void suprime(legislador**, char*);
void manage_lists(legislador**, legislador**,char*,int);
void cleanstdin();

int main(){
    legislador *chicos_buenos = NULL;
    legislador *chicos_malos = NULL;
    char comando[TAMANIO_NOMBRE+1]; // +1 para el comando
    do{
        printf("Inserte: \nF+(Nombre de legislador a favor)\nD+(Nombre de legislador en contra)\n");
        printf("B+(Nombre de legislador que se abstiene)\nE+(Cualquier cosa. Para terminar el proceso)\n");
        fscanf(stdin, "%10s", comando);
        cleanstdin();
        if(comando[0] == 'F'){
            manage_lists(&chicos_buenos, &chicos_malos, comando, FAVORABLE);
        }else if(comando[0] == 'D'){
            manage_lists(&chicos_buenos, &chicos_malos, comando, DESFAVORABLE);
        }
    }while(comando[0] != 'E');
    printf("Cerrando...\n");
    return 0;
}

void inserta(legislador **conjunto, char *nuevo_nombre){
    legislador *aux = (legislador *)malloc(sizeof(legislador));
    strncpy(aux -> nombre, nuevo_nombre, TAMANIO_NOMBRE-1);
    aux -> siguiente = NULL;
    // si el puntero al conjunto no apunta a nada, que apunte al auxiliar
    if(*conjunto == NULL){
        *conjunto = aux;
        return;
    }
    // si no agregar aux al comienzo del conjunto
    aux -> siguiente = *conjunto;
    *conjunto = aux;
}
void suprime(legislador **conjunto, char *legislador_a_borrar){
    legislador *aux = NULL;
    if(*conjunto == NULL)
        return;
    aux = ((*conjunto)-> siguiente);

    if(!strcmp((*conjunto)->nombre, legislador_a_borrar)){
        free(*conjunto);
        *conjunto = aux;
    }else if(aux != NULL && !strcmp(aux->nombre, legislador_a_borrar)){
        //Si el siguiente (aux) no es nulo y hay que borrarlo apunto al siguiente y libero el aux
        (*conjunto)->siguiente = aux->siguiente;
        free(aux);
    }else{
        suprime(&(*conjunto)->siguiente ,legislador_a_borrar);
    }
}
void mostrar(legislador *conjunto){
    if(conjunto == NULL){
        printf("\n");
        return;
    }
    printf("%s |", conjunto->nombre);
    mostrar(conjunto->siguiente);
}
int miembro(legislador *conjunto, char *nombre_leg){
    if(conjunto == NULL)
        return NO_PERTENECE;
    if(!strcmp(conjunto->nombre,nombre_leg))
        return PERTENECE;

    return miembro(conjunto->siguiente, nombre_leg);
}
void manage_lists(legislador **chicos_buenos,legislador **chicos_malos,char *comando,int tipo_voto){
    char nombre_legislador[TAMANIO_NOMBRE];
    strncpy(nombre_legislador,&comando[1],TAMANIO_NOMBRE-1);

    if(!miembro(*chicos_buenos, nombre_legislador) && tipo_voto == FAVORABLE){
        suprime(chicos_malos, nombre_legislador);
        inserta(chicos_buenos, nombre_legislador);
    }else if(!miembro(*chicos_malos, nombre_legislador) && tipo_voto == DESFAVORABLE){
        suprime(chicos_buenos, nombre_legislador);
        inserta(chicos_malos, nombre_legislador);
    }
    printf("\nA FAVOR: ");
    mostrar(*chicos_buenos);
    printf("EN CONTRA: ");
    mostrar(*chicos_malos);
    printf("\n");
}
void cleanstdin(){
    char c;
    while(( c = getchar() ) != EOF && c != '\n');
}
