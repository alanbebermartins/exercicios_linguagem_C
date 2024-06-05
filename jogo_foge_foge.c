#include <stdio.h>
#include <stdlib.h>

// OBS: PRECISA TER O ARQUIVO TXT COM O DESENHO DO MAPA DO JOGO PARA FUNCIONAR
// Variáveis globais
char mapa[5][10+1];
int linhas;
int colunas;

int main() {
    printf("**********************************\n");
    printf("* Bem vindo ao jogo do foge foge *\n");
    printf("**********************************\n\n");

    FILE* f;

    f = fopen("mapa.txt", "r");

    if(f == 0){
        printf("Desculpe, mas não foi possivel ler o mapa!\n");
        exit(1);
    }

    for( int i = 0; i < 5; i++){
        fscanf(f, "%s", mapa[i]);
    }

    for( int i = 0; i < 5; i++){
        printf("%s\n", mapa[i]);
    }

    fclose(f);

    // mapa[0][0] = '|';
    // mapa[4][9] = '@';

    // printf("%c %c\n", mapa[0][0], mapa[4][9]);
}