#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 32

enum choice{
CREATE_CATEGORY=1,
NEXT_CATEGORY=2,
PREVIOUS_CATEGORY = 3,
REMOVE_CATEGORY = 4,
LIST_CATEGORIES = 5,
ADD_OBJECT=6,
REMOVE_OBJECT=7,
LIST_OBJECTS=8
};

typedef struct OBJ_BLOCK{
    struct OBJ_BLOCK *previous;
    struct OBJ_BLOCK *next;
    char name[BUFFER];
}o_block
;

typedef struct CATEGORY_BLOCK{
    struct CATEGORY_BLOCK *previous;
    struct CATEGORY_BLOCK *next;
    char name[BUFFER];
    o_block *object_list;
}c_block;

//create category
//next category
//previous category
//list categories
//delete category (free nodes inside it)
//add object to category
//list objects of the current category
//delete from objects list using id

void create_category(c_block**,char*);//
void list_categories(c_block*);//
void next_category(c_block**);//
void previous_category(c_block**);//
void add_object(c_block*, char*);//
void list_objects(c_block*);//
void remove_object(c_block*,char*);//
void remove_category(c_block**);
void cleanstdin();

int main(){
    c_block *c_list = NULL;
    c_block *wc_list = NULL;
    unsigned int option_selected;
    char input[BUFFER];
    do{
        printf("\n1-create category\n2-next category\n3-previous category\n4-remove category\n5-list-categories\n6-add object\n7-remove object\n8-list objects\n");
        scanf("%d",&option_selected);
        cleanstdin();
        switch(option_selected){
            case CREATE_CATEGORY:
                printf("Inserte nombre de la categoria : \n");
                fgets(input,BUFFER,stdin);
                //cleanstdin();
                printf("%s\n", input);
                create_category(&c_list,input);
                if(!wc_list)
                    wc_list = c_list;
                break;
            case NEXT_CATEGORY:
                next_category(&wc_list);
                break;
            case PREVIOUS_CATEGORY:
                previous_category(&wc_list);
                break;
            case REMOVE_CATEGORY:
                remove_category(&wc_list);
                break;
            case LIST_CATEGORIES:
                list_categories(wc_list);
                break;
            case ADD_OBJECT:
                printf("Inserte nombre del nuevo objeto : \n");
                cleanstdin();
                fgets(input,BUFFER,stdin);
                add_object(wc_list,input);
                break;
            case REMOVE_OBJECT:
                printf("Inserte nombre del objeto a remover: \n");
                fgets(input,BUFFER,stdin);
                cleanstdin();
                remove_object(wc_list,input);
                break;
            case LIST_OBJECTS:
                list_objects(wc_list);
                break;
        }
    }while(option_selected != 0);

    return 0;
}

void create_category(c_block **c_list, char *c_name){
    c_block *new_category = malloc(sizeof(c_block));
    strncpy(new_category->name, c_name, BUFFER);
    new_category -> object_list = NULL;

    if(!*c_list){
        new_category -> next = new_category;
        new_category -> previous = new_category;
        *c_list = new_category;
        return;
    }
    new_category->next = (*c_list)->next;
    new_category->previous = (*c_list);
    (*c_list)->next->previous = new_category;
    (*c_list)->next = new_category;
    *c_list = new_category;
}

void list_categories(c_block *c_list){
    c_block *aux;

    if(!c_list){
        printf("No categories available\n");
        return;
    }
    aux = c_list;
    do{
        printf("> %s\n",aux->name);
        aux = aux->next;
    }while(aux != c_list);
}

void next_category(c_block **wc_list){
    if(!(*wc_list)->next || !*wc_list){
        printf("No categories available\n");
        return;
    }
    *wc_list = (*wc_list)->next;
}
void previous_category(c_block **wc_list){
    if(!(*wc_list)->previous || !*wc_list){
        printf("No categories available\n");
        return;
    }
    *wc_list = (*wc_list)->previous;
}

void add_object(c_block *wc_list, char *new_name){
    o_block **list_head = &wc_list->object_list;
    o_block *new_object = malloc(sizeof(o_block));
    strncpy(new_object->name, new_name,BUFFER);

    if(!*list_head){
        new_object->previous = new_object;
        new_object->next = new_object;
        *list_head = new_object;
        return;
    }

    new_object->next = (*list_head)->next;
    new_object->previous = *list_head;
    (*list_head)->next->previous = new_object;
    (*list_head)->next = new_object;
    (*list_head) = new_object;
}
void list_objects(c_block *wc_list){
    o_block *aux;
    if(!wc_list->object_list){
        printf("No objects present on the current category\n");
        return;
    }
    aux = wc_list->object_list;
    do{
        printf("%s | ",aux->name);
        aux = aux->next;
    }while(aux != wc_list->object_list);
}

void remove_object(c_block *wc_list,char *node_to_remove){
    o_block *aux;
    int flag;
    if(!wc_list){
        printf("No objects to remove\n");
        return;
    }
    aux = wc_list->object_list;
    do{
        aux = aux->next;
        flag = strcmp(node_to_remove,aux->next->name);
    }while(flag && aux->next != wc_list->object_list);

    if(!flag){
        if(aux->next == wc_list->object_list){
            wc_list->object_list = aux->next->next;
            if(wc_list->object_list == wc_list->object_list->next)
                wc_list->object_list = NULL;
        }
        aux->next = aux->next->next;
        aux = aux->next->previous;
        aux->next->previous = aux->previous;
        free(aux);
    }
}

// ARREGLAR ESTO PARA QUE LA WC QUEDE NULA DE NUEVO CUANDO BORRO EL ULTIMO OBJETO
void remove_category(c_block **wc_list){
    c_block *aux;
    if(!*wc_list){
        printf("No category available to delete\n");
        return;
    }
    aux = *wc_list;

    while(aux->object_list){
        remove_object(aux, aux->object_list->name);
    }

    do{
        aux = aux->next;
    }while(aux->next != *wc_list);

    aux->next = aux->next->next;
    aux->next->previous = aux;
    free(*wc_list);
    *wc_list = aux -> next;

    //if(aux->next == *wc_list){
    //    free(*wc_list);
    //    *wc_list = NULL;
    //}else{
    //    free(*wc_list);
    //    *wc_list = aux->next;
    //}

}

void cleanstdin(){
    char c;
    while((c = getchar()) != EOF && c != '\n'){}
}
