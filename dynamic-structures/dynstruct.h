#ifndef DYNSTRUCT_H_
#define DYNSTRUCT_H_
typedef struct node{
    int value;
    struct node *next;
}node;
typedef struct queue{
    struct node *front;
    struct node *back;
} queue;
typedef struct tree_node{
    int value;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

//Tree functions
void add_tree_node(tree_node **,int);
void inorder(tree_node*);
void preorder(tree_node*);
void postorder(tree_node*);
void remove_tree_node(tree_node **,int);

//List functions
void list_add(node **,int value);
void remove_node(node**, int);
//void traverse_list(node*);

//Queue functions

queue *create_queue();
void enqueue(queue**,int);
void dequeue(queue**);
int emptyQueue(queue*);
//void traverse_aux(node*);
void traverse_queue(queue*);

//Stack functions
void charge();
void pop(node**);
void push(node**,int);
void traverse(node*);

#endif // DYNSTRUCT_H_
