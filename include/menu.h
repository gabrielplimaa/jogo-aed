#ifndef MENU_H
#define MENU_H

#include "ranking.h"
#include "config.h"

typedef enum {
    MENU_JOGAR       = 1,
    MENU_RANKING     = 2,
    MENU_INSTRUCOES  = 3,
    MENU_SAIR        = 0
} OpcaoMenu;

void telaAbertura(void);
OpcaoMenu exibirMenuPrincipal(void);
void telaRanking(const Ranking *ranking);
void telaInstrucoes(void);
int telaEntradaNome(char *nomeDestino, int tamanhoMax);

#endif
