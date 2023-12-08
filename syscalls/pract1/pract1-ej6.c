#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#define LAST_ARG 2
#define SHOW_RFIL 'e'
#define SHOW_DIR 'd'
#define SHOW_FINO 'i'

char *cat(const char *, const char *);

int main(int argc, char *argv[]){
    DIR *rootdir;
    struct stat child_stat;
    struct dirent *child_entity;
    mode_t child_mode;
    char *newpath,*pivot;
    char option;

    if(argc != 3){
        return -1;
    }
    option = getopt(argc,argv,"edi");
    rootdir = opendir(argv[LAST_ARG]);
    
    while((child_entity = readdir(rootdir))){
        // catenates '/' to the child entity name of the desired dir
        pivot = cat("/",child_entity->d_name); 
        
        // now the directory's path is catenated to the name
        // of the child entity
        newpath = cat(argv[LAST_ARG],pivot); 
        // asks for the status of the desired file entity
        stat(newpath,&child_stat);
        free(pivot);
        free(newpath);

        child_mode = child_stat.st_mode;

        if(S_ISREG(child_mode)){
            if(option == SHOW_RFIL){
                printf("%s\n", child_entity->d_name);
            }else if(option == SHOW_FINO){
                printf("%ld - %s\n", child_stat.st_ino, child_entity->d_name);
            }
        }

        if(S_ISDIR(child_mode) && option == SHOW_DIR)
            printf("%s\n", child_entity->d_name);
    }
    // PROBLEMA : Algunos directorios se reconocen como archivos regulares
    // ISREG retorna 1 en directorios, raro

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
    for(int i = 0; i < size2; i++){
        new_str[size1+i] = sola[i];
    }

    return new_str;
}
