#include <stdio.h>
#include <stdlib.h>

// OBS: PRECISA TER O ARQUIVO TXT COM O DESENHO DO MAPA DO JOGO PARA FUNCIONAR
// Variáveis globais
char** mapa;
int linhas;
int colunas;

// Lista das funções do jogo
void liberarmapa();
void alocarmapa();
void lermapa();

// Funções do jogo

void liberarmapa(){
    for (int i = 0; i < linhas; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void alocarmapa() {
    mapa = malloc(sizeof(char*) * linhas);
    for ( int i = 0; i < linhas; i++) {
        mapa[i] = malloc(sizeof(char) * (colunas + 1));
    }
}

void lermapa() {
    FILE* f;

    f = fopen("mapa.txt", "r");

    if(f == 0){
        printf("Desculpe, mas não foi possivel ler o mapa!\n");
        exit(1);
    }

    fscanf(f, "%d %d", &linhas, &colunas);

    alocarmapa();

    for( int i = 0; i < 5; i++){
        fscanf(f, "%s", mapa[i]);
    }

    fclose(f);
}

void imprimirmapa() {
    for( int i = 0; i < 5; i++){
        printf("%s\n", mapa[i]);
    }
}

int acabou() {
    return 0;
}

void move(char direcao) {
    int x;
    int y;

    // Acha a posição do avatar do foge foge
    for ( int i = 0; i < linhas; i++) {
        for ( int j = 0; j < colunas; j++) {
            if (mapa[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao) {
        case 'a':
            mapa[x][y-1] = '@';
            break;
        case 'w':
            mapa[x-1][y] = '@';
            break;
        case 's':
            mapa[x+1][y] = '@';
            break;
        case 'd':
            mapa[x][y+1] = '@';
            break;
    }

    mapa[x][y] = '.';
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