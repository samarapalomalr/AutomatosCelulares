#include "double_hash.h"
#include <stdlib.h>
#include <stdio.h>

#define VAZIO -1

// Cria uma tabela hash
HashTable* criarHashTable(int tamanho) {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    if (tabela == NULL) return NULL;

    tabela->chaves = (int*)malloc(tamanho * sizeof(int));
    tabela->valores = (int*)malloc(tamanho * sizeof(int));

    if (tabela->chaves == NULL || tabela->valores == NULL) {
        free(tabela);
        return NULL;
    }

    for (int i = 0; i < tamanho; i++) {
        tabela->chaves[i] = VAZIO; // Inicializa todas as chaves como vazias
        tabela->valores[i] = 0;    // Inicializa os valores como 0 
    }

    tabela->tamanho = tamanho;
    tabela->ocupados = 0;

    return tabela;
}

// Destroi a tabela hash
void destruirHashTable(HashTable* tabela) {
    if (tabela) {
        free(tabela->chaves);
        free(tabela->valores);
        free(tabela);
    }
}

// Funcao de hash primaria 
int hash1(int chave, int tamanho) {
    return ((chave * 1 + 2) % tamanho);
}

// Funcao de hash secundaria
int hash2(int chave, int tamanho) {
    return ((chave * 3 + 4) % tamanho);
}

// Funcao para encontrar a posicao correta de uma chave
int encontrarPosicao(HashTable* tabela, int chave) {
    int posicao = hash1(chave, tabela->tamanho);
    int salto = hash2(chave, tabela->tamanho);
    int i = 0;

    while (tabela->chaves[posicao] != VAZIO) {
        if (tabela->chaves[posicao] == chave) {
            return posicao; // Retorna a posicao se encontrar a chave
        }
        posicao = (posicao + salto) % tabela->tamanho;
        i++;
        
        if (i >= tabela->tamanho) return -1; // Se percorreu toda a tabela e nao encontrou
    }

    return posicao; // Retorna a posicao onde pode inserir
}

// Funcao para inserir na tabela hash
int inserirHashTable(HashTable* tabela, int chave, int valor) {
    if (tabela->ocupados >= tabela->tamanho) return 0; // Tabela cheia

    int posicao = encontrarPosicao(tabela, chave);
    if (posicao == -1) return 0; // Nao encontrou espaco

    if (tabela->chaves[posicao] == VAZIO) {
        tabela->ocupados++;
    }

    tabela->chaves[posicao] = chave;
    tabela->valores[posicao] = valor;
    return 1;
}

// Funcao para buscar na tabela hash
int buscarHashTable(HashTable* tabela, int chave) {
    int posicao = encontrarPosicao(tabela, chave);
    if (posicao == -1 || tabela->chaves[posicao] == VAZIO) {
        return 0; 
    }

    return tabela->valores[posicao]; // Retorna 1 se a celula esta viva
}







