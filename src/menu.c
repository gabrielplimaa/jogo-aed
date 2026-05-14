#include "raylib.h"
#include "menu.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

static const Color COR_TITULO     = { 255, 215,   0, 255 };
static const Color COR_SELECIONADO= { 255, 215,   0, 255 };
static const Color COR_NORMAL     = { 230, 230, 230, 255 };

static void desenharFundoMenu(Texture2D fundo) {
    if (fundo.id != 0) {
        DrawTexturePro(
            fundo,
            (Rectangle){0, 0, (float)fundo.width, (float)fundo.height},
            (Rectangle){0, 0, LARGURA_TELA, ALTURA_TELA},
            (Vector2){0, 0}, 0.0f, WHITE
        );
    }
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, (Color){0, 0, 0, 140});
}
void telaAbertura(void) {
    Texture2D logo = LoadTexture("sprites/tela_inicio.png"); 

    float escalaX = (float)LARGURA_TELA / logo.width;
    float escalaY = (float)ALTURA_TELA / logo.height;

    while (1) {
        if (IsKeyPressed(KEY_ENTER) || WindowShouldClose()) break;

        BeginDrawing();
        
            ClearBackground(BLACK);
            DrawTextureEx(logo, (Vector2){ 0, 0 }, 0.0f, escalaX > escalaY ? escalaX : escalaY, WHITE);
            
        EndDrawing();
    }

    UnloadTexture(logo);
}

OpcaoMenu exibirMenuPrincipal(void) {
    int opcaoAtual = 1;
    Texture2D fundo = LoadTexture("sprites/cenario.png");

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) { UnloadTexture(fundo); return MENU_SAIR; }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            opcaoAtual++;
            if (opcaoAtual > 3) opcaoAtual = 0;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            opcaoAtual--;
            if (opcaoAtual < 0) opcaoAtual = 3;
        }
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            UnloadTexture(fundo);
            return (OpcaoMenu)opcaoAtual;
        }

        if (IsKeyPressed(KEY_ONE))   { UnloadTexture(fundo); return MENU_JOGAR; }
        if (IsKeyPressed(KEY_TWO))   { UnloadTexture(fundo); return MENU_RANKING; }
        if (IsKeyPressed(KEY_THREE)) { UnloadTexture(fundo); return MENU_INSTRUCOES; }
        if (IsKeyPressed(KEY_ZERO))  { UnloadTexture(fundo); return MENU_SAIR; }

        BeginDrawing();
            desenharFundoMenu(fundo);

            const char *titulo = "PEGA O FREVO!";
            int tw = MeasureText(titulo, 58);
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2 + 2, 72, 58, (Color){120, 60, 0, 200});
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2,     70, 58, COR_TITULO);

            const char *subtitulo = "Carnaval Recifense";
            DrawText(subtitulo, LARGURA_TELA / 2 - MeasureText(subtitulo, 20) / 2, 138, 20, (Color){255, 180, 50, 255});

            DrawLine(LARGURA_TELA / 2 - 180, 168, LARGURA_TELA / 2 + 180, 168, (Color){255, 215, 0, 120});

            const char *opcoes[4] = { "Sair", "Jogar", "Ver Ranking", "Instrucoes" };
            int ordem[4] = {1, 2, 3, 0};

            for (int i = 0; i < 4; i++) {
                int   idx  = ordem[i];
                int   tam  = (idx == opcaoAtual) ? 30 : 24;
                Color cor  = (idx == opcaoAtual) ? COR_SELECIONADO : COR_NORMAL;
                int   posY = 190 + i * 58;
                int   posX = LARGURA_TELA / 2 - MeasureText(opcoes[idx], tam) / 2;

                if (idx == opcaoAtual) {
                    DrawRectangle(LARGURA_TELA / 2 - 155, posY - 6, 310, tam + 12, (Color){255, 215, 0, 30});
                    DrawRectangleLines(LARGURA_TELA / 2 - 155, posY - 6, 310, tam + 12, (Color){255, 215, 0, 100});
                    DrawText(">", LARGURA_TELA / 2 - 145, posY, tam, COR_SELECIONADO);
                }

                DrawText(opcoes[idx], posX, posY, tam, cor);
            }

            DrawText("Setas / WASD + ENTER para navegar",
                LARGURA_TELA / 2 - MeasureText("Setas / WASD + ENTER para navegar", 13) / 2,
                ALTURA_TELA - 28, 13, (Color){180, 180, 180, 180});
        EndDrawing();
    }
    UnloadTexture(fundo);
    return MENU_SAIR;
}

