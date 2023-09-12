#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>

#define BUF_SIZE 1024

#define PATTERN argc-1
#define SIGNAL 1
#define PROC_DIR "/proc"

char *cat(const char *, const char *);

int main(int argc, char *argv[]){
    DIR *processes_dir;
    struct dirent *process_dirent;
    int pid, fd_cmdline, signal;
    char *p1,*p2;
    char buffer[BUF_SIZE];
    if(argc > 3 || argc < 2){
        printf("usage : \n my_pkill [-signal] pattern\n");
        return -1;
    }

    /**
     * - Read on a loop /proc using readdir until it sends null
     * - Get those entities that have a number as a name (atoi returns 0 on fail);
     * - Inside these entities, use the path to obtain the cmdline file and
     *   use read() syscall in the cmdline file to get the full path. Here would be
     *   useful to use the amount of read characters(read_chars), to add 
     *   buf[read_chars] = '\0'
     * - Find subtring using strstr(char *haystack, char* needle) which return NULL on fail.
     * - If the substring is on the string, use kill(pid_t pid,int sig) the pid.d_name
    */
    signal = atoi(argv[SIGNAL] + 1); // gets the character after -
    if(argv[1][0] == '-' && !signal){
        printf("signal must be an integer\n");
        return -1;
    }

    processes_dir = opendir(PROC_DIR);
    process_dirent = readdir(processes_dir);

    while((process_dirent = readdir(processes_dir))){
        pid = atoi(process_dirent->d_name);
        if(pid){
            p1 = cat("/",process_dirent->d_name); // /pid
            p2 = cat(PROC_DIR,p1); // /proc/pid
            free(p1);
            p1 = cat(p2,"/cmdline"); // /proc/pid/cmdline
            free(p2);

            fd_cmdline = open(p1,O_RDONLY);
            free(p1);

            read(fd_cmdline,buffer,BUF_SIZE); // reads the file, already adds '\0' at the end
                                              
            if(strstr(buffer, argv[PATTERN])){
                kill(pid, signal ? signal : SIGTERM);
            }
        }
    }

    return 0;
}


char *cat(const char *compa, const char *sola){
    int size1 = 0, size2 = 0;
    char *new_str;

    while(compa[size1] != '\0')
        size1++;
    while(sola[size2] != '\0')
        size2++;

    new_str = malloc(sizeof(char) * (size1 + size2 + 1));

    if(!new_str)
        return new_str;

    for(int i = 0; i < size1; i++){
        new_str[i] = compa[i];
    }
    for(int j = 0; j < size2; j++){
        new_str[size1+j] = sola[j];
    }

    new_str[size1+size2] = '\0';

    return new_str;
}
