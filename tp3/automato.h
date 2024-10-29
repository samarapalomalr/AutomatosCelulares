#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "double_hash.h"

typedef struct AutomatoCelular {
    HashTable* tabela; // Usa a tabela hash para armazenar apenas células vivas
    int linhas, colunas;
} AutomatoCelular;

// Funções principais
AutomatoCelular* alocarReticulado(int linhas, int colunas);
int leituraReticulado(AutomatoCelular* automato, FILE* arquivo); 
void desalocarReticulado(AutomatoCelular** automato);
void evoluirReticulado(AutomatoCelular* automato, int geracoes);
void imprimeReticulado(const AutomatoCelular* automato);

#endif // AUTOMATO_H


