// Flora Machado Aidar  11.120.270-1  
// Nicole De Camillis   11.120.454-1

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACIDADE 10

typedef struct {
  int valores[CAPACIDADE];
  char nome[CAPACIDADE][30];
  char dataRegistro[CAPACIDADE][30];
  char prazoConclusao[CAPACIDADE][30];
  int head; // q index comeca
  int tail; // ultimo index c elemento + 1
  int count;
} Fila;

typedef struct Celula {      //define estrutura da celula
  struct Celula *anterior;
  struct Celula *proximo;
  char nome[100];
  char departamento[100];
  char cargo[100];
  int posicao;
  Fila *tarefas;
} Celula;

typedef struct LDDE {        //define estrutura da lista
  Celula *primeiro;
  int qtde;
} LDDE;

LDDE *inicializa_lista() {
  LDDE *lista = malloc(sizeof(LDDE));
  lista->primeiro = NULL;
  lista->qtde = 0;
  return lista;
}
Fila *inicializa_fila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->head = 0;
  fila->tail = 0;
  fila->count = 0;
  return fila;
}

Celula *inicializa_celula(char nome[], char departamento[], char cargo[], int posicao, Fila tarefas) {
  Celula *celula = malloc(sizeof(Celula));
  celula->anterior = NULL;
  celula->proximo = NULL;
  strcpy(celula->nome, nome);
  strcpy(celula->departamento, departamento);
  strcpy(celula->cargo, cargo);
  Fila *tarefa = inicializa_fila();
  celula->tarefas = tarefa;
  celula->posicao = posicao;
  return celula;
}

int isFull(Fila *fila) {
  if (fila->count == CAPACIDADE) // cheia
    return 1;
  return 0;
}

int isEmpty(Fila *fila) {
  if (fila->count == 0) // vazia
    return 1;
  return 0;
}

Celula *buscar(LDDE *lista, char nome[]) {    //roda a lista e retorna a celula buscada
  Celula *atual = lista->primeiro;
  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    atual = atual->proximo;
  }
  return atual;
}

void enqueue(Fila *fila) {    //adiciona uma tarefa (ao ultimo lugar) da fila
  printf("Para inserir a tarefa, por favor\n");
  printf("  Insira o nome da tarefa:\n  ");
  char nomeTarefa[30];
  fgets(nomeTarefa, 30, stdin);
  printf("  Insira a data de registro:\n  ");
  char dataRegistro[30];
  fgets(dataRegistro, 30, stdin);
  printf("  Insira o prazo de conclusao:\n  ");
  char prazoConclusao[30];
  fgets(prazoConclusao, 30, stdin);  
  if (!isFull(fila)) {
    strcpy(fila->nome[fila->tail % CAPACIDADE], nomeTarefa);
    strcpy(fila->dataRegistro[fila->tail % CAPACIDADE], dataRegistro);
    strcpy(fila->prazoConclusao[fila->tail % CAPACIDADE], prazoConclusao);
    fila->tail = fila->tail % CAPACIDADE + 1;
    fila->count++;
  }
}

void dequeue(Fila *fila) {  //retira a tarefa mais antiga (primeira) da fila
  if (!isEmpty(fila)) {
    fila->head++;
    fila->count--;
  }
}

void buscarTarefas(LDDE *lista) {  //busca e printa tarefa e colaborador responsavel
  printf("Insira o nome da tarefa que deseja buscar:\n");
  char nomeTarefa[30];
  getchar();
  fgets(nomeTarefa, 30, stdin);
  Celula *atual = lista->primeiro;
  while (atual != NULL) {
    for (int i = atual->tarefas->head; i < atual->tarefas->tail; i++) {
      if (strcmp(atual->tarefas->nome[i], nomeTarefa) == 0) {
        printf("----------------------------------------------------------\n");
        printf("Colaborador responsável: %s", atual->nome);
        printf("\tTarefa: %s", atual->tarefas->nome[i]);
        printf("\tData de Registro: %s", atual->tarefas->dataRegistro[i]);
        printf("\tPrazo de Conclusão: %s", atual->tarefas->prazoConclusao[i]);
        printf("----------------------------------------------------------\n");
        return;
      }
    }
    atual = atual->proximo;
  }
  printf("Não existe nenhuma tarefa com este nome.\n");
}

