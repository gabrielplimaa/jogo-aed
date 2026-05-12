#include <stdlib.h>
#include "lista.h"

void inicializarLista(ListaObjetos *lista) {
    lista->inicio    = NULL;
    lista->quantidade = 0;
}

void inserirObjeto(ListaObjetos *lista, float posX, float posY, TipoObjeto tipo) {
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (novo == NULL) return;

    inicializarObjeto(&novo->objeto, posX, posY, tipo);
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->quantidade++;
}

void removerObjeto(ListaObjetos *lista, NoLista *anterior, NoLista *atual) {
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    lista->quantidade--;
}

void moverObjetos(ListaObjetos *lista, float velocidade) {
    NoLista *no = lista->inicio;
    while (no != NULL) {
        no->objeto.posY += velocidade;
        no = no->proximo;
    }
}


int detectarColisao(ListaObjetos *lista, float jogX, float jogY,
                    float jogLarg, float jogAlt, int *vidasPerdidas) {
    NoLista *anterior    = NULL;
    NoLista *atual       = lista->inicio;
    int      pontosGanhos = 0;

    while (atual != NULL) {
        Objeto *obj = &atual->objeto;

        int colidiu = (obj->posX              < jogX + jogLarg &&
                       obj->posX + obj->largura > jogX          &&
                       obj->posY              < jogY + jogAlt  &&
                       obj->posY + obj->altura  > jogY);

        if (colidiu) {
            NoLista *proximo = atual->proximo;

            if (obj->tipo == OBJETO_ROJAO) {
                (*vidasPerdidas)++;
            } else {
                pontosGanhos += obj->pontos;
            }

            removerObjeto(lista, anterior, atual);
            atual = proximo;
        } else {
            anterior = atual;
            atual    = atual->proximo;
        }
    }

    return pontosGanhos;
}

int contarObjetos(const ListaObjetos *lista) {
    return lista->quantidade;
}

void limparLista(ListaObjetos *lista) {
    NoLista *atual = lista->inicio;
    while (atual != NULL) {
        NoLista *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->inicio    = NULL;
    lista->quantidade = 0;
}
