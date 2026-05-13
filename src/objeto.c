#include "objeto.h"

int pontosDoObjeto(TipoObjeto tipo) {
    switch (tipo) {
        case OBJETO_GUARDA_CHUVA: return 10;
        case OBJETO_MASCARA:      return 20;
        case OBJETO_ZABUMBA:      return 30;
        case OBJETO_ROJAO:        return 0;
        default:                  return 0;
    }
}

void inicializarObjeto(Objeto *obj, float posX, float posY, TipoObjeto tipo) {
    obj->tipo    = tipo;
    obj->posX    = posX;
    obj->posY    = posY;
    obj->largura = (float)LARGURA_OBJETO;
    obj->altura  = (float)ALTURA_OBJETO;
    obj->ativo   = 1;
    obj->pontos  = pontosDoObjeto(tipo);
}
