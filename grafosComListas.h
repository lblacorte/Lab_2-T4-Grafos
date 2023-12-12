#ifndef GRAFOSCOMLISTAS_H
#define GRAFOSCOMLISTAS_H

// Estrutura de um nó
typedef struct No {
    int destino;
    struct No* proximo;
} No;

// Estrutura do grafo
typedef struct Grafo {
    int numVertices;
    No** listaAdj;
} Grafo;

// Função para criar um nó
No* criarNo(int destino);

// Funções para criar o grafo
Grafo* criarGrafo(int numVertices);

// Função pra inserir uma aresta
void inserirAresta(Grafo* grafo, int origem, int destino);

// Função para remover uma aresta
void removerAresta(Grafo* grafo, int origem, int destino);

// Função para buscar uma aresta
int buscarAresta(Grafo* grafo, int origem, int destino);

// Função para imprimir o grafo
void imprimirGrafo(Grafo* grafo);

// Função para liberar o grafo
void liberarGrafo(Grafo* grafo);

// Função para percorrer o grafo em largura
void percorrerGrafoLargura(Grafo* grafo, int noInicial, int* preOrdem, int* posOrdem);

// Função auxiliar para percorrer o grafo em profundidade por percurso pré-ordem
void percorrerGrafoProfundidadePreOrdemAux(Grafo* grafo, int no, int* visitado);

// Função para percorrer o grafo em profundidade por percurso pré-ordem
void percorrerGrafoProfundidadePreOrdem(Grafo* grafo, int noInicial);

// Função auxiliar para percorrer o grafo em profundidade por percurso pós-ordem
void percorrerGrafoProfundidadePosOrdemAux(Grafo* grafo, int no, int* visitado);

// Função para percorrer o grafo em profundidade por percurso pós-ordem
void percorrerGrafoProfundidadePosOrdem(Grafo* grafo, int noInicial);

#endif