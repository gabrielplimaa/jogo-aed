#include "raylib.h"
#include "menu.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

static const Color COR_SELECIONADO = { 255, 215, 0,   255 };
static const Color COR_NORMAL      = { 200, 200, 200, 255 };
static const Color COR_FUNDO_MENU  = { 20,  10,  50,  255 };

OpcaoMenu exibirMenuPrincipal(void) {
    int opcaoAtual = 1;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) return MENU_SAIR;

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            opcaoAtual++;
            if (opcaoAtual > 3) opcaoAtual = 0;
        }
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            opcaoAtual--;
            if (opcaoAtual < 0) opcaoAtual = 3;
        }
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
            return (OpcaoMenu)opcaoAtual;

        if (IsKeyPressed(KEY_ONE))   return MENU_JOGAR;
        if (IsKeyPressed(KEY_TWO))   return MENU_RANKING;
        if (IsKeyPressed(KEY_THREE)) return MENU_INSTRUCOES;
        if (IsKeyPressed(KEY_ZERO))  return MENU_SAIR;

        BeginDrawing();
            ClearBackground(COR_FUNDO_MENU);

            const char *titulo = "PEGA O FREVO!";
            DrawText(titulo, LARGURA_TELA / 2 - MeasureText(titulo, 52) / 2, 80, 52, COR_SELECIONADO);

            const char *subtitulo = "Carnaval Recifense";
            DrawText(subtitulo, LARGURA_TELA / 2 - MeasureText(subtitulo, 20) / 2, 142, 20, (Color){ 255, 150, 0, 255 });

            const char *opcoes[4] = { "0. Sair", "1. Jogar", "2. Ver Ranking", "3. Instrucoes" };
            int ordem[4] = {1, 2, 3, 0};

            for (int i = 0; i < 4; i++) {
                int   idx = ordem[i];
                Color cor = (idx == opcaoAtual) ? COR_SELECIONADO : COR_NORMAL;
                int   tam = (idx == opcaoAtual) ? 28 : 24;

                if (idx == opcaoAtual)
                    DrawText(">", LARGURA_TELA / 2 - 160, 220 + i * 55, 28, COR_SELECIONADO);

                DrawText(opcoes[idx], LARGURA_TELA / 2 - MeasureText(opcoes[idx], tam) / 2, 220 + i * 55, tam, cor);
            }

            DrawText("Use Setas / WASD + ENTER para navegar", LARGURA_TELA / 2 - MeasureText("Use Setas / WASD + ENTER para navegar", 14) / 2, ALTURA_TELA - 30, 14, DARKGRAY);
        EndDrawing();
    }
    return MENU_SAIR;
}

int telaEntradaNome(char *nomeDestino, int tamanhoMax) {
    char buffer[TAMANHO_NOME] = {0};
    int  cursor = 0;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) return 0;

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

        /* ENTER com nome preenchido inicia o jogo */
        if (IsKeyPressed(KEY_ENTER) && cursor > 0) {
            strncpy(nomeDestino, buffer, tamanhoMax - 1);
            nomeDestino[tamanhoMax - 1] = '\0';
            return 1;
        }

        BeginDrawing();
            ClearBackground(COR_FUNDO_MENU);

            const char *titulo = "QUAL E O SEU NOME?";
            DrawText(titulo, LARGURA_TELA / 2 - MeasureText(titulo, 34) / 2, 140, 34, COR_SELECIONADO);

            const char *sub = "Seu nome aparecera no ranking!";
            DrawText(sub, LARGURA_TELA / 2 - MeasureText(sub, 18) / 2, 190, 18, (Color){ 255, 150, 0, 255 });

            DrawRectangle(LARGURA_TELA / 2 - 160, 270, 320, 44, (Color){ 255, 255, 255, 30 });
            DrawRectangleLines(LARGURA_TELA / 2 - 160, 270, 320, 44, YELLOW);

            int  piscar = (int)(GetTime() * 2.0) % 2;
            char exibido[TAMANHO_NOME + 2];
            snprintf(exibido, sizeof(exibido), "%s%s",
                     buffer, piscar ? "_" : " ");

            DrawText(exibido, LARGURA_TELA / 2 - MeasureText(exibido, 24) / 2, 278, 24, YELLOW);

            DrawText("Letras, numeros e _ permitidos", LARGURA_TELA / 2 - MeasureText("Letras, numeros e _ permitidos", 13) / 2, 328, 13, DARKGRAY);

            DrawText("ENTER para jogar  |  ESC ou TAB para voltar", LARGURA_TELA / 2 - MeasureText("ENTER para jogar  |  ESC ou TAB para voltar", 14) / 2, ALTURA_TELA - 40, 14, DARKGRAY);
        EndDrawing();
    }
    return 0;
}

void telaRanking(const Ranking *ranking) {
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) return;

        BeginDrawing();
            ClearBackground(COR_FUNDO_MENU);

            const char *titulo = "RANKING - TOP 5";
            DrawText(titulo, LARGURA_TELA / 2 - MeasureText(titulo, 36) / 2, 60, 36, COR_SELECIONADO);

            if (ranking->total == 0) {
                const char *vazio = "Nenhuma pontuacao ainda. Seja o primeiro!";
                DrawText(vazio, LARGURA_TELA / 2 - MeasureText(vazio, 18) / 2, 250, 18, COR_NORMAL);
            } else {
                for (int i = 0; i < ranking->total; i++) {
                    char linha[64];
                    snprintf(linha, sizeof(linha), "%d.  %-20s  %d pts", i + 1, ranking->entradas[i].nome, ranking->entradas[i].pontuacao);

                    Color cor = (i == 0) ? COR_SELECIONADO : COR_NORMAL;
                    DrawText(linha, LARGURA_TELA / 2 - MeasureText(linha, 22) / 2, 140 + i * 60, 22, cor);
                }
            }

            DrawText("ESC ou TAB para voltar ao menu", LARGURA_TELA / 2 - MeasureText("ESC ou TAB para voltar ao menu", 14) / 2, ALTURA_TELA - 40, 14, DARKGRAY);
        EndDrawing();
    }
}

void telaInstrucoes(void) {
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) return;

        BeginDrawing();
            ClearBackground(COR_FUNDO_MENU);

            const char *titulo = "INSTRUCOES";
            DrawText(titulo, LARGURA_TELA / 2 - MeasureText(titulo, 36) / 2, 30, 36, COR_SELECIONADO);

            const char *linhas[] = {
                "SOBRE O JOGO:",
                "  Pega o Frevo e um arcade do Carnaval Recifense.",
                "  Controle um foliao e recolha os itens tipicos do frevo",
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
                "  Cada item que tocar o chao sem ser pego = -1 vida.",
                "  Perca todas as vidas e o jogo termina!",
                "",
                "NIVEL:",
                "  A cada 10 pontos o jogo fica mais rapido.",
                "  Quanto maior o nivel, maior o desafio!"
            };

            int total = (int)(sizeof(linhas) / sizeof(linhas[0]));
            for (int i = 0; i < total; i++) {
                Color cor = (linhas[i][0] != ' ' && linhas[i][0] != '\0') ? COR_SELECIONADO : COR_NORMAL;
                DrawText(linhas[i], 55, 82 + i * 22, 16, cor);
            }

            DrawText("ESC ou TAB para voltar ao menu", LARGURA_TELA / 2 - MeasureText("ESC ou TAB para voltar ao menu", 14) / 2, ALTURA_TELA - 30, 14, DARKGRAY);
        EndDrawing();
    }
}
