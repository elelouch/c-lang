#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ID 0
#define NRO 1
#define PLAYER_ID 2
#define SIZE 12

int main (int argc, char *argv[])
{
    key_t key = 8765;
    int seg_id;
    int *buf;

    if((seg_id = shmget(key, SIZE, IPC_CREAT | 0666)) == -1){
        perror("shmget");
        exit(1);
    }
    printf("id de segmento %d. Recuerde pasarlo a los jugadores.\n", seg_id);
    if((buf = shmat(seg_id, NULL,0)) == (void*)-1){
        perror("shmat");
        exit(1);
    }
    buf[ID] = 0;
    buf[NRO] = 0;
    buf[PLAYER_ID] = 0;
    while(buf[ID] != -1) {
        sleep(1);
    }
    shmdt(buf);
    shmctl(seg_id, IPC_RMID,NULL);
    return 0;
}

