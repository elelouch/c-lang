#include <stdio.h>
#include <unistd.h>

int main(){
    int child_pid = fork(); // fork returns the pid of the child node

    if(child_pid != 0) for(;;); // el padre se queda loopeando para siempre
    if(child_pid == 0) execl("/bin/ls", "ls", "-l", NULL); // el hijo se convierte en ls y luego termina

    printf("mi pid es %d", child_pid);
    return 0;
}
