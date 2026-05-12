# Pega o Frevo!

Trabalho prático da disciplina de Algoritmos e Estruturas de Dados — Tema: Na Vibe do Recife (Frevo / Carnaval Recifense).

## Sobre o jogo

Jogo arcade carnavalesco onde você controla um **folião** que se move horizontalmente na base da tela e deve pegar objetos que caem do céu:

| Objeto | Símbolo | Pontos |
|--------|---------|--------|
| Guarda-chuva de frevo | `UCH` | +10 |
| Máscara carnavalesca  | `MSK` | +20 |
| Zabumba               | `ZAB` | +30 |

- Você tem **3 vidas**. Cada objeto que cair sem ser pego custa uma vida.
- A velocidade aumenta a cada **10 pontos** coletados.
- Ao perder todas as vidas, seu nome entra no **ranking dos 5 melhores**.

## Pré-requisitos

- WSL (Windows Subsystem for Linux) com Ubuntu 24.04
- Raylib instalada no WSL em `/usr/local/lib/libraylib.a`
- GCC disponível no WSL

Para instalar o Raylib no WSL (caso ainda não esteja):
```bash
sudo apt install libraylib-dev
# ou compilar da fonte:
# https://github.com/raysan5/raylib
```

## Como compilar

```bash
# No terminal do WSL, dentro da pasta do projeto:
make
```

O binário será gerado em `build/pega-o-frevo`.

## Como rodar

```bash
 # ou diretamente:
./build/pega-o-frevo
```

## Como jogar

- **Setas Esquerda/Direita** ou **A/D** — move o folião
- **Setas Cima/Baixo** ou **W/S** — navega no menu
- **ENTER / ESPAÇO** — confirma seleção
- **ESC** — volta ao menu anterior

## Estrutura do projeto

```
Pega-o-Frevo/
├── src/
│   ├── main.c        # Entrada do programa e loop do menu
│   ├── jogo.c        # Loop principal da partida
│   ├── lista.c       # Lista encadeada (objetos caindo)
│   ├── objeto.c      # Tipos e pontuação dos objetos
│   ├── jogador.c     # Lógica e desenho do folião
│   ├── ranking.c     # Ranking com persistência em disco
│   ├── ordenacao.c   # Insertion Sort
│   ├── interface.c   # Desenho do fundo, HUD e objetos
│   └── menu.c        # Telas de menu, ranking e instruções
├── include/
│   ├── config.h      # Constantes globais do jogo
│   ├── objeto.h
│   ├── lista.h
│   ├── jogador.h
│   ├── ranking.h
│   ├── ordenacao.h
│   ├── jogo.h
│   ├── menu.h
│   └── interface.h
├── data/
│   └── ranking.txt   # Ranking persistido entre sessões
├── build/            # Binário gerado pelo make
└── Makefile
```

## Estruturas de dados implementadas

### Lista Encadeada (`lista.c` / `lista.h`)
Armazena os objetos que estão caindo em tempo real. Funções implementadas:
- `inserirObjeto()` — insere novo objeto no início da lista
- `removerObjeto()` — remove nó específico liberando memória
- `moverObjetos()` — atualiza posição Y de todos os objetos
- `detectarColisao()` — verifica AABB entre folião e cada objeto
- `contarObjetos()` — retorna o tamanho atual da lista
- `limparLista()` — libera toda a memória da lista

### Insertion Sort (`ordenacao.c` / `ordenacao.h`)
Ordena o ranking em ordem decrescente de pontuação a cada nova entrada.

## Referências

- [Raylib](https://www.raylib.com/) — biblioteca gráfica
- [Frevo](https://pt.wikipedia.org/wiki/Frevo) — ritmo e cultura do Carnaval Recifense
