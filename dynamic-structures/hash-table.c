#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10
#define NAME_MAX 32

typedef struct person{
  char name[NAME_MAX];
  int id;
  struct person *left;
  struct person *right;
}person;

int hash_func(person  **);
person *create_person(char*);
void hash_table_insert(person **hash_table, char *);
void insert(person**,person*);
void delete(person**,person*);


int main(){
  person *hash_table[TABLE_SIZE] = {NULL};

  return 0;
}

person *create_person(char *name){
  person *new_person = (person *) malloc(sizeof(person));
  new_person->left = NULL;
  new_person->right = NULL;
  new_person->id = 0;
  strncpy(new_person->name,name,NAME_MAX);

  return new_person;
}

void cleanstdin(){
  char c;
  while(( c = getchar() ) != EOF && c != '\n');
}

void insert (person **root, person *person){
  if (!*root){
    (*root) = person;
    return;
  }

  if((*root)->id < person -> id){
    insert(&(*root)->right, person);
  }else if((*root)->id > person -> id){
    insert(&(*root)->right, person);
  }
}

int hash_func(person **evaluate_person){
  unsigned int hash_value = 0, id_cpy = 0;
  char name_pivot[NAME_MAX];
  int i, length;
  strncpy(name_pivot,(*evaluate_person)->name, NAME_MAX);
  length = strnlen(name_pivot, NAME_MAX);

  for(i = 0; i < length; i++){
    hash_value += name_pivot[i];
    id_cpy += name_pivot[i];
    hash_value = (hash_value * name_pivot[i] ) % TABLE_SIZE;
  }

  (*evaluate_person)->id = id_cpy;

  return hash_value;
}

hash_table_insert(person **root_tree, char *name){

}
