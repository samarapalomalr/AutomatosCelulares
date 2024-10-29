//Interface do TAD AutomatoCelular
//Usando listas encadeadas para representar um automato
#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "matriz.h"

typedef struct AutomatoCelular {
    MatrizEsparsa* matriz;
} AutomatoCelular;

AutomatoCelular* alocarReticulado(int linhas, int colunas);
void desalocarReticulado(AutomatoCelular** automato);
void leituraReticulado(AutomatoCelular* automato, FILE* arquivo);
void evoluirReticulado(AutomatoCelular* automato, int geracoes);
void imprimeReticulado(const AutomatoCelular* automato);

#endif // AUTOMATO_H

