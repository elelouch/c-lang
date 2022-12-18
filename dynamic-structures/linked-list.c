#include "dynstruct.h"
#include <stdio.h>
#include <stdlib.h>

void list_add(node **head, int new_value){
    node *pivot = (node *)malloc(sizeof(node));
    pivot -> value = new_value;
    pivot -> next = NULL;
    if(!(*head)){
        *head = pivot;
        return;
    }
    pivot->next = *head;
    *head = pivot;
}
void remove_node(node **head, int remove_value){
    node *pivot = NULL;
    node *next_node = (*head)->next;
    node *next_next_node = next_node->next;

    if((*head)->value == remove_value){
        pivot = *head;
        *head = (*head)->next;
        free(pivot);
    }else if(next_node -> value == remove_value){
        (*head)->next = next_next_node;
        free(next_node);
    }else{
        remove_node(&(*head)->next, remove_value);
    }
}
