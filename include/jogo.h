#ifndef JOGO_H
#define JOGO_H

#include "lista.h"
#include "jogador.h"
#include "ranking.h"
#include "config.h"

typedef enum {
    FASE_JOGANDO,
    FASE_GAME_OVER
} FaseJogo;

typedef struct {
    Jogador      foliao;
    ListaObjetos objetos;
    Ranking     *ranking;
    FaseJogo     fase;
    float        velocidade;
    int          frameContador;
    int          nivel;
    char         nomeJogador[TAMANHO_NOME];
} EstadoJogo;

void inicializarJogo(EstadoJogo *estado, Ranking *ranking, const char *nome);
void executarJogo(EstadoJogo *estado);
void encerrarJogo(EstadoJogo *estado);

#endif
