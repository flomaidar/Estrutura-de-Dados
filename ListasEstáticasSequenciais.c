#include <stdio.h>

#define capacidade 10

int posicao_de_insercao(int lista[], int valor, int n) {
  int idx = 0;
  if (n == capacidade)
    return -1;
  while (valor > lista[idx] && idx < n)
    idx++;
  return idx;
}

int inserir(int lista[], int valor, int n) {
  int i;
  if (n == 0) {
    lista[n] = valor;
    return 1;
  }
  int idx = posicao_de_insercao(lista, valor, n);
  if (idx >= 0) {
    for (i = n; i >= idx; i--)
      lista[i] = lista[i - 1];
    lista[idx] = valor;
    return 1;
  }
  return 0;
}

int remover(int lista[], int idx, int n) {
    int valor = lista[idx];
  for(int i = idx; i<n-1; i++){
      lista[i] = lista[i+1];
  }
  return valor;
}

int buscar(int lista[], int valor, int n) {
  int idx,x;
  for(int i = 0; i<n; i++){
      if(lista[i] == valor){
      idx = i;
      x = remover(lista, idx, n);
      return x;
    }
  }
  return -1;
}

void imprimir(int lista[], int n) {
  for(int i = 0; i < n; i++){
   printf("%d ", lista[i]);
  }
  printf("\n");
}

int main(void) {
  int valores[capacidade];
  int n = 0, x, i;
  int lista[capacidade];
	for(i = 0; i < capacidade; i++){
		scanf("%d", &valores[i]);
	}
  printf("===== INSERIR =====\n");
  for (i = 0; i < capacidade; i++) {
    printf("Inserir %d\n", valores[i]);
    x = inserir(lista, valores[i], n);
    if (x > 0)
      n++;
    imprimir(lista, n);
  }
  x = -1;
  printf("===== REMOVER =====\n");
  for (i = 0; i < capacidade; i++) {
    printf("Remover %d\n", valores[i]);
    x = buscar(lista, valores[i], n);
    if (x >= 0)
      n--;
    imprimir(lista, n);
  }
  return 0;
}