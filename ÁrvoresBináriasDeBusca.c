#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice{
	int valor;
	struct Vertice* esq;
	struct Vertice* dir;
	struct Vertice* pai;
} Vertice;

typedef struct Arvore{
	Vertice* raiz;
	int qtde;
} Arvore;

void imprimeEstrutura(Vertice* raiz){
	if (raiz != NULL){
      printf(" %d( ",  raiz->valor);
      imprimeEstrutura(raiz->esq);
      imprimeEstrutura(raiz->dir);
      printf(" )");
    }
}

void inserir(Arvore* arvore, int valor){
	Vertice* novo = malloc(sizeof(Vertice));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;
	novo->valor = valor;

	Vertice* anterior = NULL;
	Vertice* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(valor <= anterior->valor){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}

	novo->pai = anterior;
	if(anterior != NULL){
		if(valor <= anterior->valor){
			anterior->esq = novo;
		}else{
			anterior->dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
	arvore->qtde++;
}

int remover_vertice(Arvore* arvore, Vertice* vertice){
  int aux;
  int filhos = 0;
  if (vertice->esq != NULL) 
    filhos++; 
  if (vertice->dir != NULL) 
    filhos++;
  if (filhos == 1) {
    Vertice *troca;
    if (vertice->dir != NULL) {
      troca = vertice->dir;
      while (troca->esq != NULL) 
       troca = troca->esq;
    } else {
      troca = vertice->esq;
      while (troca->dir != NULL)
        troca = troca->dir;
    }
    aux = vertice->valor;
    vertice->valor = troca->valor;
    troca->valor = aux;
    remover_vertice(arvore, troca);
  }

  if (filhos == 0) {
    if (vertice->pai != NULL) {
      if (vertice->pai->dir == vertice)
        vertice->pai->dir = NULL;
      else 
        vertice->pai->esq = NULL;
    } else
      arvore->raiz = NULL;
    arvore->qtde--;
    free(vertice);
  }

  if (filhos == 2){
    Vertice *troca = vertice->esq;
    while (troca->dir != NULL)
      troca = troca->dir;
    aux = vertice->valor;
    vertice->valor = troca->valor;
    troca->valor = aux;
    remover_vertice(arvore, troca);
  }
  return 0;
}

int buscar_valor(Arvore* arvore, int valor){
	Vertice* atual = arvore->raiz;
	while(atual != NULL){
		if(valor < atual->valor){
			atual = atual->esq;
		}else{
			if(valor > atual->valor){
				atual = atual->dir;
			}else{
				return remover_vertice(arvore, atual);
			}
		}
	}
	return 0;
}

int main(void) {
	int dados[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
    Arvore* arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	for(int i = 0; i < 10; i++){
		inserir(arvore, dados[i]);
		imprimeEstrutura(arvore->raiz);
		printf("\n");
	}
	
	for(int i = 0; i < 10; i++){
		buscar_valor(arvore, dados[i]);
		imprimeEstrutura(arvore->raiz);
		printf("\n");
	}
		
  return 0;
}