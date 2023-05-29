#include <stdio.h>

void imprime(int v[], int tamanho){
  for(int i = 0; i < tamanho; i++)
    printf("%d ", v[i]);
  printf("\n");
}

void bubble_sort(int v[], int tamanho){
  for(int i=0; i < tamanho; i++){
    for(int j=tamanho-1; j > i; j--){
      if(v[j] < v[j-1]){
        int aux = v[j];
        v[j] = v[j-1];
        v[j-1] = aux;
      }
    }
  }
}

void insertion_sort(int v[], int tamanho){
  for(int j=1; j < tamanho; j++){
    int chave = v[j];
    int i = j-1;
    while(i>=0 && v[i]>chave){
      v[i+1] = v[i];
      i = i-1;
    }
    v[i+1] = chave;
  }
}

void selection_sort(int v[], int tamanho){
  for(int i=0; i < tamanho-1; i++){
  int min = i;
    for(int j=i+1; j < tamanho; j++){
      if (v[j] < v[min])
        min = j;
      }
    if (v[i] != v[min]){
      int aux = v[i];
      v[i] = v[min];
      v[min] = aux;
      }
  }
}

int main(void) {
  int v[] = {8, 4, 2, 7, 1, 3, 9, 6, 0, 5};
  int tamanho = sizeof(v)/sizeof(int);

  imprime(v,tamanho);
  printf("\nDigite o número da forma que deseja ordenar o vetor:");
  printf("\n\n1. Bubble Sort\n2. Insertion Sort\n3. Selection Sort\n\n");
  int resp;
  scanf("%d", &resp);
  switch (resp){
    case 1:
      bubble_sort(v,tamanho);
    break;
    case 2:
      insertion_sort(v,tamanho);
    break;
    case 3:
      selection_sort(v,tamanho);
    break;
    }
    imprime(v,tamanho);
  return 0;
}