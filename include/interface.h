#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogador.h"
#include "lista.h"

void desenharFundo(void);
void desenharJogador(const Jogador *foliao);
void desenharObjetos(const ListaObjetos *lista);
void desenharHUD(const Jogador *foliao, int nivel);
void desenharGameOver(int pontuacao);

#endif
