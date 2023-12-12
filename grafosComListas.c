#include "grafosComListas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

No* criarNo(int destino) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro ao alocar memoria para o no");
        exit(EXIT_FAILURE);
    }
    novoNo->destino = destino;
    novoNo->proximo = NULL;
    return novoNo;
}

Grafo* criarGrafo(int numVertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        perror("Erro ao alocar memoria para o grafo");
        exit(EXIT_FAILURE);
    }

    grafo->numVertices = numVertices;

    // Alocar memória para a lista de adjacências
    grafo->listaAdj = (No**)malloc(numVertices * sizeof(No*));
    if (grafo->listaAdj == NULL) {
        perror("Erro ao alocar memoria para a lista de adjacencias");
        exit(EXIT_FAILURE);
    }

    // Inicializar a lista de adjacências de cada vértice
    for (int i = 0; i < numVertices; i++) {
        grafo->listaAdj[i] = NULL;
    }

    return grafo;
}

void inserirAresta(Grafo* grafo, int origem, int destino) {
    // Verifique se os vértices estão dentro dos limites
    if (origem < 0 || origem >= grafo->numVertices || destino < 0 || destino >= grafo->numVertices) {
        printf("\n\n *****ERRO: Os vertices devem estar dentro dos limites de 0 a %d.\n", grafo->numVertices - 1);
        return;
    }

    // Verifique se a aresta já existe
    if (buscarAresta(grafo, origem, destino) == 1) {
        printf("\n\n *****ERRO: A aresta de %d para %d ja existe.\n\n", origem, destino);
        return;
    }

    No* novoNo = criarNo(destino);
    No** atual = &(grafo->listaAdj[origem]);

    // Encontre o local de inserção
    while (*atual != NULL && (*atual)->destino < destino) {
        atual = &((*atual)->proximo);
    }

    // Insira o novo nó
    novoNo->proximo = *atual;
    *atual = novoNo;

    printf("\n\n *****A aresta de %d para %d foi inserida.\n\n", origem, destino);
}

void removerAresta(Grafo* grafo, int origem, int destino) {
    int existe = buscarAresta(grafo, origem, destino);

    if (existe == 0) {
        printf("\n\n *****ERRO: A aresta de %d para %d nao existe.\n\n", origem, destino);
        return;
    }

    No* atual = grafo->listaAdj[origem];
    No* anterior = NULL;

    while (atual != NULL && atual->destino != destino) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->proximo = atual->proximo;
        } else {
            grafo->listaAdj[origem] = atual->proximo;
        }
        free(atual);
    }

    printf("\n\n *****A aresta de %d para %d foi removida.\n\n", origem, destino);
}

int buscarAresta(Grafo* grafo, int origem, int destino) {
    No* atual = grafo->listaAdj[origem];

    while (atual != NULL) {
        if (atual->destino == destino) {
            return 1;
        }
        atual = atual->proximo;
    }

    return 0;
}

void imprimirGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numVertices; ++i) {
        printf("Vertice %d:", i);
        No* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->proximo;
        }
        printf(" -> NULL\n");
    }
}

void liberarGrafo(Grafo* grafo) {
    if (grafo != NULL) {
        for (int i = 0; i < grafo->numVertices; ++i) {
            No* atual = grafo->listaAdj[i];
            while (atual != NULL) {
                No* proximo = atual->proximo;
                free(atual);
                atual = proximo;
            }
        }
        free(grafo->listaAdj);
        free(grafo);
    }
}

void percorrerGrafoLargura(Grafo* grafo, int noInicial, int* preOrdem, int* posOrdem) {
    int* visitado = (int*)malloc(grafo->numVertices * sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memoria para o vetor de visitados");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < grafo->numVertices; ++i) {
        visitado[i] = 0;
        preOrdem[i] = -1; // Marcador para indicar que o nó não foi visitado
        posOrdem[i] = -1; // Marcador para indicar que o nó não foi visitado
    }

    Fila* fila = criarFila();
    enqueue(fila, noInicial);
    visitado[noInicial] = 1;

    int idxPreOrdem = 0;
    int idxPosOrdem = 0;

    while (!filaVazia(fila)) {
        int atual = dequeue(fila);
        preOrdem[idxPreOrdem++] = atual;

        No* adjacente = grafo->listaAdj[atual];
        while (adjacente != NULL) {
            int destino = adjacente->destino;
            if (!visitado[destino]) {
                enqueue(fila, destino);
                visitado[destino] = 1;
            }
            adjacente = adjacente->proximo;
        }

        posOrdem[idxPosOrdem++] = atual;
    }

    free(visitado);
    liberarFila(fila);
}

void percorrerGrafoProfundidadePreOrdemAux(Grafo* grafo, int no, int* visitado) {
    visitado[no] = 1;
    printf("%d", no);
    No* adjacente = grafo->listaAdj[no];
    while (adjacente != NULL) {
        int destino = adjacente->destino;
        if (!visitado[destino]) {
            printf(", ");
            percorrerGrafoProfundidadePreOrdemAux(grafo, destino, visitado);
        }
        adjacente = adjacente->proximo;
    }
}

void percorrerGrafoProfundidadePreOrdem(Grafo* grafo, int noInicial) {
    int* visitado = (int*)malloc(grafo->numVertices * sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memoria para o vetor de visitados");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < grafo->numVertices; ++i) {
        visitado[i] = 0;
    }

    percorrerGrafoProfundidadePreOrdemAux(grafo, noInicial, visitado);

    printf("\n");
    free(visitado);
}

void percorrerGrafoProfundidadePosOrdemAux(Grafo* grafo, int no, int* visitado) {
    visitado[no] = 1;

    No* adjacente = grafo->listaAdj[no];
    while (adjacente != NULL) {
        int destino = adjacente->destino;
        if (!visitado[destino]) {
            percorrerGrafoProfundidadePosOrdemAux(grafo, destino, visitado);
        }
        adjacente = adjacente->proximo;
    }

    printf("%d", no);
    if (no != 0) {
        printf(", ");
    }
}

void percorrerGrafoProfundidadePosOrdem(Grafo* grafo, int noInicial) {
    int* visitado = (int*)malloc(grafo->numVertices * sizeof(int));
    if (visitado == NULL) {
        perror("Erro ao alocar memoria para o vetor de visitados");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < grafo->numVertices; ++i) {
        visitado[i] = 0;
    }

    percorrerGrafoProfundidadePosOrdemAux(grafo, noInicial, visitado);

    printf("\n");
    free(visitado);
}