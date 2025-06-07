/*
Autor: Carlos André Sabino
Nível: Novato
Descrição:
Este programa simula um jogo de Batalha Naval.
*/

#include <stdio.h>

//Definindo o tamanho
#define tamanho_tabuleiro 10
#define tamanho_navio 3

int main() {
    // Declaração do tabuleiro (0)
    int tabuleiro[tamanho_tabuleiro][tamanho_tabuleiro] = {0};

    //Declaração dos navios (3)
    int navio_hor[tamanho_navio] = {3,3,3};
    int navio_ver[tamanho_navio] = {3,3,3};

    // Coordenadas iniciais dos navios
    int linha_hor = 7, coluna_hor = 2;
    int linha_ver = 0, coluna_ver = 7;

    // Verificação de limites
    if (linha_ver + tamanho_navio > tamanho_tabuleiro || coluna_hor + tamanho_navio > tamanho_tabuleiro) {
        printf("Erro: fora dos limites do tabuleiro.\n");
        return 1;
    }

    // Verifica sobreposição para navio vertical
    for (int i = 0; i < tamanho_navio; i++) {
        if (tabuleiro[linha_ver + i][coluna_ver] != 0) {
            printf("Erro: sobreposição detectada no navio vertical.\n");
            return 1;
        }
    }

    // Posiciona o navio vertical
    for (int i = 0; i < tamanho_navio; i++) {
        tabuleiro[linha_ver + i][coluna_ver] = navio_ver[i];
    }

    // Verifica sobreposição para navio horizontal
    for (int i = 0; i < tamanho_navio; i++) {
        if (tabuleiro[linha_hor][coluna_hor + i] != 0) {
            printf("Erro: sobreposição detectada no navio horizontal.\n");
            return 1;
        }
    }

    // Posiciona o navio horizontal
    for (int i = 0; i < tamanho_navio; i++) {
        tabuleiro[linha_hor][coluna_hor + i] = navio_hor[i];
    }

    // Exibe o tabuleiro
    printf("============================\n");
    printf(" Tabuleiro de Batalha Naval\n");
    printf("============================\n");
    for (int i = 0; i < tamanho_tabuleiro; i++) {
        for (int j = 0; j < tamanho_tabuleiro; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
