#include "kruskal.h"

int main(){
    int M_Costos[VERTICES][VERTICES]; // matriz con los pesos
    arista *cola = NULL; // cola de prioridad
    int i,j;

    for(i = 0; i < VERTICES; i++){ //diagonal superior
        for(j = i+1; j < VERTICES; j++){
            printf("\nIngrese el costo de lado entre vertices %d y %d: ",i,j);
            scanf("%d",&M_Costos[i][j]);

            if(M_Costos[i][j])
                inserta(i,j,M_Costos[i][j], &cola); //inserta en cola de prioridad
        }
    }

    kruskal(&cola);
    return 0;
}
