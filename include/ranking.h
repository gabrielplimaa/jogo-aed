#ifndef RANKING_H
#define RANKING_H

#include "ordenacao.h"
#include "config.h"

typedef struct {
    EntradaRanking entradas[MAX_RANKING];
    int total;
} Ranking;

void inicializarRanking(Ranking *ranking);
void inserirNoRanking(Ranking *ranking, int pontuacao, const char *nome);
void ordenarRanking(Ranking *ranking);
void salvarRanking(const Ranking *ranking, const char *caminho);
void carregarRanking(Ranking *ranking, const char *caminho);
void exibirRanking(const Ranking *ranking);

#endif
