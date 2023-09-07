#include <stdio.h>
#include <stdlib.h>

typedef struct Partition Partition;
struct Partition {
    int inicio;
    int fim;
    Partition *proximo;
};

typedef struct Pilha Pilha;
struct Pilha {
    Partition *inicio;
};

void inicializarPilha(Pilha *pilha) {
    pilha->inicio = NULL;
};

void empilhar(Pilha *pilha, int inicio, int fim) {
    Partition *partition = malloc(sizeof(Partition));
    partition->inicio = inicio;
    partition->fim = fim;
    partition->proximo = NULL;

    if (pilha->inicio == NULL) {
        pilha->inicio = partition;
    } else {
        Partition *aux = pilha->inicio;

        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = partition;
    }
};

Partition desempilhar(Pilha *pilha) {
    Partition *anterior, *remover, partition;
    
    remover = pilha->inicio;

    if (!remover->proximo) {
        partition = *remover;
        free(remover);
        pilha->inicio = NULL;
        return partition;
    } else {
        while (remover->proximo != NULL) {
            anterior = remover;
            remover = remover->proximo;
        }

        partition = *remover;
        free(remover);
        anterior->proximo = NULL;
        return partition;
    }
};

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
};

int partition(int lista[], int inicio, int fim) {
    int pivot = lista[fim];
    int i = inicio;

    for (int j = inicio; j < fim-1; j++) {
        if (lista[j] <= pivot) {
            swap(&lista[j], &lista[i]);
            i++;
        }
    }

    swap(&lista[i], &lista[fim]);

    return i;
};

void quicksort(int lista[], int inicio, int fim) {
    Pilha pilha;
    inicializarPilha(&pilha);

    empilhar(&pilha, inicio, fim);

    while(pilha.inicio != NULL) {
        Partition particao = desempilhar(&pilha);

        if (particao.inicio < particao.fim) {
            int posicaoPivot = partition(lista, particao.inicio, particao.fim);

            empilhar(&pilha, particao.inicio, posicaoPivot-1);
            empilhar(&pilha, posicaoPivot+1, particao.fim);
        }
    }
};

int main() {
    int vetor[] = {4, 7, 2, 6, 4, 1, 8, 3};
    int indice_inicio = 0;
    int indice_fim = 7;

    printf("Array antes da ordenação:\n");
    for (int i = 0; i <= indice_fim; i++) {
        printf("%d ", vetor[i]);
    }

    quicksort(vetor, indice_inicio, indice_fim);

    printf("\nArray após a ordenação:\n");
    for (int i = 0; i <= indice_fim; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
};