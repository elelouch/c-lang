#include "dynstruct.h"
#include <stdio.h>
#include <stdlib.h>

void add_tree_node(tree_node **root, int new_value){
    tree_node *pivot = (tree_node *)malloc(sizeof(tree_node));
    if(!pivot){
        printf("Couldn't add the new node\n");
        return;
    }
    pivot -> value = new_value;
    pivot -> left = NULL;
    pivot -> right = NULL;

    if(!(*root)){
        *root = pivot;
        return;
    }
    free(pivot);
    if((*root)->value > new_value){
        add_tree_node(&(*root)->left, new_value);
    }else if((*root)->value < new_value){
        add_tree_node(&(*root)->right,new_value);
    }
}

void inorder(tree_node *root){
    if(!(root)){
        return;
    }
    inorder(root->left);
    printf("%d | ",root->value);
    inorder(root->right);
}

void preorder(tree_node *root){
    if(!(root))
        return;

    printf("%d | ",root->value);
    preorder(root->left);
    preorder(root->right);
}

void postorder(tree_node *root){
    if(!root){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d | ",root->value);
}
tree_node *highest_minimum(tree_node **root){
    tree_node *pivot;
    if((*root)->right == NULL){
        pivot = *root;
        *root = (*root)->left;
        pivot -> left = NULL;
        return pivot;
    }
    return highest_minimum(&(*root)->right);
}
void remove_tree_node(tree_node **root, int remove_value){
    tree_node *tree_node_replace;
    if((*root)->value > remove_value){
        remove_tree_node(&(*root)->left,remove_value);
    }else if((*root)->value < remove_value){
        remove_tree_node(&(*root)->right,remove_value);
    }else{
        tree_node_replace = highest_minimum(&(*root)->left);
        tree_node_replace->left = (*root)->left;
        tree_node_replace->right = (*root)->right;
        free(*root);
        *root = tree_node_replace;
    }
}
