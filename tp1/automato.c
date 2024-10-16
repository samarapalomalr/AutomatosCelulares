#include "automato.h"
#include <stdlib.h>
#include <stdio.h>

//Esse arquivo contera as implementacoes das funcoes que operam sobre a estrutura do automato 

// Aloca um reticulado
AutomatoCelular* alocarReticulado(int dimensao) {
    AutomatoCelular* automato = (AutomatoCelular*)malloc(sizeof(AutomatoCelular));
    if (automato == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o reticulado.\n");
        exit(EXIT_FAILURE);
    }

    automato->celulas = (int**)malloc(dimensao * sizeof(int*));
    if (automato->celulas == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para as celulas.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimensao; i++) {
        automato->celulas[i] = (int*)malloc(dimensao * sizeof(int));
        if (automato->celulas[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para as celulas.\n");
            exit(EXIT_FAILURE);
        }
    }

    automato->proximaGeracao = (int**)malloc(dimensao * sizeof(int*));
    if (automato->proximaGeracao == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para a proxima geracao.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < dimensao; i++) {
        automato->proximaGeracao[i] = (int*)malloc(dimensao * sizeof(int));
        if (automato->proximaGeracao[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memoria para a proxima geracao.\n");
            exit(EXIT_FAILURE);
        }
    }

    automato->dimensao = dimensao;

    return automato;
}

// Desaloca um reticulado
void desalocarReticulado(AutomatoCelular* automato) {
    // Libera memoria das matrizes de celulas e da estrutura AutomatoCelular
    for (int i = 0; i < automato->dimensao; i++) {
        free(automato->celulas[i]);
        free(automato->proximaGeracao[i]);
    }
    free(automato->celulas);
    free(automato->proximaGeracao);
    free(automato);
}

// Ler o reticulado inicial a partir do arquivo
AutomatoCelular* leituraReticulado(FILE* entrada, int *numGeracoes) {
    int dimensao;
    fscanf(entrada, "%d %d", &dimensao, numGeracoes);

    AutomatoCelular* automato = alocarReticulado(dimensao);

    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < dimensao; j++) {
            fscanf(entrada, "%d", &automato->celulas[i][j]);
        }
    }

    return automato;
}

// Funcao auxiliar para contar o numero de celulas vivas vizinhas de uma celula especifica
int contarCelulasVivasVizinhas(AutomatoCelular* automato, int linha, int coluna) {
    int contador = 0;
    int dimensao = automato->dimensao;

    // Verifica as 8 celulas vizinhas ao redor da celula atual
    for (int i = linha - 1; i <= linha + 1; i++) {
        for (int j = coluna - 1; j <= coluna + 1; j++) {
            // Verifica se a celula esta dentro dos limites do reticulado
            if (i >= 0 && i < dimensao && j >= 0 && j < dimensao) {
                // Ignora a propria celula
                if (i != linha || j != coluna) {
                    // Se a celula vizinha estiver viva, incrementar o contador
                    if (automato->celulas[i][j] == 1) {
                        contador++;
                    }
                }
            }
        }
    }
    return contador;
}

// Evolui o reticulado por um numero especificado de geracoes
void evoluirReticulado(AutomatoCelular* automato, int geracoes) {
    // Verifica se ainda ha geracoes a serem evoluidas
    if (geracoes > 0) {
        int dimensao = automato->dimensao;

        // Itera sobre cada celula do reticulado
        for (int i = 0; i < dimensao; i++) {
            for (int j = 0; j < dimensao; j++) {
                // Conta o numero de celulas vivas vizinhas
                int celulasVivasVizinhas = contarCelulasVivasVizinhas(automato, i, j);

                // Aplica as regras do jogo da vida para determinar o estado da celula na proxima geracao
                if (automato->celulas[i][j] == 1) {
                    if (celulasVivasVizinhas < 2 || celulasVivasVizinhas > 3) {
                        // Morte por solidao ou superpopulacao
                        automato->proximaGeracao[i][j] = 0;
                    } else {
                        // Celula viva permanece viva
                        automato->proximaGeracao[i][j] = 1;
                    }
                } else {
                    if (celulasVivasVizinhas == 3) {
                        // Renascimento de celula morta
                        automato->proximaGeracao[i][j] = 1;
                    } else {
                        // Celula morta permanece morta
                        automato->proximaGeracao[i][j] = 0;
                    }
                }
            }
        }

        // Atualiza o estado do reticulado para refletir a proxima geracao
        for (int i = 0; i < dimensao; i++) {
            for (int j = 0; j < dimensao; j++) {
                automato->celulas[i][j] = automato->proximaGeracao[i][j];
            }
        }

        // Chama recursivamente a funcao para evoluir as proximas geracoes
        evoluirReticulado(automato, geracoes - 1);
    }
}

// Imprime o reticulado atual
void imprimeReticulado(AutomatoCelular* automato) {
    for (int i = 0; i < automato->dimensao; i++) {
        for (int j = 0; j < automato->dimensao; j++) {
            printf("%d ", automato->celulas[i][j]);
        }
        printf("\n");
    }
}
