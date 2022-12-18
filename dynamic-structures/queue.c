#include "dynstruct.h"
#include <stdio.h>
#include <stdlib.h>
void enqueue(queue **my_queue,int new_value){
    //create pivot node
    node *pivot = (node *)malloc(sizeof(node));
    pivot -> value = new_value;
    pivot -> next = NULL;

    if((*my_queue)->back == NULL){
        //if there aren't any elements on the queue, point both front and back to the added node
        (*my_queue)->front = pivot;
        (*my_queue)->back = pivot;
    }else{
        /*else add pivot to the back, pointing the previous back node to the pivot and make
         * the new pivot the back of the queue*/
        (*my_queue)->back->next = pivot;
        (*my_queue)->back = pivot;
    }
}
void dequeue(queue **my_queue){
    node *pivot = NULL;
    if((*my_queue)->front == NULL){
        printf("Empty queue \n");
    }else{
        /*point the pivot to the next value of the front
         *free the node on the front, and make the pivot (next node of the freed node)
         *the new front*/
        pivot = (*my_queue)->front->next;
        free((*my_queue)->front);
        (*my_queue)->front = pivot;
    }
}
void traverse_aux(node *my_node){
    if(!( my_node )){
        printf("\n");
        return;
    }
    printf("%d | ",my_node->value);
    traverse_aux(my_node->next);
}
void traverse_queue(queue *my_queue){
    if(!(my_queue-> front)){
        printf("Empty queue\n");
        return;
    }
    traverse_aux(my_queue->front);
}
queue *create_queue(){
    queue *new_queue = (queue *)malloc(sizeof(queue));
    if(!(new_queue)){
        printf("Cannot allocate memory\n");
    }
    new_queue -> front = NULL;
    new_queue -> back = NULL;
    return new_queue;
}

int emptyQueue(queue *my_queue){
    if(my_queue->front == NULL)
        return 1;
    return 0;
}
