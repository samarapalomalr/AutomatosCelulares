//Implementacao do TAD MatrizEsparsa
#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

//Aloca dinamicamente uma estrutura MatrizEsparsa
MatrizEsparsa* alocarMatriz(int linhas, int colunas) {
    MatrizEsparsa* matriz = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    matriz->numLinhas = linhas;
    matriz->numColunas = colunas;
    //O campo linhas é um vetor de ponteiros para celulas
    matriz->linhas = (Celula**)malloc(linhas * sizeof(Celula*));
    for (int i = 0; i < linhas; i++) {
        //Todos os ponteiros sao definidos como NULL, indicando que nao ha celulas nessa linha
        matriz->linhas[i] = NULL;
    }
    return matriz; //retorna o ponteiro para a matriz alocada
}

//Libera a memoria alocada para a MatrizEsparsa e suas celulas
void desalocarMatriz(MatrizEsparsa** matriz) {
    if (matriz == NULL || *matriz == NULL) return;

    //Para cada linha, se ha celulas alocadas, percorre-se a lista 
    //encadeada circular e libera cada celula
    for (int i = 0; i < (*matriz)->numLinhas; i++) {
        Celula* atual = (*matriz)->linhas[i];
        if (atual != NULL) {
            Celula* inicio = atual;
            do {
                Celula* temp = atual;
                atual = atual->prox;
                free(temp);
            } while (atual != inicio);
        }
    }
    free((*matriz)->linhas); //libera o vetor de linhas
    free(*matriz); //libera a matriz
    *matriz = NULL;
}

//Insere um elemento na matriz esparsa na posicao especificada por linha e coluna
void inserirElemento(MatrizEsparsa* matriz, int linha, int coluna) {
    if (linha >= matriz->numLinhas || coluna >= matriz->numColunas) return; //Verifica se a posiçao é valida

    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->linha = linha;
    nova->coluna = coluna;
    nova->valor = 1;
    
    Celula* atual = matriz->linhas[linha];

    if (atual == NULL) { //Se a linha ainda nao possui elementos
        nova->prox = nova; //A nova celula e adicionada como o unico elemento da lista circular
        matriz->linhas[linha] = nova;
    
    //insere a nova celula na posicao correta na lista circular, garantindo que as celulas 
    //estejam ordenadas pela coluna
    //Depois, a lista circular e atualizada para manter a referencia correta entre as celulas, 
    //seja ao inserir no inicio ou no meio da lista
    } else {
        Celula* anterior = NULL;
        do {
            if (atual->coluna >= coluna) break;
            anterior = atual;
            atual = atual->prox;
        } while (atual != matriz->linhas[linha]);

        nova->prox = atual;
        if (anterior != NULL) {
            anterior->prox = nova;
        } else {
            matriz->linhas[linha] = nova;
        }
    }
}

//Busca por uma celula especifica na matriz esparsa
Celula* buscarElemento(MatrizEsparsa* matriz, int linha, int coluna) {
    if (linha >= matriz->numLinhas || coluna >= matriz->numColunas) return NULL;

    Celula* atual = matriz->linhas[linha];
    if (atual == NULL) return NULL;

    //Percorre a lista circular na linha especificada ate encontrar a celula 
    //que corresponde a coluna desejada
    do {
        if (atual->coluna == coluna) return atual;
        atual = atual->prox;
    } while (atual != matriz->linhas[linha]);

    return NULL;
}

//Imprime a matriz esparsa na forma de uma matriz densa
//A lista circular e percorrida conforme necessario para 
//verificar a presenca de celulas ativas em cada coluna
void imprimeMatriz(const MatrizEsparsa* matriz) {
    for (int i = 0; i < matriz->numLinhas; i++) {
        Celula* atual = matriz->linhas[i];
        for (int j = 0; j < matriz->numColunas; j++) {
            if (atual != NULL && atual->coluna == j) {
                printf("1 ");
                atual = atual->prox;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
