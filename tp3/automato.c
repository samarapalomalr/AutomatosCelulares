#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "double_hash.h"

// Aloca e inicializa um reticulado
AutomatoCelular* alocarReticulado(int linhas, int colunas) {
    AutomatoCelular* automato = (AutomatoCelular*)malloc(sizeof(AutomatoCelular));
    if (automato == NULL) {
        return NULL; 
    }

    automato->linhas = linhas;
    automato->colunas = colunas;
    automato->tabela = criarHashTable(linhas * colunas); // Tabela hash do tamanho da area do reticulado

    if (automato->tabela == NULL) { 
        free(automato);
        return NULL;
    }

    return automato; // Retorna o ponteiro para o automato alocado
}

// Libera a memoria associada ao reticulado
void desalocarReticulado(AutomatoCelular** automato) {
    if (*automato != NULL) {
        destruirHashTable((*automato)->tabela); // Destroi a tabela hash
        free(*automato); // Libera a memoria do automato
        *automato = NULL; // Zera o ponteiro para evitar dangling pointers
    }
}

// Le os valores iniciais do reticulado a partir de um arquivo
int leituraReticulado(AutomatoCelular* automato, FILE* arquivo) {
    int valor;
    for (int i = 0; i < automato->linhas; i++) {
        for (int j = 0; j < automato->colunas; j++) {
            if (fscanf(arquivo, "%d", &valor) != 1) { 
                return 0; // Falha na leitura
            }
            if (valor == 1) { // Inserir apenas celulas vivas
                if (!inserirHashTable(automato->tabela, i * automato->colunas + j, 1)) {
                    return 0; // Falha na insercao
                }
            }
            // Celulas com valor 0 (mortas) nao sao inseridas na tabela hash
        }
    }
    return 1; // Sucesso
}

// Conta o numero de vizinhas vivas de uma celula
int contarVizinhasVivas(AutomatoCelular* automato, int linha, int coluna) {
    int vizinhasVivas = 0; // Contador de celulas vivas vizinhas
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Deslocamentos em linha
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Deslocamentos em coluna

    // Verifica todas as 8 vizinhas
    for (int i = 0; i < 8; i++) {
        int novaLinha = linha + dx[i];
        int novaColuna = coluna + dy[i];

        // Verifica se a nova posicao esta dentro dos limites do reticulado
        if (novaLinha >= 0 && novaLinha < automato->linhas && novaColuna >= 0 && novaColuna < automato->colunas) {
            int valor = buscarHashTable(automato->tabela, novaLinha * automato->colunas + novaColuna);
            vizinhasVivas += valor; // Adiciona a contagem se a vizinha esta viva (1) ou morta (0)
        }
    }

    return vizinhasVivas; // Retorna o numero de vizinhas vivas
}

// Evolui o reticulado por um numero especificado de geracoes
void evoluirReticulado(AutomatoCelular* automato, int geracoes) {
    for (int g = 0; g < geracoes; g++) {
        HashTable* novaGeracao = criarHashTable(automato->linhas * automato->colunas); // Cria uma nova tabela hash para a proxima geracao

        if (novaGeracao == NULL) {
            fprintf(stderr, "Erro ao criar nova geração.\n");
            return;
        }

        // Itera sobre todas as celulas do reticulado
        for (int i = 0; i < automato->linhas; i++) {
            for (int j = 0; j < automato->colunas; j++) {
                int vivas = contarVizinhasVivas(automato, i, j); 
                int estadoAtual = buscarHashTable(automato->tabela, i * automato->colunas + j); // Obtem o estado atual da celula 

                // Aplica as regras do Jogo da Vida
                int novoEstado = 0;
                if (estadoAtual == 1 && (vivas == 2 || vivas == 3)) {
                    novoEstado = 1; // A celula continua viva
                } else if (estadoAtual == 0 && vivas == 3) {
                    novoEstado = 1; // A celula se torna viva
                }
                // Caso contrario, a celula permanece morta (nao e inserida na tabela)

                if (novoEstado == 1) { // Insere apenas celulas vivas
                    if (!inserirHashTable(novaGeracao, i * automato->colunas + j, 1)) {
                        fprintf(stderr, "Erro ao inserir nova célula.\n");
                        destruirHashTable(novaGeracao);
                        return;
                    }
                }
                // Celulas mortas nao sao inseridas na tabela hash
            }
        }

        destruirHashTable(automato->tabela); // Destroi a tabela anterior
        automato->tabela = novaGeracao;      // Atualiza para a nova geracao
    }
}

// Imprime o reticulado no estado atual
void imprimeReticulado(const AutomatoCelular* automato) {
    for (int i = 0; i < automato->linhas; i++) {
        for (int j = 0; j < automato->colunas; j++) {
            int valor = buscarHashTable(automato->tabela, i * automato->colunas + j);
            printf("%d ", valor); 
        }
        printf("\n");
    }
}





