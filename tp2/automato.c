//Implementacao do TAD AutomatoCelular
#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "matriz.h"

//Aloca e inicializa uma estrutura AutomatoCelular, que representa o reticulado do automato celular
AutomatoCelular* alocarReticulado(int linhas, int colunas) {
    //Internamente, essa estrutura contem uma matriz esparsa, que e alocada pela funcao alocarMatriz 
    AutomatoCelular* automato = (AutomatoCelular*)malloc(sizeof(AutomatoCelular));
    automato->matriz = alocarMatriz(linhas, colunas);
    return automato; //retorna um ponteiro para o automato
}

//Libera a memoria alocada para o AutomatoCelular, bem como para a matriz esparsa associada
void desalocarReticulado(AutomatoCelular** automato) {
    if (automato == NULL || *automato == NULL) return;
    desalocarMatriz(&(*automato)->matriz);
    free(*automato);
    *automato = NULL;
}

//Le o estado inicial do automato celular a partir de um arquivo
void leituraReticulado(AutomatoCelular* automato, FILE* arquivo) {
    //Para cada posicao na matriz, o valor lido (0 ou 1) e utilizado para decidir se deve 
    //ser inserida uma celula na matriz esparsa
    for (int i = 0; i < automato->matriz->numLinhas; i++) {
        for (int j = 0; j < automato->matriz->numColunas; j++) {
            int valor;
            fscanf(arquivo, "%d", &valor);
            //Se o valor for 1, a funcao inserirElemento e chamada para inserir a 
            //celula ativa na posicao correspondente
            if (valor == 1) {
                inserirElemento(automato->matriz, i, j);
            }
        }
    }
}

//Evolucao do automato celular por um numero especificado de geracoes
void evoluirReticulado(AutomatoCelular* automato, int geracoes) {
    for (int g = 0; g < geracoes; g++) {
        //a cada nova geração
        //Uma nova matriz esparsa (novaMatriz) e alocada para armazenar o estado atualizado
        MatrizEsparsa* novaMatriz = alocarMatriz(automato->matriz->numLinhas, automato->matriz->numColunas);

        
        //Para cada celula da matriz atual, e contada a quantidade de celulas vivas em 
        //suas vizinhancas (oito celulas adjacentes)
        for (int i = 0; i < automato->matriz->numLinhas; i++) {
            for (int j = 0; j < automato->matriz->numColunas; j++) {
                int vivos = 0;
                int deltas[] = {-1, 0, 1};
                for (int di = 0; di < 3; di++) {
                    for (int dj = 0; dj < 3; dj++) {
                        if (!(deltas[di] == 0 && deltas[dj] == 0)) {
                            int ni = i + deltas[di];
                            int nj = j + deltas[dj];
                            if (ni >= 0 && ni < automato->matriz->numLinhas && nj >= 0 && nj < automato->matriz->numColunas) {
                                if (buscarElemento(automato->matriz, ni, nj)) {
                                    vivos++;
                                }
                            }
                        }
                    }
                }

                //As regras de atualizacao sao aplicadas
                Celula* celulaAtual = buscarElemento(automato->matriz, i, j);
                if (celulaAtual) {
                    if (vivos == 2 || vivos == 3) {
                        inserirElemento(novaMatriz, i, j);
                    }
                } else {
                    if (vivos == 3) {
                        inserirElemento(novaMatriz, i, j);
                    }
                }
            }
        }  
        //Apos processar todas as celulas, a matriz antiga e desalocada, 
        //e a nova matriz se torna a matriz atual do automato
        desalocarMatriz(&automato->matriz);
        automato->matriz = novaMatriz;
    }
}

//Imprime o estado atual do automato celular
void imprimeReticulado(const AutomatoCelular* automato) {
    imprimeMatriz(automato->matriz);
}


