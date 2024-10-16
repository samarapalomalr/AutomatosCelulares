#include "automato.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numGeracoes;

    // Ler o automato celular da entrada padrao
    AutomatoCelular* automato = leituraReticulado(stdin, &numGeracoes);

    // Evolui o reticulado pelo numero de geracoes especificado
    evoluirReticulado(automato, numGeracoes);

    // Imprimi o estado atual do reticulado apos as geracoes
    imprimeReticulado(automato);

    // Desaloca memoria antes de encerrar o programa
    desalocarReticulado(automato);

    return EXIT_SUCCESS;
}




