#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Inicializa tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Verifica se está dentro dos limites
int dentroDoLimite(int linha, int coluna) {
    return (linha >= 0 && linha < TAM_TABULEIRO &&
            coluna >= 0 && coluna < TAM_TABULEIRO);
}

// Posiciona navio com validação
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                     int linha, int coluna,
                     int dirLinha, int dirColuna) {

    // Verifica se pode posicionar
    for (int i = 0; i < TAM_NAVIO; i++) {
        int novaLinha = linha + i * dirLinha;
        int novaColuna = coluna + i * dirColuna;

        if (!dentroDoLimite(novaLinha, novaColuna) ||
            tabuleiro[novaLinha][novaColuna] != 0) {
            return 0; // inválido
        }
    }

    // Posiciona
    for (int i = 0; i < TAM_NAVIO; i++) {
        int novaLinha = linha + i * dirLinha;
        int novaColuna = coluna + i * dirColuna;
        tabuleiro[novaLinha][novaColuna] = 3;
    }

    return 1;
}

// Cone (expandindo para baixo)
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (j >= centro - i && j <= centro + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cruz
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (i == centro || j == centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Octaedro (losango)
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (abs(i - centro) + abs(j - centro) <= centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Aplica habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {

    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {

            if (habilidade[i][j] == 1) {

                int linhaTab = origemLinha + (i - centro);
                int colunaTab = origemColuna + (j - centro);

                if (dentroDoLimite(linhaTab, colunaTab) &&
                    tabuleiro[linhaTab][colunaTab] == 0) {

                    tabuleiro[linhaTab][colunaTab] = 5;
                }
            }
        }
    }
}

// Exibe tabuleiro SOMENTE EM NÚMEROS
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {

    printf("\n===== TABULEIRO =====\n\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {

    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // ===== NAVIOS =====
    posicionarNavio(tabuleiro, 1, 1, 0, 1);   // Horizontal
    posicionarNavio(tabuleiro, 5, 2, 1, 0);   // Vertical
    posicionarNavio(tabuleiro, 0, 7, 1, 1);   // Diagonal principal
    posicionarNavio(tabuleiro, 6, 9, 1, -1);  // Diagonal secundária

    // ===== HABILIDADES =====
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 2, 2);
    aplicarHabilidade(tabuleiro, cruz, 7, 3);
    aplicarHabilidade(tabuleiro, octaedro, 4, 7);

    exibirTabuleiro(tabuleiro);

    return 0;
}
