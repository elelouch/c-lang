#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 20

typedef struct child{
    char name[MAX_NAME];
    int age;
    struct child *next_child;
}child;


void add_in_circle(child**,char *,int);
void delete_in_circle(char*, child**,child**);
void add_in_lake(child**, child*);
void remove_from_lake(child**, child**,char);
void show_circle(child*);
void show_lake(child*);


int main(){
    child *circle = NULL;
    child *lake = NULL;
    return 0;
}

void add_in_circle(child **circle_head, char *new_name, int new_age){
    child *new_child = (child*)malloc(sizeof(child));
    new_child->age = new_age;
    strncpy(new_child->name,new_name,MAX_NAME);

    if(!*circle_head){
        new_child->next_child = new_child;
        *circle_head = new_child;
        return;
    }

    new_child->next_child = (*circle_head)->next_child;
    (*circle_head)->next_child = new_child;
    *circle_head = new_child;
}

void show_circle(child *circle_head){
    child *aux = circle_head->next_child;
    printf("Kids in the circle: ");
    while(aux != circle_head){
        printf("%s | ", aux->name);
        aux = aux->next_child;
    }
    printf("%s\n",aux->name);
}

void delete_in_circle(char *remove_child, child **circle_head, child **lake){
    child *aux = NULL ; // loop pivot
    child *aux2 = NULL; // pivot

    if(!*circle_head){
        printf("No one is playing :c \n");
        return;
    }

    aux = (*circle_head)->next_child;

    while(strcmp(aux->next_child->name,remove_child))
        aux = aux->next_child;

    if(aux->next_child == *circle_head){
        aux->next_child = aux->next_child->next_child;
        (*circle_head)->next_child = NULL;
        aux2 = *circle_head;
        *circle_head = aux;
        add_in_lake(lake,aux2);
    }else{
        aux2 = aux->next_child;
        aux->next_child = aux->next_child->next_child;
        aux2->next_child=NULL;
        add_in_lake(lake, aux2);
    }
}

void add_in_lake(child **lake, child *removed_child){
    if(!*lake) {
        *lake = removed_child;
        return;
    }
    removed_child->next_child = *lake;
    *lake = removed_child;
}

void show_lake(child *head_child){
    if(!head_child){
        printf("\n");
        return;
    }
    printf("%s\n",head_child->name);
    show_lake(head_child->next_child);
}

void remove_from_lake(child **lake, child **circle_head, char keep_playing){
    char remove_name[MAX_NAME];
    int remove_age;
    child *aux;

    strncpy(remove_name,(*lake)->name,MAX_NAME);
    remove_age = (*lake)->age;
    aux = *lake;
    *lake = (*lake)->next_child;
    free(aux);
    if(keep_playing == 'y'){
        add_in_circle(circle_head,remove_name,remove_age);
    }
}
