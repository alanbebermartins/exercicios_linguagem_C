#include <stdio.h>
#include <stdlib.h>
#include "foge_foge.h"

struct mapa m;

// OBS: PRECISA TER O ARQUIVO TXT COM O DESENHO DO MAPA DO JOGO PARA FUNCIONAR

// Funções do jogo

void liberarmapa(){
    for (int i = 0; i < m.linhas; i++) {
        free(m.matriz[i]);
    }
    free(m.matriz);
}

void alocarmapa() {
    m.matriz = malloc(sizeof(char*) * m.linhas);
    for ( int i = 0; i < m.linhas; i++) {
        m.matriz[i] = malloc(sizeof(char) * (m.colunas + 1));
    }
}

void lermapa() {
    FILE* f;

    f = fopen("mapa.txt", "r");

    if(f == 0){
        printf("Desculpe, mas não foi possivel ler o mapa!\n");
        exit(1);
    }

    fscanf(f, "%d %d", &(m.linhas), &(m.colunas));

    alocarmapa();

    for( int i = 0; i < 5; i++){
        fscanf(f, "%s", m.matriz[i]);
    }

    fclose(f);
}

void imprimirmapa() {
    for( int i = 0; i < 5; i++){
        printf("%s\n", m.matriz[i]);
    }
}

int acabou() {
    return 0;
}

void move(char direcao) {
    int x;
    int y;

    // Acha a posição do avatar do foge foge
    for ( int i = 0; i < m.linhas; i++) {
        for ( int j = 0; j < m.colunas; j++) {
            if (m.matriz[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao) {
        case 'a':
            m.matriz[x][y-1] = '@';
            break;
        case 'w':
            m.matriz[x-1][y] = '@';
            break;
        case 's':
            m.matriz[x+1][y] = '@';
            break;
        case 'd':
            m.matriz[x][y+1] = '@';
            break;
    }

    m.matriz[x][y] = '.';
}

int main() {
    printf("**********************************\n");
    printf("* Bem vindo ao jogo do foge foge *\n");
    printf("**********************************\n\n");

    lermapa();

    do {
        imprimirmapa();

        char comando;
        scanf(" %c", &comando);
        move(comando);
        
    } while (!acabou());

    liberarmapa();
}