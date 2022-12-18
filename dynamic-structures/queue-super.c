#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 16
#define CHECKOUT_SIZE 10

//FREE -> OCCUPIED

typedef struct CLIENT{
    int items;
    char name[BUFFER];
    struct CLIENT *next;
}client;

typedef struct CASHIER_Q {
    char state[BUFFER];
    int total_items;
    client *front;
    client *back;
}cashier_queue;

cashier_queue *checkouts[CHECKOUT_SIZE] = {NULL};

void add_cashier();
void add_client(int, char*);
void remove_cashier(int);
void show_checkouts();
void show_cashier_queue(cashier_queue *);
int get_queue_less_items();
void traverse_queue();
void remove_client(cashier_queue*);

int main(void){

    return 0;
}

void show_checkouts(){
    int i;
    for(i = 0; i < CHECKOUT_SIZE; i++){
        if(checkouts[i]){
            printf("CHECKOUT N: %d OPEN\n",i);
            show_cashier_queue(checkouts[i]);
        }else{
            printf("CHECKOUT N: %d CLOSED\n",i);
        }
    }
}
void add_cashier(){
    cashier_queue *new_cashier = malloc(sizeof(cashier_queue));
    int i;
    strncpy(new_cashier->state, "FREE", BUFFER);
    new_cashier->front = NULL;
    new_cashier->back = NULL;
    new_cashier->total_items = 0;

    for(i = 0; i < CHECKOUT_SIZE; i++){
        if(!checkouts[i]){
            checkouts[i] = new_cashier;
            return;
        }
    }
    free(new_cashier);
}

int get_queue_less_items(){
    int items_got, i = 0, cashier_with_less_items = -1;

    while(i < CHECKOUT_SIZE){
        if(checkouts[i]){
            items_got = checkouts[i]->total_items;
            cashier_with_less_items = i;
            break; // if it finds a not null pointer, get out
        }
        i++;
    }

    while(i < CHECKOUT_SIZE-1){
        if(checkouts[i+1] && checkouts[i+1]->total_items < items_got){
            items_got = checkouts[i+1]->total_items;
            cashier_with_less_items = i+1;
        }
        i++;
    }

    return cashier_with_less_items;
}

void add_client(int picked_up_items, char *name){
    client *new_client = malloc(sizeof(client));
    int i;
    strncpy(new_client->name,name,BUFFER);
    new_client->items = picked_up_items;
    new_client->next = NULL;

    i = get_queue_less_items();
    if(i == -1){
        printf("No cash register available, wait until one's added\n");
        free(new_client);
        return;
    }


    if(!checkouts[i]->back){
        checkouts[i]->front = new_client;
        checkouts[i]->back = new_client;
        checkouts[i]->total_items += picked_up_items;
        strncpy(checkouts[i]->state, "OCCUPIED",BUFFER);
    }else{
        checkouts[i]->back->next = new_client;
        checkouts[i]->back = new_client;
        checkouts[i]->total_items += picked_up_items;
    }
}

void show_cashier_queue(cashier_queue *working_q){
    client *aux;
    if(!working_q){
        printf("No cashier on this checkout\n");
        return;
    }
    aux = working_q->front;

    while(aux){
        printf("%s | ",aux->name);
        aux = aux->next;
    }
    printf("\n");
}

void traverse_queue(){
    int i;
    for(i = 0 ; i < CHECKOUT_SIZE; i++){
        if(checkouts[i] && checkouts[i]->total_items > 0){
            checkouts[i]->front->items -= 5;
            checkouts[i]->total_items -= 5;
            if(checkouts[i]->front->items <= 0){
                remove_client(checkouts[i]);
            }
        }
    }
}

void remove_client(cashier_queue *queue){
    client *aux;
    if(!queue->front){
        printf("No clients on the queue\n");
        return;
    }
    aux = queue->front;
    queue->front = aux->next;
    free(aux);
    if(!queue->front){
        strncpy(queue->state,"FREE",BUFFER);
        queue->total_items = 0;
    }
}
