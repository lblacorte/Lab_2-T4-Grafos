#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) {
        perror("Erro ao alocar memoria para a fila");
        exit(EXIT_FAILURE);
    }
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

void liberarFila(Fila* fila) {
    while (!filaVazia(fila)) {
        dequeue(fila);
    }
    free(fila);
}

int filaVazia(Fila* fila) {
    return fila->frente == NULL;
}

void enqueue(Fila* fila, int dado) {
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no da fila");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->frente = novoNo;
        fila->tras = novoNo;
    } else {
        fila->tras->proximo = novoNo;
        fila->tras = novoNo;
    }
}

int dequeue(Fila* fila) {
    if (filaVazia(fila)) {
        fprintf(stderr, "Erro: a fila esta vazia\n");
        exit(EXIT_FAILURE);
    }

    NoFila* primeiro = fila->frente;
    int dado = primeiro->dado;

    fila->frente = primeiro->proximo;
    free(primeiro);

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    return dado;
}