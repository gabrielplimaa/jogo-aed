#include "jogador.h"

void inicializarJogador(Jogador *foliao) {
    foliao->largura     = LARGURA_JOGADOR;
    foliao->altura      = ALTURA_JOGADOR;
    foliao->posX        = (LARGURA_TELA - LARGURA_JOGADOR) / 2.0f;
    foliao->posY        = ALTURA_TELA - ALTURA_JOGADOR - 10.0f;
    foliao->vidas       = VIDAS_INICIAIS;
    foliao->pontuacao   = 0;
    foliao->estadoAtual = PARADO;
}

void moverJogador(Jogador *foliao) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        foliao->posX -= VELOCIDADE_JOGADOR;
        foliao->estadoAtual = ANDANDO_ESQUERDA;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        foliao->posX += VELOCIDADE_JOGADOR;
        foliao->estadoAtual = ANDANDO_DIREITA;
    } else {
        foliao->estadoAtual = PARADO;
    }

    if (foliao->posX < 0.0f)
        foliao->posX = 0.0f;
    if (foliao->posX + foliao->largura > LARGURA_TELA)
        foliao->posX = LARGURA_TELA - foliao->largura;
}
