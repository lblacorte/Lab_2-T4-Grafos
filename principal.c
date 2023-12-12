#include "grafosComListas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao, numVertices, origem, destino;
    printf("\nDigite o numero de vertices do grafo: ");
    scanf("%d", &numVertices);
    Grafo* grafo = criarGrafo(numVertices);
    do {
        printf("\n----- MENU -----\n");
        printf("1 - Inserir no grafo\n");
        printf("2 - Remover do grafo\n");
        printf("3 - Imprimir o grafo\n");
        printf("4 - Percorrer em largura, mostrando percurso em pre-ordem e pos-ordem\n");
        printf("5 - Percorrer em profundidade, mostrando percurso em pre-ordem e pos-ordem\n");
        printf("6 - Sair\n");
        printf("\n------> Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("\n\n *****Insercao no grafo*****\n");
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite o destino: ");
                scanf("%d", &destino);
                inserirAresta(grafo, origem, destino);
                printf("\n");
                break;
            case 2:
                printf("\n\n *****Remocao do grafo*****\n");
                printf("Digite a origem: ");
                scanf("%d", &origem);
                printf("Digite o destino: ");
                scanf("%d", &destino);
                removerAresta(grafo, origem, destino);
                printf("\n");
                break;
            case 3:
                printf("\n\n *****Impressao do grafo*****\n");
                imprimirGrafo(grafo);
                printf("\n");
                break;
            case 4:
                printf("\n\n *****Percursos do grafo em largura*****\n");
                int* preOrdem = (int*)malloc(grafo->numVertices * sizeof(int));
                int* posOrdem = (int*)malloc(grafo->numVertices * sizeof(int));
                if (preOrdem == NULL || posOrdem == NULL) {
                    perror("\n\n *****Erro ao alocar memoria para os vetores de pre-ordem e pos-ordem\n");
                    exit(EXIT_FAILURE);
                }
                printf("Digite o vertice de origem: ");
                scanf("%d", &origem);
                percorrerGrafoLargura(grafo, origem, preOrdem, posOrdem);
                printf("\n- Busca em largura, mostrando percurso PRE-ORDEM:\n");
                for (int i = 0; i < grafo->numVertices && preOrdem[i] != -1; ++i) {
                    printf("%d", preOrdem[i]);
                    if(i < grafo->numVertices - 1 && preOrdem[i + 1] != -1) {
                        printf(", ");
                    }
                }
                printf("\n- Busca em largura, mostrando percurso POS-ORDEM:\n");
                for (int i = 0; i < grafo->numVertices && posOrdem[i] != -1; ++i) {
                    printf("%d", posOrdem[i]);
                    if(i < grafo->numVertices - 1 && posOrdem[i + 1] != -1) {
                        printf(", ");
                    }
                }
                printf("\n");
                free(preOrdem);
                free(posOrdem);
                break;
            case 5:
                printf("\n\n *****Percursos do grafo em profundidade*****\n");
                printf("Digite o vertice de origem: ");
                scanf("%d", &origem);
                printf("\n- Busca em profundidade, mostrando percurso PRE-ORDEM:\n");
                percorrerGrafoProfundidadePreOrdem(grafo, origem);
                printf("\n- Busca em profundidade, mostrando percurso POS-ORDEM:\n");
                percorrerGrafoProfundidadePosOrdem(grafo, origem);
                printf("\n");
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("\n\n ***** ERRO: Opcao invalida! *****\n\n");
                break;
        }
    } while (opcao != 6);
    liberarGrafo(grafo);
    return 0;
}