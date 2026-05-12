#ifndef LISTA_H
#define LISTA_H

#include "config.h"
#include "objeto.h"

typedef struct NoLista {
    Objeto          objeto;
    struct NoLista *proximo;
} NoLista;

typedef struct {
    NoLista *inicio;
    int      quantidade;
} ListaObjetos;

void inicializarLista(ListaObjetos *lista);
void inserirObjeto(ListaObjetos *lista, float posX, float posY, TipoObjeto tipo);
void removerObjeto(ListaObjetos *lista, NoLista *anterior, NoLista *atual);
void moverObjetos(ListaObjetos *lista, float velocidade);
int  detectarColisao(ListaObjetos *lista, float jogX, float jogY,
                     float jogLarg, float jogAlt, int *vidasPerdidas);
int  contarObjetos(const ListaObjetos *lista);
void limparLista(ListaObjetos *lista);

#endif /* LISTA_H */
