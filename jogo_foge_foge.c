#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "foge_foge.h"

MAPA m;
POSICAO avatar;
// OBS: PRECISA TER O ARQUIVO TXT COM O DESENHO DO MAPA DO JOGO PARA FUNCIONAR
// Funções do jogo

void copiamapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;
    alocarmapa(destino);
    for (int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

int paraondevaiofantasma(int xatual, int yatual, int* xdestino, int* ydestino) {
    int opcoes[4][2] = {
        {xatual, yatual+1}, {xatual+1, yatual}, {xatual, yatual-1}, {xatual-1, yatual}
    };
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;
        if (podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}

void fantasmas() {
    MAPA copia;
    copiamapa(&copia, &m);
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            if (copia.matriz[i][j] == FANTASMA) {
                int xdestino;
                int ydestino;
                int encontrou = paraondevaiofantasma(i, j, &xdestino, &ydestino);
                if(encontrou) {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }
        }
    }
    liberarmapa(&copia);
}

int ehparede(MAPA* m, int x, int y) {
    return m->matriz[x][y] == PAREDE_VERTICAL || m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int ehumpersonagem(MAPA* m, char personagem, int x, int y) {
    return m->matriz[x][y] == personagem;
}

int podeandar(MAPA* m, char personagem, int x, int y) {
    return ehvalida(m, x, y) && !ehparede(m, x, y) && !ehumpersonagem(m, personagem, x, y);
}

void liberarmapa(){
    for (int i = 0; i < m.linhas; i++) {
        free(m.matriz[i]);
    }
    free(m.matriz);
}

void alocarmapa() {
    m.matriz = malloc(sizeof(char*) * m.linhas);
    for (int i = 0; i < m.linhas; i++) {
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
    POSICAO position; 
    int fogefogenomapa = encontramapa(&m, &position, AVATAR);
    return !fogefogenomapa;
}

int encontramapa(MAPA* m, POSICAO* p, char c) {
    for ( int i = 0; i < m->linhas; i++) {
        for ( int j = 0; j < m->colunas; j++) {
            if (m->matriz[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
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

    if (!podeandar(&m, AVATAR, proximox, proximoy))
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
        fantasmas();
    } while (!acabou());
    liberarmapa();
}