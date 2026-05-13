#ifndef OBJETO_H
#define OBJETO_H

#include "config.h"

typedef enum {
    OBJETO_GUARDA_CHUVA = 0,
    OBJETO_MASCARA      = 1,
    OBJETO_ZABUMBA      = 2,
    OBJETO_ROJAO        = 3
} TipoObjeto;

typedef struct {
    TipoObjeto tipo;
    float      posX;
    float      posY;
    float      largura;
    float      altura;
    int        ativo;
    int        pontos;
} Objeto;

void inicializarObjeto(Objeto *obj, float posX, float posY, TipoObjeto tipo);
int  pontosDoObjeto(TipoObjeto tipo);

#endif /* OBJETO_H */
