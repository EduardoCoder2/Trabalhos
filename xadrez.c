#include <stdio.h>


void moverTorre(int casas) {
    if (casas <= 0) {
        return; 
    }

    printf("Direita\n");
    moverTorre(casas - 1); 
}


void moverRainha(int casas) {
    if (casas <= 0) {
        return; 
    }

    printf("Esquerda\n");
    moverRainha(casas - 1);
}

void moverBispo(int casas) {

    if (casas <= 0) {
        return; 
    }

    
    for (int vertical = 0; vertical < 1; vertical++) {

        
        for (int horizontal = 0; horizontal < 1; horizontal++) {

            printf("Cima\n");
            printf("Direita\n");
        }
    }

    moverBispo(casas - 1); 
}

void moverCavalo() {

    int movimentoVertical = 2;
    int movimentoHorizontal = 1;

   
    for (int i = 0; i < movimentoVertical; i++) {

        printf("Cima\n");

        
        if (i == 1) {
            continue; 
        }
    }

    
    int j = 0;
    while (j < movimentoHorizontal) {

        printf("Direita\n");

        if (j == 0) {
            j++;
            break; 
        }
    }
}


int main() {

    int casasTorre = 5;
    int casasBispo = 5;
    int casasRainha = 8;

    printf("Movimento da Torre:\n");
    moverTorre(casasTorre);

    printf("\nMovimento do Bispo:\n");
    moverBispo(casasBispo);

    printf("\nMovimento da Rainha:\n");
    moverRainha(casasRainha);

    printf("\nMovimento do Cavalo:\n");
    moverCavalo();

    return 0;
}