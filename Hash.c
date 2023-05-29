#include <stdio.h>
#include <stdlib.h>

#define tam_hash 7

typedef struct Celula {
  int valor;
  struct Celula *proximo;
} Celula;

typedef struct {
  Celula *inicio;
} Lista;

typedef struct {
  Lista *table[tam_hash];
} Hash;

Hash *start_hash() {
  Hash *hash = malloc(sizeof(Hash));
  for (int i = 0; i < tam_hash; i++) {
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    hash->table[i] = lista;
  }
  return hash;
}

void inserir_hash(Hash *hash, int valor) {
  Celula *novo = malloc(sizeof(Celula));
  novo->proximo = NULL;
  novo->valor = valor;
  if (hash->table[valor % tam_hash]->inicio == NULL)
    hash->table[valor % tam_hash]->inicio = novo;
  else {
    Celula *aux = hash->table[valor % tam_hash]->inicio;
    hash->table[valor % tam_hash]->inicio = novo;
    novo->proximo = aux;
  }
}

void remover_hash(Hash *hash, int valor) {
  Celula *atual = hash->table[valor % tam_hash]->inicio;
  Celula *anterior = NULL;
  while(atual != NULL && atual->valor != valor){
    anterior = atual;
    atual = atual->proximo;
  }
  if(atual == NULL){
    return;
  }else{
    if(anterior == NULL){
      hash->table[valor % tam_hash]->inicio = atual->proximo;
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

void imprimir(Hash *hash) {
  printf("---------------------\n");
  for (int i = 0; i<tam_hash; i++){
    printf("%d -> ",i);
    Celula *atual = hash->table[i]->inicio;
	   while(atual != NULL){
		    printf("%d ", atual->valor);
		    atual = atual->proximo;
  	}
    printf("\n");
  }
  printf("---------------------\n");
}

int main(void) {
  // não alterar essa função
  int valores[] = {190, 322, 172, 89, 13, 4,  769, 61,
                   15,  76,  97,  28, 80, 76, 88};
  int tam = sizeof(valores) / sizeof(int);
  Hash *hash = start_hash();
  for (int i = 0; i < tam; i++) {
    inserir_hash(hash, valores[i]);
  }
  imprimir(hash);
  for (int i = 5; i < 10; i++) {
    remover_hash(hash, valores[i]);
  }
  imprimir(hash);
  for (int i = 3; i < 7; i++) {
    inserir_hash(hash, valores[i]);
  }
  imprimir(hash);
  for (int i = 10; i < 15; i++) {
    remover_hash(hash, valores[i]);
  }
  imprimir(hash);
  return 0;
}