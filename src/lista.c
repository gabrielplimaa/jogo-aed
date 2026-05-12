#include <stdlib.h>
#include "lista.h"

/* Inicializa a lista sem nós e com contador zerado */
void inicializarLista(ListaObjetos *lista) {
    lista->inicio    = NULL;
    lista->quantidade = 0;
}

/* Aloca um novo nó, preenche o objeto via inicializarObjeto() e insere no início */
void inserirObjeto(ListaObjetos *lista, float posX, float posY, TipoObjeto tipo) {
    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
    if (novo == NULL) return;

    inicializarObjeto(&novo->objeto, posX, posY, tipo);
    novo->proximo = lista->inicio;
    lista->inicio = novo;
    lista->quantidade++;
}

/* Remove o nó atual, ajusta ponteiros do vizinho anterior e libera a memória */
void removerObjeto(ListaObjetos *lista, NoLista *anterior, NoLista *atual) {
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    lista->quantidade--;
}

/* Avança todos os objetos somando velocidade ao eixo Y */
void moverObjetos(ListaObjetos *lista, float velocidade) {
    NoLista *no = lista->inicio;
    while (no != NULL) {
        no->objeto.posY += velocidade;
        no = no->proximo;
    }
}

/* Percorre a lista testando colisão retangular com o jogador.
   Rojão colidido remove o nó e incrementa *vidasPerdidas.
   Item normal colidido remove o nó e acumula seus pontos.
   Retorna o total de pontos ganhos no quadro. */
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

/* Retorna o número de objetos atualmente na lista */
int contarObjetos(const ListaObjetos *lista) {
    return lista->quantidade;
}

/* Libera todos os nós em sequência e reinicializa a lista vazia */
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
