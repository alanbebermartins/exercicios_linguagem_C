#include <stdio.h>
#include <stdlib.h>
#include "foge_foge.h"

MAPA m;
POSICAO avatar;

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

void encontramapa(MAPA* m, POSICAO* p, char c) {
    for ( int i = 0; i < m->linhas; i++) {
        for ( int j = 0; j < m->colunas; j++) {
            if (m->matriz[i][j] == c) {
                p->x = i;
                p->y = j;
                break;
            }
        }
    }
}

void move(char direcao) {
    int x;
    int y;

    m.matriz[avatar.x][avatar.y] = '.';

    switch (direcao) {
        case 'a':
            m.matriz[avatar.x][avatar.y-1] = '@';
            avatar.y--;
            break;
        case 'w':
            m.matriz[avatar.x-1][avatar.y] = '@';
            avatar.x--;
            break;
        case 's':
            m.matriz[avatar.x+1][avatar.y] = '@';
            avatar.x++;
            break;
        case 'd':
            m.matriz[avatar.x][avatar.y+1] = '@';
            avatar.y++;
            break;
    }

    
}

int main() {
    printf("**********************************\n");
    printf("* Bem vindo ao jogo do foge foge *\n");
    printf("**********************************\n\n");

    lermapa();
    encontramapa(&m, &avatar, '@');

    do {
        imprimirmapa();
        char comando;
        scanf(" %c", &comando);
        move(comando);
        
    } while (!acabou());

    liberarmapa();
}