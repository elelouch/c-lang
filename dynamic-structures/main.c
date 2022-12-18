#include <stdlib.h>
#include <stdio.h>
#include "dynstruct.h"
#define MAGIC_NUM 13

int main(){
    queue *new_queue = create_queue();
    tree_node *tree = NULL;
    node *stack = NULL;
    node *list = NULL;
    int i;

    // Trying own library functions
    int nodes_to_add[MAGIC_NUM]= {123,41,21,24,2,12,67,7456,10,13,21,0,-1};

    for(i = 0; i < MAGIC_NUM; i++){
        enqueue(&new_queue, nodes_to_add[i]);
        push(&stack, nodes_to_add[i]);
        add_tree_node(&tree,nodes_to_add[i]);
        list_add(&list,nodes_to_add[i]);
    }
    traverse(list);
    printf("\n");
    traverse(stack);
    printf("\n");
    inorder(tree);
    printf("\n");
    traverse_queue(new_queue);
    printf("\n");


    return 0;
}
