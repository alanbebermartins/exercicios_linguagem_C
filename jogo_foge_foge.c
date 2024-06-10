#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "foge_foge.h"

// Variaveis para renderizar os personagens

char desenhofantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenhoparede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenhoheroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenhopilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenhovazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

MAPA m;
POSICAO avatar;
int tempilula = 0;
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
        {xatual, yatual+1}, 
        {xatual+1, yatual}, 
        {xatual, yatual-1}, 
        {xatual-1, yatual}
    };
    srand(time(0));
    for(int i = 0; i < 10; i++) {
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
    for (int i = 0; i < copia.linhas; i++) {
        for (int j = 0; j < copia.colunas; j++) {
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

void liberarmapa(MAPA* m){
    for (int i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }
    free(m->matriz);
}

void alocarmapa(MAPA* m) {
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for (int i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

void lermapa(MAPA* m) {
    FILE* f;
    f = fopen("mapa.txt", "r");
    if(f == 0){
        printf("Desculpe, mas não foi possivel ler o mapa!\n");
        exit(1);
    }
    fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
    alocarmapa(m);
    for(int i = 0; i < m->linhas; i++){
        fscanf(f, "%s", m->matriz[i]);
    }
    fclose(f);
}

void imprimeparte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

void imprimirmapa(MAPA* m) {
    for( int i = 0; i < m->linhas; i++){

        for(int parte = 0; parte < 4; parte++) {

            for(int j = 0; j < m->colunas; j++) {

                switch(m->matriz[i][j]) {
                    case FANTASMA:
                        imprimeparte(desenhofantasma, parte);
                        break;
                    case AVATAR:
                        imprimeparte(desenhoheroi, parte);
                        break;
                    case PILULA:
                        imprimeparte(desenhopilula, parte);
                        break;
                    case PAREDE_HORIZONTAL:
                    case PAREDE_VERTICAL:
                        imprimeparte(desenhoparede, parte);
                        break;
                    case VAZIO:
                        imprimeparte(desenhovazio, parte);
                        break;
                }
            }
            printf("\n");
        }
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
    if(x >= m->linhas) 
        return 0;
    if(y >= m->colunas) 
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

    int proximox = avatar.x;
    int proximoy = avatar.y;

    switch(direcao) {
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

    if(ehumpersonagem(&m, PILULA, proximox, proximoy)) {
        tempilula = 1;
    }
    
    andanomapa(&m, avatar.x, avatar.y, proximox, proximoy);
    avatar.x = proximox;
    avatar.y = proximoy;
}

void explodepilula() {

    if(!tempilula) return;
    explodepilula2(avatar.x, avatar.y, 0, 1, 3);
    explodepilula2(avatar.x, avatar.y, 0, -1, 3);
    explodepilula2(avatar.x, avatar.y, 1, 0, 3);
    explodepilula2(avatar.x, avatar.y, -1, 0, 3);
    tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {

    if(qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if(!ehvalida(&m, novox, novoy)) return;
    if(ehparede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] == VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd-1);
}

int main() {
    printf("**********************************\n");
    printf("* Bem vindo ao jogo do foge foge *\n");
    printf("**********************************\n\n");
    lermapa(&m);
    encontramapa(&m, &avatar, AVATAR);
    do {

        printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NÃO"));
        imprimirmapa(&m);

        char comando;
        scanf(" %c", &comando);

        if(ehdirecao(comando)) move(comando);
        if(comando == BOMBA) explodepilula();
        
        fantasmas();
    } while (!acabou());
    liberarmapa(&m);
}