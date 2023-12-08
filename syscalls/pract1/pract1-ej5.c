#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    char buf[BUFFER_SIZE];
    int read_fd;
    int characters_read;
    int out_fd = STDOUT_FILENO;
    int argv_size = argc;
    int i;
    
    if(getopt(argc,argv,"o") == (int)'o'){
        argv_size -= 2;
        out_fd = open(argv[argc-1],O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
        /* abre el ultimo archivo del vector argv(argc-1)
         * si este no esta, lo crea y concede permisos al user para escribr y leer 
         * en el archivo
         */

    }

    i = argc == 1 ? 0 : 1;

    while(i < argv_size){
        read_fd = i == 0 ? STDIN_FILENO : open(argv[i],O_RDONLY);
        do{
            characters_read = read(read_fd, buf, BUFFER_SIZE);
            write(out_fd,buf,characters_read);
        }while(characters_read);
        i++;
    }

}
