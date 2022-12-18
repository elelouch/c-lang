#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
} node;


void add_node(node**,int);
void delnode(node**,int);
void show(node*);


int main(){
    node *head = NULL;
    add_node(&head,3);
    add_node(&head,4);
    add_node(&head,5);
    add_node(&head,22);
    show(head);

    return 0;
}
void add_node(node **head, int new_value){
    node *new_node = malloc(sizeof(node));
    new_node->value = new_value;
    if(!*head){
        *head = new_node;
        new_node->next = new_node;
        return;
    }
    new_node->next = (*head)->next;
    (*head)->next = new_node;
    *head = new_node;
}

void show(node *head){
    node *aux = head->next;

    printf("%d | ", head->value);
    while(aux != head){
        printf("%d |", aux->value);
        aux = aux->next;
    }
}

void delnode(node **head, int del_value){
    node **aux;
    if(!*head)
        return;
    aux = &(*head)->next;

    while((*aux)->next->value != del_value) aux = &(*aux)->next;

    if((*aux)->next == *head){
        (*aux) = (*head)->next;
        free(*head);
        *head = *aux;
    }else{

    }
}
