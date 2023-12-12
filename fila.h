#ifndef FILA_H
#define FILA_H

// Estrutura de um nó da fila
typedef struct NoFila {
    int dado;
    struct NoFila* proximo;
} NoFila;

// Estrutura da fila
typedef struct {
    NoFila* frente;
    NoFila* tras;
} Fila;

//Função para criar uma fila
Fila* criarFila();

//Função para liberar uma fila
void liberarFila(Fila* fila);

//Função para verificar se a fila está vazia
int filaVazia(Fila* fila);

//Função para enfileirar um elemento
void enqueue(Fila* fila, int dado);

//Função para desenfileirar um elemento
int dequeue(Fila* fila);

#endif