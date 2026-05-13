#include "ranking.h"
#include <stdio.h>
#include <string.h>

void inicializarRanking(Ranking *ranking) {
    ranking->total = 0;
    for (int i = 0; i < MAX_RANKING; i++) {
        ranking->entradas[i].pontuacao = 0;
        ranking->entradas[i].nome[0] = '\0';
    }
}

void inserirNoRanking(Ranking *ranking, int pontuacao, const char *nome) {
    if (ranking->total < MAX_RANKING) {
        ranking->entradas[ranking->total].pontuacao = pontuacao;
        strncpy(ranking->entradas[ranking->total].nome, nome, TAMANHO_NOME - 1);
        ranking->entradas[ranking->total].nome[TAMANHO_NOME - 1] = '\0';
        ranking->total++;
    } else {
        int ultimo = MAX_RANKING - 1;
        if (pontuacao > ranking->entradas[ultimo].pontuacao) {
            ranking->entradas[ultimo].pontuacao = pontuacao;
            strncpy(ranking->entradas[ultimo].nome, nome, TAMANHO_NOME - 1);
            ranking->entradas[ultimo].nome[TAMANHO_NOME - 1] = '\0';
        }
    }
    ordenarRanking(ranking);
}

void ordenarRanking(Ranking *ranking) {
    insertionSort(ranking->entradas, ranking->total);
}

void salvarRanking(const Ranking *ranking, const char *caminho) {
    FILE *arquivo = fopen(caminho, "w");
    if (!arquivo) return;
    for (int i = 0; i < ranking->total; i++) {
        fprintf(arquivo, "%d %s\n", ranking->entradas[i].pontuacao, ranking->entradas[i].nome);
    }
    fclose(arquivo);
}

void carregarRanking(Ranking *ranking, const char *caminho) {
    inicializarRanking(ranking);
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) return;
    while (ranking->total < MAX_RANKING) {
        EntradaRanking entrada;
        if (fscanf(arquivo, "%d %31s", &entrada.pontuacao, entrada.nome) != 2) break;
        ranking->entradas[ranking->total] = entrada;
        ranking->total++;
    }
    fclose(arquivo);
    ordenarRanking(ranking);
}

void exibirRanking(const Ranking *ranking) {
    printf("=== RANKING ===\n");
    for (int i = 0; i < ranking->total; i++) {
        printf("%d. %s - %d\n", i + 1, ranking->entradas[i].nome, ranking->entradas[i].pontuacao);
    }
    printf("===============\n");
}
