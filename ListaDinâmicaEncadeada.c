#include <stdio.h>
#include <stdlib.h>


typedef struct Celula{
	int valor;
	struct Celula *proximo;
}Celula;

typedef struct Lista{
	int qtde;
	Celula *primeiro;
}Lista;

void inserir(Lista *l, int valor){
	Celula *novo = malloc(sizeof(Celula));
	novo->valor = valor;
	novo->proximo = NULL;
	
	if(l->primeiro == NULL){
		l->primeiro = novo;
	}else{
		Celula *atual = l->primeiro;
		Celula *anterior = NULL;
		while(atual != NULL && atual->valor <= valor){
			anterior = atual;
			atual = atual->proximo;
		}
		if(anterior == NULL){
			novo->proximo = l->primeiro;
			l->primeiro = novo;
		}else{
			if(atual == NULL){
				anterior->proximo = novo;
			}else{
				novo->proximo = atual;
				anterior->proximo = novo;
			}
		}
	}
	l->qtde++;
}

void remover(Lista *l, int valor) {
  Celula *atual = l->primeiro;
  Celula *anterior = NULL;
  while(atual != NULL && atual->valor != valor){
    anterior = atual;
    atual = atual->proximo;
  }
  if(atual == NULL){
    return;
  }else{
    if(anterior == NULL){
      l->primeiro = atual->proximo;
      free(atual);
    }
    else{
      if(atual->proximo == NULL){
        anterior->proximo = NULL;
        free(atual);
      }
      else{
        anterior->proximo = atual->proximo;
        free(atual);
      }
    }
  }
}

Lista *inicializa_lista(){
	Lista *l = malloc(sizeof(Lista));
	l->primeiro = NULL;
	l->qtde = 0;
	return l;
}

void imprimir(Lista *l){
	Celula *atual = l->primeiro;
	while(atual != NULL){
		printf("%d ", atual->valor);
		atual = atual->proximo;
	}
	printf("\n");
}

int main(void) {
	Lista *l = inicializa_lista();
	inserir(l, 56);
	imprimir(l);
	inserir(l, 50);
	imprimir(l);
	inserir(l, 40);
	imprimir(l);
	inserir(l, 45);
	imprimir(l);
	inserir(l, 80);
	imprimir(l);
	remover(l, 40);
	imprimir(l);
	remover(l, 80);
	imprimir(l);
	remover(l, 50);
	imprimir(l);
	return 0;
}