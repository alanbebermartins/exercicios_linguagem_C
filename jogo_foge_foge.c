#include <stdio.h>
#include <stdlib.h>

// OBS: PRECISA TER O ARQUIVO TXT COM O DESENHO DO MAPA DO JOGO PARA FUNCIONAR
// Variáveis globais
char** mapa;
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

    fscanf(f, "%d %d", &linhas, &colunas);
    printf("Linhas %d e Colunas %d\n\n", linhas, colunas);

    mapa = malloc(sizeof(char*) * linhas);
    for ( int i = 0; i < linhas; i++) {
        mapa[i] = malloc(sizeof(char) * (colunas + 1));
    }

    for( int i = 0; i < 5; i++){
        fscanf(f, "%s", mapa[i]);
    }

    for( int i = 0; i < 5; i++){
        printf("%s\n", mapa[i]);
    }

    fclose(f);

    for (int i = 0; i < linhas; i++) {
        free(mapa[i]);
    }
    free(mapa);
}