void mostrarFila(LDDE *lista) {  //mostra todas as tarefas ou todas as tarefas de um
                                 //unico colaborador
  int opcao;
  char colaborador[30];
  printf("Digite o numero de acordo: \n1- Mostrar todas as tarefas de um "
         "colaborador\n2- Mostrar tarefas de todos os colaboradores\n");
  scanf("%d", &opcao);
  Celula *atual = lista->primeiro;
  switch (opcao) {
  case 1:
    printf("Digite o nome do colaborador que deseja visualizar as tarefas:\n");
    getchar();
    fgets(colaborador, 30, stdin);
    Celula *buscado = buscar(lista, colaborador);
    if (buscado == NULL) {
      printf("Não foi encontrado nenhum colaborador com esse nome\n");
    } else {
      printf("==========================================================\n");                  printf("Colaborador responsável: %s", buscado->nome);
      printf("------------------------- Tarefas ------------------------\n");
      for (int i = buscado->tarefas->head; i < buscado->tarefas->tail; i++) {
        printf("\tTarefa: %s", buscado->tarefas->nome[i]);
        printf("\tData de Registro: %s", buscado->tarefas->dataRegistro[i]);
        printf("\tPrazo de Conclusão: %s", buscado->tarefas->prazoConclusao[i]);
        printf("----------------------------------------------------------\n");
      }
    }
    break;
  case 2:
    printf("Mostrando todas as tarefas existentes:\n");
    while (atual != NULL) {
      printf("==========================================================\n");                  printf("Colaborador responsável: %s", atual->nome);
      printf("------------------------- Tarefas ------------------------\n");
      for (int i = atual->tarefas->head; i < atual->tarefas->tail; i++) {
        printf("\tTarefa: %s", atual->tarefas->nome[i]);
        printf("\tData de Registro: %s", atual->tarefas->dataRegistro[i]);
        printf("\tPrazo de Conclusão: %s", atual->tarefas->prazoConclusao[i]);
        printf("----------------------------------------------------------\n");
      }
      atual = atual->proximo;
    }
    break;
  default:
    printf("Opção invalida.\n");
  }
}

void inserir(LDDE *lista, char nome[], char departamento[], char cargo[], int posicao, Fila tarefas) { //insere colaborador na lista de acordo com a posicao determinada pelo usuario
  Celula *novo = inicializa_celula(nome, departamento, cargo, posicao, tarefas);
  if (lista->qtde == 0) {
    lista->primeiro = novo;
  } else {
    Celula *atual = lista->primeiro;
    Celula *anterior = NULL;
    while (atual != NULL && atual->posicao <= posicao) {
      anterior = atual;
      atual = atual->proximo;
    }
    if (anterior == NULL && atual != NULL) {
      novo->proximo = atual;
      atual->anterior = novo;
      lista->primeiro = novo;
    } else {
      if (atual == NULL && anterior != NULL) {
        anterior->proximo = novo;
        novo->anterior = anterior;
      } else {
        anterior->proximo = novo;
        novo->anterior = anterior;
        novo->proximo = atual;
        atual->anterior = novo;
      }
    }
  }
  lista->qtde++;
}

int remover(LDDE *lista, char nome[]) { //remove colaborador da lista
  Celula *buscado = buscar(lista, nome);
  if (buscado == NULL) {
    printf("Nenhum colaborador encontrado com este nome.\n");
    return 0;
  }
  Celula *anterior = buscado->anterior;
  Celula *proximo = buscado->proximo;
  if (anterior == NULL && proximo == NULL) {
    lista->primeiro = NULL;
  } else if (anterior == NULL) {
    lista->primeiro = proximo;
    proximo->anterior = NULL;
  } else if (proximo == NULL) {
    anterior->proximo = NULL;
  } else if (buscado->anterior != NULL && buscado->proximo != NULL) {
    buscado = buscado->proximo;
    anterior->proximo = buscado;
    buscado->anterior = anterior;
  }
  return 1;
  }

void imprimir(LDDE *lista) { //imprime toda a lista
  Celula *atual = lista->primeiro;
  while (atual != NULL) {
    printf("%s", atual->nome);
    printf("\t Departamento: %s", atual->departamento);
    printf("\t Cargo: %s", atual->cargo);
    atual = atual->proximo;
    printf("----------------------------------------------------------\n");
  }
  printf("\n");
}

void menu() {
  printf("==========================================================\n");
  printf("Digite o número de acordo com a ação que deseja executar:\n");
  printf("------ Ações com colaboradores: -------\n");
  printf("1- Inserir um colaborador\n");
  printf("2- Remover um colaborador\n");
  printf("3- Buscar um colaborador\n");
  printf("4- Mostrar todos os colaboradores\n");
  printf("--------- Ações com tarefas: ----------\n");
  printf("5- Inserir uma nova tarefa\n");
  printf("6- Remover uma tarefa existente\n");
  printf("7- Buscar uma tarefa\n");
  printf("8- Mostrar todas as tarefas\n");
  printf("==========================================================\n");
}

