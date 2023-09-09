#include <stdio.h>
#include <stdlib.h>

typedef struct Particao Particao;
struct Particao {
    int inicio;
    int fim;
    Particao *proximo;
};

typedef struct Pilha Pilha;
struct Pilha {
    Particao *inicio;
};

void inicializarPilha(Pilha *pilha) {
    pilha->inicio = NULL;
};

void empilhar(Pilha *pilha, int inicio, int fim) {
    Particao *particao = malloc(sizeof(Particao));
    particao->inicio = inicio;
    particao->fim = fim;
    particao->proximo = NULL;

    if (pilha->inicio == NULL) {
        pilha->inicio = particao;
    } else {
        Particao *aux = pilha->inicio;

        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        aux->proximo = particao;
    }
};

Particao desempilhar(Pilha *pilha) {
    Particao *anterior, *remover, particao;
    
    remover = pilha->inicio;

    if (!remover->proximo) {
        particao = *remover;
        free(remover);
        pilha->inicio = NULL;
        return particao;
    } else {
        while (remover->proximo != NULL) {
            anterior = remover;
            remover = remover->proximo;
        }

        particao = *remover;
        free(remover);
        anterior->proximo = NULL;
        return particao;
    }
};

void trocar(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
};

int ordenar(int lista[], int inicio, int fim) {
    int pivot = lista[fim];
    int i = inicio;

    for (int j = inicio; j < fim-1; j++) {
        if (lista[j] <= pivot) {
            trocar(&lista[j], &lista[i]);
            i++;
        }
    }

    trocar(&lista[i], &lista[fim]);

    return i;
};

void quicksort(int lista[], int inicio, int fim) {
    Pilha pilha;
    inicializarPilha(&pilha);

    empilhar(&pilha, inicio, fim);

    while(pilha.inicio != NULL) {
        Particao particao = desempilhar(&pilha);

        if (particao.inicio < particao.fim) {
            int posicaoPivot = ordenar(lista, particao.inicio, particao.fim);

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