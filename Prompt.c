/*
 ============================================================================
 Name        : Prompt.c
 Author      : Alex Lucchesi
 Version     : 1.0000
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

void clear(){
  Node *it = list;
  list = NULL;
  
  it = NULL; // TODO
  // TODO free list
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
