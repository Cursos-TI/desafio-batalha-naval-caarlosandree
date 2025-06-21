/*
Autor: Carlos André Sabino
Nível: Mestre
Descrição:
  Tabuleiro de Batalha Naval 10x10 com 4 navios e 3 habilidades especiais:
    - Cone
    - Cruz
    - Octaedro (losango)
  As habilidades possuem áreas de efeito que são aplicadas sobre o tabuleiro,
  destacando visualmente suas regiões afetadas.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ──────────────────────────────────────────────
// Constantes
#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5

// ──────────────────────────────────────────────
// Verifica se a posição está dentro dos limites
static bool no_limite(int linha, int coluna) {
    return linha >= 0 && linha < TAM_TABULEIRO &&
           coluna >= 0 && coluna < TAM_TABULEIRO;
}

// ──────────────────────────────────────────────
// Função para posicionar navio
static bool pos_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                      int linha, int coluna, int step_linha, int step_coluna) {
    for (int i = 0; i < 3; i++) {
        int r = linha + i * step_linha;
        int c = coluna + i * step_coluna;
        if (!no_limite(r, c) || tabuleiro[r][c] != AGUA) {
            return false;
        }
    }
    for (int i = 0; i < 3; i++) {
        int r = linha + i * step_linha;
        int c = coluna + i * step_coluna;
        tabuleiro[r][c] = NAVIO;
    }
    return true;
}

// ──────────────────────────────────────────────
// Gera matriz Cone (↧)
void gerar_cone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE / 2) - i && j <= (TAM_HABILIDADE / 2) + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// ──────────────────────────────────────────────
// Gera matriz Cruz
void gerar_cruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// ──────────────────────────────────────────────
// Gera matriz Octaedro (losango)
void gerar_octaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// ──────────────────────────────────────────────
// Aplica a matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                         int matriz[TAM_HABILIDADE][TAM_HABILIDADE],
                         int origem_linha, int origem_coluna) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int r = origem_linha + (i - centro);
                int c = origem_coluna + (j - centro);
                if (no_limite(r, c) && tabuleiro[r][c] == AGUA) {
                    tabuleiro[r][c] = AREA_HABILIDADE;
                }
            }
        }
    }
}

// ──────────────────────────────────────────────
// Exibe o tabuleiro com representação visual
void exibir_tabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    puts("===============================");
    puts("      BATALHA NAVAL PRO MAX    ");
    puts("===============================");
    printf("   ");
    for (int c = 0; c < TAM_TABULEIRO; c++) printf("%d ", c);
    printf("\n");

    for (int r = 0; r < TAM_TABULEIRO; r++) {
        printf("%2d ", r);
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            switch (tabuleiro[r][c]) {
                case AGUA: printf("~ "); break;
                case NAVIO: printf("N "); break;
                case AREA_HABILIDADE: printf("* "); break;
                default: printf("? "); break;
            }
        }
        printf("\n");
    }
}

// ──────────────────────────────────────────────
// MAIN
int main() {
    // Inicializa tabuleiro com água
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    for (int r = 0; r < TAM_TABULEIRO; r++) {
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            tabuleiro[r][c] = AGUA;
        }
    }

    // Posiciona navios
    struct { int r, c, dr, dc; } navios[] = {
        {7, 2, 0, 1},    // Horizontal
        {0, 7, 1, 0},    // Vertical
        {1, 1, 1, 1},    // Diagonal ↘
        {6, 3, -1, 1}    // Diagonal ↗
    };

    for (int i = 0; i < 4; i++) {
        if (!pos_navio(tabuleiro, navios[i].r, navios[i].c, navios[i].dr, navios[i].dc)) {
            printf("Erro ao posicionar navio %d.\n", i + 1);
            return 1;
        }
    }

    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    gerar_cone(cone);
    gerar_cruz(cruz);
    gerar_octaedro(octaedro);

    // Define pontos de origem das habilidades no tabuleiro
    aplicar_habilidade(tabuleiro, cone, 2, 2);
    aplicar_habilidade(tabuleiro, cruz, 5, 5);
    aplicar_habilidade(tabuleiro, octaedro, 8, 8);

    // Exibe o tabuleiro completo
    exibir_tabuleiro(tabuleiro);

    return 0;
}
