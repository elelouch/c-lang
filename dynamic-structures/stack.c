#include "dynstruct.h"
#include <stdio.h>
#include <stdlib.h>
void push(node **my_stack, int new_value){
    //The parameter stack here has other context
    node *pivot = (node *)malloc(sizeof(node));
    pivot -> value = new_value;
    pivot -> next = NULL;
    if(!(*my_stack)){
        *my_stack = pivot;
        return;
    }
    pivot -> next = *my_stack;
    (*my_stack) = pivot;
}

void traverse(node *my_stack){
    if(!(my_stack))
        return;
    printf("%d | ", my_stack->value);
    traverse(my_stack->next);
}

void pop(node **my_stack) {
    node *pivot;
    if(!(*my_stack)){
        printf("Empty Stack\n");
        return;
    }
    pivot = (*my_stack)->next;
    free(*my_stack);
    (*my_stack) = pivot;
}