void callInsert(LDDE *lista) { //recebe os dados dos colaboradores para chamar a funcao inserir colaboradores
  printf("Insira o nome do colaborador:\n");
  char nome[30];
  getchar();
  fgets(nome, 30, stdin);
  printf("Insira o departamento do colaborador:\n");
  char departamento[30];
  fgets(departamento, 30, stdin);
  printf("Insira o cargo do colaborador:\n");
  char cargo[30];
  fgets(cargo, 30, stdin);
  printf("Insira a posição na agenda que deseja adicionar um colaborador:\n");
  if (lista->qtde != 0) {
    Celula *atual = lista->primeiro;
    printf("Não insira em posições já ocupadas:\n");
    while (atual != NULL) {
      printf("%d - %s", atual->posicao, atual->nome);
      atual = atual->proximo;
    }
  } else
    printf("\nA lista de colaboradores está vazia no momento, adicione em "
           "qualquer posição:\n");
  int posicao;
  scanf(" %d", &posicao);
  Fila tarefas;
  inserir(lista, nome, departamento, cargo, posicao, tarefas);
}

void callRemove(LDDE *lista) { //recebe o dado de qual colaborador remover e envia para a funcao de remoção
  printf("====================== Colaboradores =====================\n");
  imprimir(lista);
  printf("==========================================================\n");
  printf("Insira o nome do colaborador a ser removido\n");
  char nome[30];
  getchar();
  fgets(nome, 30, stdin);
  int success = remover(lista, nome);
  if(success)
    printf("Colaborador removido com sucesso.\n");
}

void callBuscar(LDDE *lista) { //recebe o dado de qual colaborador quer buscar e envia para a funcao de buscar colaboradores
  printf("Insira o nome do colaborador a ser buscado:\n");
  char nome[30];
  getchar();
  fgets(nome, 30, stdin);
  Celula *buscado = buscar(lista, nome);
  if (buscado == NULL) {
    printf("Não foi encontrado nenhum colaborador com esse nome\n");
  } else {
    printf("---------------------- Colaborador -----------------------\n");
    printf("%s", buscado->nome);
    printf("\t Departamento: %s", buscado->departamento);
    printf("\t Cargo: %s", buscado->cargo);
    printf("----------------------------------------------------------\n");
  }
}

void callEnqueue(LDDE *lista) { //recebe o dado de qual colaborador receberá a tarefa e envia para a funcao de adicionar na fila de tarefas
  printf("Insira o nome do colaborador que deseja atribuir a tarefa:\n");
  char nome[30];
  getchar();
  fgets(nome, 30, stdin);  
  Celula *buscado = buscar(lista, nome);
  printf("----------------------------------------------------------\n");
  if (buscado == NULL) {
    printf("Não foi encontrado nenhum colaborador com esse nome.\n");
  } else {
    enqueue(buscado->tarefas);
    printf("----------------------------------------------------------\n");
    printf("Tarefa adicionada com sucesso!");
  }
}

void callDequeue(LDDE *lista) { //recebe o dado de qual colaborador excluirá a tarefa e envia para a funcao de excluir na fila de tarefas
  printf("Insira o nome do colaborador que deseja excluir a tarefa\n");
  char nome[30];
  getchar();
  fgets(nome, 30, stdin);
  Celula *buscado = buscar(lista, nome);
  printf("----------------------------------------------------------\n");
  if (buscado == NULL) {
    printf("Não foi encontrado nenhum colaborador com esse nome\n");
  } else {
    dequeue(buscado->tarefas);
    printf("A tarefa mais antiga do colaborador %s foi excluida com sucesso.\n",nome);
    Celula *buscado2 = buscar(lista, nome);
    if(buscado == NULL)
      printf("Este colaborador não possuí mais nenhuma tarefa.");
    else{
      printf("O colaborador ainda possuí as seguintes tarefas:\n");
      printf("------------------------- Tarefas ------------------------\n");
      for (int i = buscado->tarefas->head; i < buscado->tarefas->tail; i++) {
        printf("\tTarefa: %s", buscado->tarefas->nome[i]);
        printf("\tData de Registro: %s", buscado->tarefas->dataRegistro[i]);
        printf("\tPrazo de Conclusão: %s", buscado->tarefas->prazoConclusao[i]);
        printf("----------------------------------------------------------\n");
      }
    }
  }
}

int main(void) {
  LDDE *lista = inicializa_lista();
  Fila *fila = inicializa_fila();
  while (1) {
    sleep(1);
    menu();
    int acao;
    scanf(" %d", &acao);
    switch (acao) {
    case 1:
      callInsert(lista);
      break;
    case 2:
      callRemove(lista);
      break;
    case 3:
      callBuscar(lista);
      break;
    case 4:
      imprimir(lista);
      break;
    case 5:
      callEnqueue(lista);
      break;
    case 6:
      callDequeue(lista);
      break;
    case 7:
      buscarTarefas(lista);
      break;
    case 8:
      mostrarFila(lista);
      break;
    default:
      printf("Error. Tente novamente\n");
    }
  }
  return 0;
}