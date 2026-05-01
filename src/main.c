#include "raylib.h"

int main() {
    InitWindow(800, 450, "Meu primeiro jogo na Raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Parabens! Raylib funcionando!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}