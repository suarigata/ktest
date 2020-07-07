/*
 ============================================================================
 Name        : Prompt.c
 Author      : Alex Lucchesi
 Version     : 1.0001
 Copyright   : The Unlicense
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _node{
  int value;
  struct _node *succ;
} typedef Node;


Node *list;

void listl();

void put(char *arg){
  int num;
  sscanf(arg, "%d", &num);

  Node *new = (Node*) calloc(1, sizeof(Node));
  new->succ = NULL;
  new->value = num;

  if(!list)
    list = new;
  else{
    Node *it = list;
    while(it->succ)
      it = it->succ;
    it->succ = new;
  }

  listl();
}

void get(char *arg){
  int num;
  sscanf(arg, "%d", &num);

  Node *it = list;
  while(it && --num)
    it = it->succ;
  
  printf("%d\n", it->value);
}

void listl(){
  Node *it = list;
  for(; it; it = it->succ){
    printf("%d ", it->value);
  }
  
  printf("\n");
}

void removel(char *arg){
  int num;
  sscanf(arg, "%d", &num);

  Node *rem;

  if(num == 1){
    rem = list;
    list = list->succ;
  }
  else{
    Node *it = list;
    num -= 2;
    while(it->succ && num--)
      it = it->succ;
    
    rem = it->succ;
    it->succ = it->succ->succ;
  }
  
  if(rem){
    printf("%d\n", rem->value);

    free(rem);
  }
}

// XXX Please checkout c075177074c145fa6561853a039cdb19b16025a3 to get the 90 min test.
void clear(){
  Node *it;
  
  while(list){
      it = list;
      list = list->succ;
      free(it);
  }
  list = NULL;
}

void first(){
  if(list)
    printf("%d\n", list->value);
}

void last(){
  Node *it = list;

  if(!it->succ)
    printf("%d\n", it->value);
  else{
    while(it->succ)
      it = it->succ;

    printf("%d\n", it->value);
  }
}

// XXX Please checkout c075177074c145fa6561853a039cdb19b16025a3 to get the 90 min test.
void sort(){
  Node *new = NULL;
  Node *old = list;
  
  while(old){
    if(!new){
      new = old;
      old = old->succ;
      new->succ = NULL;
    }
    else{
      Node *it = old;
      old = old->succ;

      if(it->value < new->value){
        it->succ = new;
        new = it;
      }
      else{
        Node *it2 = new;

        while(it2->succ){
          if(it->value < it2->succ->value){
            it->succ = it2->succ;
            it2->succ = it;
            it = NULL;
            break;
          }
          it2 = it2->succ;
        }

        if(it){
          it2->succ = it;
          it->succ = NULL;
        }
      }
    }
  }
  
  list = new;
  listl();
}


void process_cmd(char *input){

  char cmd[7];

  sscanf(input, "%s", cmd);
  
  if(strncmp(input, "put", 3) == 0) put(input + strlen(cmd));
  if(strncmp(input, "get", 3) == 0) get(input + strlen(cmd));
  if(strncmp(input, "list", 4) == 0) listl();
  if(strncmp(input, "remove", 6) == 0) removel(input + strlen(cmd));
  if(strncmp(input, "clear", 5) == 0) clear();
  if(strncmp(input, "first", 5) == 0) first();
  if(strncmp(input, "last", 4) == 0) last();
  if(strncmp(input, "sort", 4) == 0) sort();
}


// void print_entry(char *entry) {
// 	printf("You entered: %s\n", entry);
// }

int main(int argc, char *argv[]) {
	
  list = NULL;
  char input[201];

	while(1) {
		printf("prompt> ");
		if (fgets(input, 200, stdin) == NULL) {
			printf("An error ocurred.\n");
			break;
		}

		if (strncmp(input, "exit\n", 5) == 0) {
			printf("Leaving. Good bye.\n");
			break;
		}
    
		// print_entry(input);

    process_cmd(input);
	}

	return EXIT_SUCCESS;
}
