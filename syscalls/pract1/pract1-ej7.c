#include <stdio.h>
#include <sys/stat.h>

// chmod

int my_atoi(char *);

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Not valid arguments, usage: \n\tmy_chmod octal file\n");
        return -1;
    }

    chmod(argv[2], my_atoi(argv[1]));
}

int my_atoi(char *strptr){
    int digitval;
    int total = 0;
    
    // [48,57]
    for (int i = 0; strptr[i] != '\0'; i++) {
        digitval = (int)strptr[i] - 48;
        if(9 < digitval || digitval < 0){
            return -1;
        }
        total = total * 10 + digitval;
    }

    return total;
}
