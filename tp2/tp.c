//Funcao principal que controla a execucao do programa
#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main(int argc, char* argv[]) {
    int linhas, geracoes;

    //Le a primeira linha do arquivo que contem a dimensao da matriz e o numero de geracoes
    fscanf(stdin, "%d %d", &linhas, &geracoes);

    AutomatoCelular* automato = alocarReticulado(linhas, linhas);
    leituraReticulado(automato, stdin); //Le o reticulado a partir do stdin

    evoluirReticulado(automato, geracoes);

    imprimeReticulado(automato);

    desalocarReticulado(&automato);

    return 0;
}
