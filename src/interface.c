#include <stdio.h>
#include "interface.h"
#include "raylib.h"
#include "config.h"

static Texture2D texFundo;
static Texture2D texFoliao;
static Texture2D texSombrinha;
static Texture2D texMascara;
static Texture2D texZabumba;
static Texture2D texEstrela;
static Texture2D texVida;
static int texturesCarregadas = 0;

static int animFrame = 0;
static int animTimer = 0;
static int facingRight = 1;

static void carregarTexturas(void) {
    if (texturesCarregadas) return;
    texFundo     = LoadTexture("sprites/cenario.png");
    texFoliao    = LoadTexture("sprites/foliao.png");
    texSombrinha = LoadTexture("sprites/sombrinha.png");
    texMascara   = LoadTexture("sprites/mascara.png");
    texZabumba   = LoadTexture("sprites/zabumba.png");
    texEstrela   = LoadTexture("sprites/estrela.png");
    texVida      = LoadTexture("sprites/vida.png");
    texturesCarregadas = 1;
}

void desenharFundo(void) {
    carregarTexturas();
    if (texFundo.id != 0) {
        DrawTexturePro(
            texFundo,
            (Rectangle){0, 0, (float)texFundo.width, (float)texFundo.height},
            (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA},
            (Vector2){0, 0}, 0.0f, WHITE
        );
    } else {
        ClearBackground((Color){20, 10, 50, 255});
    }
}

void desenharJogador(const Jogador *foliao) {
    carregarTexturas();
    Rectangle dest = { foliao->posX, foliao->posY, (float)foliao->largura, (float)foliao->altura };
    if (texFoliao.id > 0) {
        float frameWidth = 125.0f;
        float frameHeight = 125.0f;
        int row = 0;
        int frame = 0;

        if (foliao->estadoAtual == ANDANDO_DIREITA || foliao->estadoAtual == ANDANDO_ESQUERDA) {
            animTimer++;
            if (animTimer >= 10) {
                animTimer = 0;
                animFrame = (animFrame + 1) % 4;
            }
            row = 0;
            frame = animFrame;
            facingRight = (foliao->estadoAtual == ANDANDO_DIREITA);
        } else {
            animFrame = 0;
            animTimer = 0;
            row = 2;
            frame = 0;
        }

        // Flip horizontally when moving/facing left (negative width in src rect)
        int viradoEsquerda = (foliao->estadoAtual == ANDANDO_ESQUERDA) ||
                             (foliao->estadoAtual == PARADO && !facingRight);
        Rectangle src;
        if (viradoEsquerda) {
            src = (Rectangle){ (frame + 1) * frameWidth, row * frameHeight, -frameWidth, frameHeight };
        } else {
            src = (Rectangle){ frame * frameWidth, row * frameHeight, frameWidth, frameHeight };
        }
        DrawTexturePro(texFoliao, src, dest, (Vector2){ 0, 0 }, 0.0f, WHITE);

    } else {
        DrawRectangleRec(dest, BLUE);
        DrawText("Sprite Error", (int)foliao->posX, (int)foliao->posY - 20, 10, RED);
    }
}

void desenharObjetos(const ListaObjetos *lista) {
    carregarTexturas();
    const NoLista *no = lista->inicio;
    while (no != NULL) {
        const Objeto *obj = &no->objeto;
        Rectangle dest = {obj->posX, obj->posY, obj->largura, obj->altura};
        Texture2D tex;
        switch (obj->tipo) {
            case OBJETO_GUARDA_CHUVA: tex = texSombrinha; break;
            case OBJETO_MASCARA:      tex = texMascara;   break;
            case OBJETO_ZABUMBA:      tex = texZabumba;   break;
            default:                  tex = texEstrela;   break;
        }
        if (tex.id != 0) {
            DrawTexturePro(
                tex,
                (Rectangle){0, 0, (float)tex.width, (float)tex.height},
                dest,
                (Vector2){0, 0}, 0.0f, WHITE
            );
        } else {
            DrawRectangleRec(dest, RED);
        }
        no = no->proximo;
    }
}

void desenharHUD(const Jogador *foliao, int nivel) {
    carregarTexturas();
    char pontos[32];
    snprintf(pontos, sizeof(pontos), "Pontos: %d", foliao->pontuacao);
    DrawText(pontos, 10, 10, 24, YELLOW);

    char nvl[32];
    snprintf(nvl, sizeof(nvl), "Nivel: %d", nivel);
    DrawText(nvl, 10, 38, 20, WHITE);

    int sz = 30;
    for (int i = 0; i < foliao->vidas; i++) {
        int x = LARGURA_TELA - (foliao->vidas - i) * (sz + 6);
        if (texVida.id != 0) {
            DrawTexturePro(
                texVida,
                (Rectangle){0, 0, (float)texVida.width, (float)texVida.height},
                (Rectangle){(float)x, 10, (float)sz, (float)sz},
                (Vector2){0, 0}, 0.0f, WHITE
            );
        } else {
            DrawText("V", x, 10, sz, RED);
        }
    }
}

void desenharGameOver(int pontuacao) {
    static int celebFrame = 0;
    static int celebTimer = 0;

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, (Color){0, 0, 0, 160});

    if (texFoliao.id != 0) {
        celebTimer++;
        if (celebTimer >= 8) {
            celebTimer = 0;
            celebFrame = (celebFrame + 1) % 4;
        }
        Rectangle src  = {celebFrame * 125.0f, 375.0f, 125.0f, 125.0f};
        Rectangle dest = {(float)(LARGURA_TELA / 2 - 60), 45.0f, 120.0f, 120.0f};
        DrawTexturePro(texFoliao, src, dest, (Vector2){0, 0}, 0.0f, WHITE);
    }

    const char *msg = "GAME OVER";
    DrawText(msg, LARGURA_TELA / 2 - MeasureText(msg, 64) / 2, 178, 64, RED);
    char pts[48];
    snprintf(pts, sizeof(pts), "Pontuacao final: %d", pontuacao);
    DrawText(pts, LARGURA_TELA / 2 - MeasureText(pts, 28) / 2, 258, 28, WHITE);
}
