#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#define SEGMENT_ID 1 
#define ASSIGN_PLAYER_ID 2 
#define ID 0 
#define NRO 1
#define ID_DIRECTOR -1
#define MAX_PARTICIPANTS 3
#define MAX_NUM 50
#define TRUE 1
#define FALSE 0

int num_three_in_digits(int num)
{
    while(num > 0) {
        if ((num % 10) == 3) {
            return TRUE;
        }
        num /= 10;
    }
    return FALSE;
}

int generate_next (int num) 
{
    do{
        num++;
    } while(num < MAX_NUM && num_three_in_digits(num));

    return num;
}
int main(int argc, char *argv[]) 
{
    int seg_id;
    int player_id = -1;
    int num_cpy;
    int *buf;

    seg_id = atoi(argv[SEGMENT_ID]);
    
    while(TRUE) {
        if((buf = shmat(seg_id,NULL,0)) == (void*)-1){
            perror("shmat");
            exit(1);
        }

        if(player_id == -1) {
            player_id = buf[ASSIGN_PLAYER_ID];
            buf[ASSIGN_PLAYER_ID]++;
        }

        if (buf[ID] == player_id) {
            num_cpy = buf[NRO];
            buf[NRO] = generate_next(num_cpy);
            buf[ID] = buf[NRO] >= MAX_NUM ? ID_DIRECTOR : (buf[ID] + 1) % MAX_PARTICIPANTS;
            printf("Proceso : %d, con reemplazo %d -> %d\n", player_id, num_cpy, buf[NRO]);
        }

        if (buf[ID] == ID_DIRECTOR) {
            exit(0);
        }

        shmdt(buf);
        sleep(1);
    }

    return 0;
}
