#ifndef JOGADOR_H
#define JOGADOR_H

#include "config.h"
#include "raylib.h"

typedef enum {
    PARADO,
    ANDANDO_ESQUERDA,
    ANDANDO_DIREITA
} EstadoJogador;

typedef struct {
    float posX;
    float posY;
    float largura;
    float altura;
    int vidas;
    int pontuacao;
    EstadoJogador estadoAtual;
} Jogador;

void inicializarJogador(Jogador *foliao);
void moverJogador(Jogador *foliao);

#endif
