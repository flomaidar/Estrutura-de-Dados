#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Celula{
	struct Celula *proximo;
	int valor;
}Celula;

typedef struct Pilha{
  Celula *topo;
}Pilha;

Pilha* start_stack(){
Pilha *pilha = malloc(sizeof(Pilha));
	pilha->topo = NULL;
  return pilha;
}

Celula* start_cell(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->proximo = NULL;
  celula->valor = valor;
	return celula;
}

int isEmpty(Pilha* pilha){
	if (pilha->topo == NULL)
    return TRUE;
  else
    return FALSE;
}

void show_stack(Pilha* pilha){
  Celula *atual = pilha->topo;
  printf("Topo da pilha -> ");
  while(atual!= NULL){
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
  printf("<- Fim da pilha\n");
}

void push(Pilha* pilha, int value){
  Celula *celula = start_cell(value);
  if (!isEmpty(pilha))
    celula->proximo = pilha->topo;
  pilha->topo = celula;
}

int pop(Pilha* pilha){
  if (!isEmpty(pilha)){
    int value = pilha->topo->valor;
    pilha->topo = pilha->topo->proximo;
    return value;
	}
  else
    return -1;
}

int main(void) {
	Pilha* pilha = start_stack();
  for(int i = 0; i < 10; i++){
		printf("Empilhando: %d\n", i);
		push(pilha, i);
	}
	show_stack(pilha);
	for(int i = 0; i <= 10; i++){
		printf("Desempilhando: %d\n", pop(pilha));
		show_stack(pilha);
	}
	
  return 0;
}