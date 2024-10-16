#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <stdio.h>  

// Declaracao da estrutura que representa o automato 
typedef struct {
    // Representa o automato celular
    int dimensao;
    int **celulas; // matriz para armazenar o estado das celulas
    int **proximaGeracao; // matriz para armazenar o estado da proxima geracao
} AutomatoCelular;

// Funcoes publicas do TAD AutomatoCelular
AutomatoCelular* alocarReticulado(int dimensao);
void desalocarReticulado(AutomatoCelular* automato);
AutomatoCelular* leituraReticulado(FILE* entrada, int *numGeracoes);
int contarCelulasVivasVizinhas(AutomatoCelular* automato, int linha, int coluna);
void evoluirReticulado(AutomatoCelular* automato, int geracoes);
void imprimeReticulado(AutomatoCelular* automato);

#endif


