#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura da Tabela Hash 
typedef struct HashTable {
    int* chaves;      // Vetor de chaves
    int* valores;     // Vetor de valores
    int tamanho;      // Tamanho total da tabela
    int ocupados;     // Numero de posicoes ocupadas
} HashTable;

// Funces principais
HashTable* criarHashTable(int tamanho);
void destruirHashTable(HashTable* tabela);
int inserirHashTable(HashTable* tabela, int chave, int valor);
int buscarHashTable(HashTable* tabela, int chave);

// Funcoes auxiliares para hashing duplo
int hash1(int chave, int tamanho);
int hash2(int chave, int tamanho);
int encontrarPosicao(HashTable* tabela, int chave);

#endif // DOUBLE_HASH_H




