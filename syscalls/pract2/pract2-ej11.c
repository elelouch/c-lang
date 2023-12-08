#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define READ 0
#define WRITE 1
#define PAIR 2
#define BUF_SIZE 128

int make_op (char op, int fst, int snd) {
    int result;
    switch (op) {
        case '+' :
            result = fst + snd;
            break;
        case '-' :
            result = fst - snd;
            break;
        case '*' :
            result = fst * snd;
            break;
        case '/' :
            result = fst / snd;
            break;
    }
    return result;
}

int is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int find_op_index(char *buf,int size)
{
    for(int i = 0; i < size; i++) {
        if(is_op(buf[i]))
            return i;
    }
    return -1;
}

int parse_and_make_op (int fd) 
{
    FILE *file;
    char buf[BUF_SIZE];
    char *after_op;
    int op_index;
    int fst;
    int snd;

    file = fdopen(fd,"r");
    fgets(buf,BUF_SIZE,file);

    op_index = find_op_index(buf, BUF_SIZE);
    after_op = &buf[op_index + 1];
    
    fst = atoi(buf);
    snd = atoi(after_op);

    return make_op(buf[op_index],fst,snd);
}

void read_print_from_pipe (int fd) 
{
    FILE *file;
    char buf[BUF_SIZE];
    file = fdopen(fd,"r");
    fgets(buf,BUF_SIZE, file);
    printf(buf);
}
    
void simple_operation(char *op_buf, int size)
{
    int res;
    int to_child_pipe[PAIR];
    int to_parent_pipe[PAIR];
    int child_pid;

    if(pipe(to_child_pipe) || pipe(to_parent_pipe)) {
        perror("pipe");
        exit(1);
    }

    child_pid = fork();

    if (child_pid) {
        close(to_child_pipe[READ]);
        close(to_parent_pipe[WRITE]);

        dprintf(to_child_pipe[WRITE], op_buf);
        read_print_from_pipe(to_parent_pipe[READ]);

        close(to_child_pipe[WRITE]);
        close(to_parent_pipe[READ]);
    }

    if (!child_pid) {
        close(to_child_pipe[WRITE]);
        close(to_parent_pipe[READ]);

        res = parse_and_make_op(to_child_pipe[READ]);
        dprintf(to_parent_pipe[WRITE],"%d\n",res);

        close(to_child_pipe[READ]);
        close(to_parent_pipe[WRITE]);
        exit(0);
    }

}

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE];
    
    do {
        printf("Enter a simple arithmetic operation :\n");
        fgets(buf, sizeof(buf), stdin);
        simple_operation(buf,sizeof(buf));
        printf("Continue? [y/n(other)] : ");
        fgets(buf,sizeof(buf),stdin);
    } while (buf[0] == 'y');

    return 0;
}


