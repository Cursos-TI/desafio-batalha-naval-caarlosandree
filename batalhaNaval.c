/*
Autor: Carlos André Sabino
Desafio: Nível Aventureiro
Descrição:
  Simula a preparação de um tabuleiro de Batalha Naval 10×10.
  Posiciona quatro navios de tamanho 3:
    ─ 1 horizontal
    ─ 1 vertical
    ─ 2 diagonais (↘ e ↗)
  Valida limites e sobreposição.
  Exibe o tabuleiro resultante no console.
*/

#include <stdio.h>
#include <stdbool.h>

// Constantes
#define borda_tabuleiro 10
#define tamanho_navio 3
#define agua 0
#define parte_navio 3

// Função para verificar se a posição está dentro dos limites
static bool no_limite(int linha, int coluna) {
    return linha >= 0 && linha < borda_tabuleiro && coluna >= 0 && coluna < borda_tabuleiro;
}

// Função para posicionar navios
static bool pos_navio(int borda[borda_tabuleiro][borda_tabuleiro],
                      int init_linha, int init_coluna,
                      int step_linha, int step_coluna) {
    // Verificar limites e colisões
    for (int i = 0; i < tamanho_navio; i++) {
        int r = init_linha + i * step_linha;
        int c = init_coluna + i * step_coluna;

        if (!no_limite(r, c) || borda[r][c] != agua) {
            return false;
        }
    }

    // Posicionar o navio
    for (int i = 0; i < tamanho_navio; i++) {
        int r = init_linha + i * step_linha;
        int c = init_coluna + i * step_coluna;
        borda[r][c] = parte_navio;
    }
    return true;
}

int main(void) {
    // Inicializa o tabuleiro com água (0)
    int borda[borda_tabuleiro][borda_tabuleiro];
    for (int r = 0; r < borda_tabuleiro; ++r) {
        for (int c = 0; c < borda_tabuleiro; ++c) {
            borda[r][c] = agua;
        }
    }

    // Lista de navios
    struct {
        int r, c;   // Coordenada inicial
        int dr, dc; // Direção
    } navios[] = {
        {7, 2, 0, 1},   // Horizontal
        {0, 7, 1, 0},   // Vertical
        {1, 1, 1, 1},   // Diagonal ↘
        {6, 3, -1, 1}   // Diagonal ↗
    };

    // Posiciona cada navio
    for (size_t i = 0; i < sizeof(navios) / sizeof(navios[0]); ++i) {
        if (!pos_navio(borda, navios[i].r, navios[i].c, navios[i].dr, navios[i].dc)) {
            printf("Erro: impossível posicionar o navio %zu.\n", i + 1);
            return 1;
        }
    }

    // Exibe o tabuleiro
    puts("============================");
    puts("   Tabuleiro Batalha Naval  ");
    puts("============================");
    for (int r = 0; r < borda_tabuleiro; ++r) {
        for (int c = 0; c < borda_tabuleiro; ++c) {
            printf("%d ", borda[r][c]);
        }
        putchar('\n');
    }

    return 0;
}
