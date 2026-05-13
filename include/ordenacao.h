#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "config.h"

typedef struct {
    char nome[TAMANHO_NOME];
    int pontuacao;
} EntradaRanking;

void insertionSort(EntradaRanking *entradas, int total);

#endif
