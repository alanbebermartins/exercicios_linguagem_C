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

int ehdirecao(char direcao) {
    return direcao == ESQUERDA || direcao == CIMA || direcao == BAIXO || direcao == DIREITA;
}

int ehvalida(MAPA* m, int x, int y) {
    if (x >= m->linhas) 
        return 0;
    if (y >= m->colunas) 
        return 0;

    return 1;
}

int ehvazia(MAPA* m, int x, int y) {
    return m->matriz[x][y] == VAZIO;
}

void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino) {
    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = VAZIO;
}

void move(char direcao) {

    if (!ehdirecao(direcao)) 
    return;

    int proximox = avatar.x;
    int proximoy = avatar.y;

    switch (direcao) {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
    }

    if (!ehvalida(&m, proximox, proximoy))
        return;
    if (!ehvazia(&m, proximox, proximoy))
        return;
    
    andanomapa(&m, avatar.x, avatar.y, proximox, proximoy);
    avatar.x = proximox;
    avatar.y = proximoy;
}

int main() {
    printf("**********************************\n");
    printf("* Bem vindo ao jogo do foge foge *\n");
    printf("**********************************\n\n");

    lermapa();
    encontramapa(&m, &avatar, AVATAR);

    do {
        imprimirmapa();
        char comando;
        scanf(" %c", &comando);
        move(comando);
        
    } while (!acabou());

    liberarmapa();
}