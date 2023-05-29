
#include <stdio.h>
#include <stdlib.h>
#define tamanho_da_fila 10

typedef struct Fila{
	int v[tamanho_da_fila];
	int tail;
	int head;
	int count;
}Fila;

int isFull(Fila *fila){
	if (fila->count == tamanho_da_fila)
    return 1;
  return 0;
}

void enqueue(Fila *fila, int valor){
	if(!isFull(fila)){
    fila->v[fila->tail % tamanho_da_fila] = valor;
    fila->tail++;
    fila->count++;
	}
}

int isEmpty(Fila *fila){
	if(fila->count == 0)
    return 1;
  return 0;
}

int dequeue(Fila *fila){
	int x = -1;
	if(!isEmpty(fila)){
		x = fila->v[fila->head % tamanho_da_fila];
    fila->head++;
    fila->count--;
		return x;
	}else{
		return 0;
	}
}

void mostra_fila(Fila *fila){
	for(int i = fila->head; i < fila->tail; i++)
    printf("%d ",fila->v[i%tamanho_da_fila]);
  printf("\n");
}

Fila *inicializa_fila(){
  Fila *fila = malloc(sizeof(Fila));
  fila->head = 0;
  fila->tail = 0;
  fila->count = 0;
	return fila;
}

int main(void) {
	Fila *fila = inicializa_fila();
	for(int i = 0; i < 100; i++){
		if(i % 3 == 0){
			dequeue(fila);
		}else{
			enqueue(fila, i);
		}
		mostra_fila(fila);
	}
  return 0;
}