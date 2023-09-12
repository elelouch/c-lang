#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define CHILD_PID 0
#define MES 1
#define ANIO 2

void emosion(int);

int main(int argc, char *argv[]){
    if(argc != 3)
        return 1;

    pid_t pid_holder;
    char *mes = argv[MES];
    char *anio = argv[ANIO];
    char cal[] = "/usr/bin/cal";
    char *nargv[] = {cal,mes,anio,NULL};

    pid_holder = fork();

    if (pid_holder == CHILD_PID ) {
        execve(cal, nargv, NULL);
    }else{
        printf("Esperando ... por mi hijo %d :c\n", pid_holder);
        wait(&pid_holder);
    }
    pid_holder = fork();
    if (pid_holder == CHILD_PID) {
        signal(SIGUSR1, emosion);
        pause();
        _exit(0);
    }else{
        printf("Mandale un SIGUSR1(10) a este %d \n", pid_holder);
        wait(&pid_holder);
    }

    return 0;
}

void emosion(int signal){ 
    printf("Recibida la senial SIGUSR1, la tengo al pedo jajaa \n");
}