int telaEntradaNome(char *nomeDestino, int tamanhoMax) {
    char buffer[TAMANHO_NOME] = {0};
    int  cursor = 0;
    Texture2D fundo = LoadTexture("sprites/cenario.png");

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) { UnloadTexture(fundo); return 0; }

        for (int c = GetCharPressed(); c != 0; c = GetCharPressed()) {
            if (cursor < tamanhoMax - 1) {
                if ((c >= 'A' && c <= 'Z') ||
                    (c >= 'a' && c <= 'z') ||
                    (c >= '0' && c <= '9') ||
                     c == '_')
                {
                    buffer[cursor++] = (char)c;
                    buffer[cursor]   = '\0';
                }
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE) && cursor > 0)
            buffer[--cursor] = '\0';

        if (IsKeyPressed(KEY_ENTER) && cursor > 0) {
            strncpy(nomeDestino, buffer, tamanhoMax - 1);
            nomeDestino[tamanhoMax - 1] = '\0';
            UnloadTexture(fundo);
            return 1;
        }

        BeginDrawing();
            desenharFundoMenu(fundo);

            const char *titulo = "QUAL E O SEU NOME?";
            int tw = MeasureText(titulo, 36);
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2 + 2, 132, 36, (Color){120, 60, 0, 200});
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2,     130, 36, COR_TITULO);

            const char *sub = "Seu nome vai aparecer no ranking!";
            DrawText(sub, LARGURA_TELA / 2 - MeasureText(sub, 18) / 2, 180, 18, (Color){255, 180, 50, 255});

            DrawRectangle(LARGURA_TELA / 2 - 170, 235, 340, 50, (Color){0, 0, 0, 160});
            DrawRectangleLines(LARGURA_TELA / 2 - 170, 235, 340, 50, COR_TITULO);

            int piscar = (int)(GetTime() * 2.0) % 2;
            char exibido[TAMANHO_NOME + 2];
            snprintf(exibido, sizeof(exibido), "%s%s", buffer, piscar ? "_" : " ");
            DrawText(exibido, LARGURA_TELA / 2 - MeasureText(exibido, 26) / 2, 244, 26, COR_TITULO);

            DrawText("Letras, numeros e _ permitidos",
                LARGURA_TELA / 2 - MeasureText("Letras, numeros e _ permitidos", 13) / 2,
                300, 13, (Color){180, 180, 180, 200});

            DrawText("ENTER para jogar  |  ESC para voltar",
                LARGURA_TELA / 2 - MeasureText("ENTER para jogar  |  ESC para voltar", 14) / 2,
                ALTURA_TELA - 36, 14, (Color){180, 180, 180, 180});
        EndDrawing();
    }
    UnloadTexture(fundo);
    return 0;
}

void telaRanking(const Ranking *ranking) {
    Texture2D fundo = LoadTexture("sprites/cenario.jpeg");

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) { UnloadTexture(fundo); return; }

        BeginDrawing();
            desenharFundoMenu(fundo);

            const char *titulo = "RANKING - TOP 5";
            int tw = MeasureText(titulo, 38);
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2 + 2, 52, 38, (Color){120, 60, 0, 200});
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2,     50, 38, COR_TITULO);

            DrawLine(LARGURA_TELA / 2 - 200, 100, LARGURA_TELA / 2 + 200, 100, (Color){255, 215, 0, 100});

            if (ranking->total == 0) {
                const char *vazio = "Nenhuma pontuacao ainda. Seja o primeiro!";
                DrawText(vazio, LARGURA_TELA / 2 - MeasureText(vazio, 18) / 2, 250, 18, COR_NORMAL);
            } else {
                for (int i = 0; i < ranking->total; i++) {
                    char linha[64];
                    snprintf(linha, sizeof(linha), "%d.  %-20s  %d pts",
                             i + 1, ranking->entradas[i].nome, ranking->entradas[i].pontuacao);
                    Color cor = (i == 0) ? COR_TITULO : COR_NORMAL;
                    int tam   = (i == 0) ? 24 : 20;
                    DrawText(linha, LARGURA_TELA / 2 - MeasureText(linha, tam) / 2, 120 + i * 56, tam, cor);
                }
            }

            DrawText("ESC para voltar ao menu",
                LARGURA_TELA / 2 - MeasureText("ESC para voltar ao menu", 14) / 2,
                ALTURA_TELA - 36, 14, (Color){180, 180, 180, 180});
        EndDrawing();
    }
    UnloadTexture(fundo);
}

void telaInstrucoes(void) {
    Texture2D fundo = LoadTexture("sprites/cenario.jpeg");

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) { UnloadTexture(fundo); return; }

        BeginDrawing();
            desenharFundoMenu(fundo);

            const char *titulo = "INSTRUCOES";
            int tw = MeasureText(titulo, 38);
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2 + 2, 27, 38, (Color){120, 60, 0, 200});
            DrawText(titulo, LARGURA_TELA / 2 - tw / 2,     25, 38, COR_TITULO);

            DrawLine(LARGURA_TELA / 2 - 200, 73, LARGURA_TELA / 2 + 200, 73, (Color){255, 215, 0, 100});

            const char *linhas[] = {
                "SOBRE O JOGO:",
                "  Pega o Frevo e um arcade do Carnaval Recifense.",
                "  Controle um foliao e recolha os itens do frevo",
                "  antes que caiam no chao!",
                "",
                "CONTROLES:",
                "  Seta Esquerda / A   ->   mover para esquerda",
                "  Seta Direita  / D   ->   mover para direita",
                "",
                "ITENS E PONTUACAO:",
                "  Guarda-chuva de Frevo   ->   +10 pontos",
                "  Mascara Carnavalesca    ->   +20 pontos",
                "  Zabumba                 ->   +30 pontos",
                "",
                "VIDAS:",
                "  Voce comeca com 3 vidas.",
                "  Cada item no chao = -1 vida. Perca tudo = fim!",
                "",
                "NIVEL:",
                "  A cada 10 pontos o jogo fica mais rapido."
            };

            int total = (int)(sizeof(linhas) / sizeof(linhas[0]));
            for (int i = 0; i < total; i++) {
                Color cor = (linhas[i][0] != ' ' && linhas[i][0] != '\0')
                            ? COR_TITULO : COR_NORMAL;
                DrawText(linhas[i], 60, 84 + i * 22, 16, cor);
            }

            DrawText("ESC para voltar ao menu",
                LARGURA_TELA / 2 - MeasureText("ESC para voltar ao menu", 14) / 2,
                ALTURA_TELA - 28, 14, (Color){180, 180, 180, 180});
        EndDrawing();
    }
    UnloadTexture(fundo);
}
