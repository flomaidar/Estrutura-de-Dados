#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 9

typedef struct Heap {
  int valores[TAMANHO];
  int qtde;
}Heap;

int pai(int filho){  
  return (filho - 1) / 2;
} 

int ultimo_pai(Heap* h){ 
  return (h->qtde / 2) - 1;
} 

int filho_esq(int pai){
 return 2* pai + 1;
}

int filho_dir(int pai){
  return 2 * pai + 2;
}

void peneirar(Heap* h, int pai){
  int f_esq = filho_esq(pai);
  int f_dir = filho_dir(pai);
  int maior;
  int aux;
  
  if(f_esq < h->qtde && h->valores[f_esq] > h->valores[pai]){
    maior = f_esq;
   }else{
   maior = pai;
   }
   if(f_dir < h->qtde && h->valores[f_dir] > h->valores[maior]){
    maior = f_dir;}
   if(maior != pai){
    aux = h->valores[pai];
   h->valores[pai] = h->valores[maior];
   h->valores[maior] = aux;
   peneirar(h, maior);}}

void construir_heap(Heap* h){
 int i;
 for(i = ultimo_pai(h); i >= 0; i--){
  peneirar(h, i);
 }
}

void show(Heap* h){
 for(int i = 0; i < h->qtde; i++){
  printf("%d ", h->valores[i]);
 }
  printf("\n");
}

void inserir(Heap* h,int value){
  if(h->qtde<=TAMANHO){
    if(h->qtde==0){
      h->valores[0]=value;
      h->qtde++;
    }else{
      h->valores[h->qtde]= value;
      h->qtde++;
      for(int i =ultimo_pai(h);i>=0;i--){
        construir_heap(h);
        printf("");
      }  
    }
  }else return;     
}

void remover(Heap* h){
  printf("Remove: %d \n ",h->valores[0]);
  int aux = h->valores[h->qtde-1];
  h->valores[h->qtde-1] = h->valores[0];
  h->valores[0] = aux;
  h->qtde--;
  
  for(int i =ultimo_pai(h);i>=0;i--){
        construir_heap(h);
        printf("");
      } 
}
Heap * start_heap(){
  Heap* heap = malloc(sizeof(Heap));
  heap->qtde = 0;
  return heap;
}

int main() {
    //não alterar esta funçõe
	int valores_1[] = {99, 56, 90, 8, 43, 6, 7, 4, 6};
	int valores_2[] = {2, 5, 7, 2 ,1};
	int tamanho = sizeof(valores_2) / sizeof(int);
  Heap* h = malloc(sizeof(Heap));
  h->qtde = 0;
	for(int i = 0; i < TAMANHO; i++){
		inserir(h, valores_1[i]);
	}
	show(h);
	for(int i = 0; i < TAMANHO; i++){
		remover(h);
		show(h);
	}
	for(int i = 0; i < tamanho; i++){
		printf("Inserindo: %d\n", valores_2[i]);
		inserir(h, valores_2[i]);
	}
	show(h);
	for(int i = 0; i < tamanho; i++){
		remover(h);
	}
  return 0;
}