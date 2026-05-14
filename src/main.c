#include "raylib.h"
#include "config.h"
#include "jogo.h"
#include "menu.h"
#include "ranking.h"

int main(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, TITULO_JANELA);
    SetTargetFPS(FPS_ALVO);
    telaAbertura();

    while (IsKeyDown(KEY_ENTER)) {
        BeginDrawing();
        EndDrawing();
    }
    
    Ranking ranking;
    carregarRanking(&ranking, CAMINHO_RANKING);

    while (!WindowShouldClose()) {
        OpcaoMenu opcao = exibirMenuPrincipal();

        if (opcao == MENU_SAIR) break;

        if (opcao == MENU_JOGAR) {
            char nome[TAMANHO_NOME] = {0};
            int confirmou = telaEntradaNome(nome, TAMANHO_NOME);
            if (!confirmou) continue;

            EstadoJogo estado;
            inicializarJogo(&estado, &ranking, nome);
            executarJogo(&estado);
            encerrarJogo(&estado);
        }
        else if (opcao == MENU_RANKING)    telaRanking(&ranking);
        else if (opcao == MENU_INSTRUCOES) telaInstrucoes();
    }

    CloseWindow();
    return 0;
}
