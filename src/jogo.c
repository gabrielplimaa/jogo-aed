#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "jogo.h"
#include "interface.h"
#include "config.h"

static float posXAleatoria(void) {
    return (float)(GetRandomValue(0, LARGURA_TELA - LARGURA_OBJETO));
}

static TipoObjeto tipoAleatorio(void) {
    return (TipoObjeto)(GetRandomValue(0, 2));
}

void inicializarJogo(EstadoJogo *estado, Ranking *ranking, const char *nome) {
    inicializarJogador(&estado->foliao);
    inicializarLista(&estado->objetos);
    estado->ranking       = ranking;
    estado->fase          = FASE_JOGANDO;
    estado->velocidade    = VELOCIDADE_BASE;
    estado->frameContador = 0;
    estado->nivel         = 0;

    strncpy(estado->nomeJogador, nome, TAMANHO_NOME - 1);
    estado->nomeJogador[TAMANHO_NOME - 1] = '\0';
}

static void atualizarNivel(EstadoJogo *estado) {
    int novoNivel = estado->foliao.pontuacao / PONTOS_POR_NIVEL;
    if (novoNivel > estado->nivel) {
        estado->nivel      = novoNivel;
        estado->velocidade = VELOCIDADE_BASE + estado->nivel * INCREMENTO_VEL;
    }
}

static int removerObjetosPerdidos(ListaObjetos *lista) {
    NoLista *anterior = NULL;
    NoLista *atual    = lista->inicio;
    int      perdidos = 0;

    while (atual != NULL) {
        if (atual->objeto.posY > ALTURA_TELA) {
            NoLista *proximo = atual->proximo;
            removerObjeto(lista, anterior, atual);
            atual    = proximo;
            perdidos++;
        } else {
            anterior = atual;
            atual    = atual->proximo;
        }
    }
    return perdidos;
}

static void desenharGameOverFinal(int pontuacao, const char *nome) {
    desenharGameOver(pontuacao);

    char msg[64];
    snprintf(msg, sizeof(msg), "Placar de %s salvo no ranking!", nome);
    DrawText(msg, LARGURA_TELA / 2 - MeasureText(msg, 18) / 2, 310, 18, YELLOW);

    const char *voltar = "ENTER ou TAB para voltar ao menu";
    DrawText(voltar, LARGURA_TELA / 2 - MeasureText(voltar, 16) / 2, 350, 16, LIGHTGRAY);
}

void executarJogo(EstadoJogo *estado) {
    int rankingSalvo = 0;

    while (!WindowShouldClose()) {

        /* TAB ou ESC em qualquer fase volta ao menu */
        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) break;

        if (estado->fase == FASE_JOGANDO) {
            moverJogador(&estado->foliao);

            estado->frameContador++;
            if (estado->frameContador >= INTERVALO_SPAWN){
                estado->frameContador = 0;
                inserirObjeto(&estado->objetos, posXAleatoria(), -(float)ALTURA_OBJETO, tipoAleatorio());
            }

            moverObjetos(&estado->objetos, estado->velocidade);

            int vidasPerdidas = 0;
            int pontosGanhos  = detectarColisao(
                &estado->objetos,
                estado->foliao.posX, estado->foliao.posY,
                estado->foliao.largura, estado->foliao.altura,
                &vidasPerdidas
            );
            estado->foliao.pontuacao += pontosGanhos;
            estado->foliao.vidas     -= vidasPerdidas;

            int perdidos = removerObjetosPerdidos(&estado->objetos);
            estado->foliao.vidas -= perdidos;

            atualizarNivel(estado);

            if (estado->foliao.vidas <= 0) {
                estado->foliao.vidas = 0;
                limparLista(&estado->objetos);

                /* Salva no ranking com o nome coletado antes de jogar */
                if (!rankingSalvo) {
                    inserirNoRanking(estado->ranking, estado->foliao.pontuacao, estado->nomeJogador);
                    salvarRanking(estado->ranking, CAMINHO_RANKING);
                    rankingSalvo = 1;
                }

                estado->fase = FASE_GAME_OVER;
            }

        } else {
            /* FASE_GAME_OVER: ENTER volta ao menu */
            if (IsKeyPressed(KEY_ENTER)) break;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            desenharFundo();
            desenharObjetos(&estado->objetos);
            desenharJogador(&estado->foliao);
            desenharHUD(&estado->foliao, estado->nivel);

            if (estado->fase == FASE_GAME_OVER)
                desenharGameOverFinal(estado->foliao.pontuacao, estado->nomeJogador);
        EndDrawing();
    }
}

void encerrarJogo(EstadoJogo *estado) {
    limparLista(&estado->objetos);
}
