#include <stdio.h>
#include <unistd.h>

int main(){
    int i,j,k;
    // fork crea un nuevo proceso duplicando al padre y siempre devuelve el pid del hijo
    // como es una copia, al principio el hijo solo tiene punteros al valor del padre
    // utilizando la tecnica copy on write (implicit shadowing).
    // Cuando se escribe al hijo, se rompe el puntero al padre. Cuando se escribe en el padre,
    // se copia en el hijo.
    
    for(i = 0; i < 3; i++){
        j = getpid();   // j obtiene el id actual del proceso
        k = fork();     // k es 0 en el hijo y distinto de cero en el padre
        printf("%d - %d\n", j, k);
    }

    // 123 - 

    return 0;
}
