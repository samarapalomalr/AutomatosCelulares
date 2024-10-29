//Interface do TAD MatrizEsparsa
//Esse TAD representa uma "matriz esparsa" "usando listas encadeadas circulares"
#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Celula {
    int linha;
    int coluna;
    int valor;
    struct Celula* prox;
} Celula;

typedef struct {
    int numLinhas;
    int numColunas;
    Celula** linhas;
} MatrizEsparsa;

MatrizEsparsa* alocarMatriz(int linhas, int colunas);
void desalocarMatriz(MatrizEsparsa** matriz);
void inserirElemento(MatrizEsparsa* matriz, int linha, int coluna);
Celula* buscarElemento(MatrizEsparsa* matriz, int linha, int coluna);
void imprimeMatriz(const MatrizEsparsa* matriz);

#endif // MATRIZ_H
