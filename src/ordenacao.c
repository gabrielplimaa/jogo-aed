#include "ordenacao.h"
#include <string.h>

void insertionSort(EntradaRanking *entradas, int total) {
    for (int i = 1; i < total; i++) {
        EntradaRanking chave = entradas[i];
        int j = i - 1;
        while (j >= 0 && entradas[j].pontuacao < chave.pontuacao) {
            entradas[j + 1] = entradas[j];
            j--;
        }
        entradas[j + 1] = chave;
    }
}
