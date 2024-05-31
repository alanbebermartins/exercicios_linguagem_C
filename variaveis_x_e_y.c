#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    // Imprime o cabecalho do jogo
    setlocale(LC_ALL, "Portuguese");
    printf("* Jogo das variaveis x e y *\n");
    int variavel_X;
    int variavel_Y;
    printf("Informe o valor da variavel 'X'");
    scanf("%d", &variavel_X);
    printf("O valor da variavel X e = %d\n", variavel_X);
    printf("Informe o valor da variavel 'Y'");
    scanf("%d", &variavel_Y);
    printf("O valor da variavel Y e = %d\n", variavel_Y);
    int resultado = variavel_X * variavel_Y;
    printf("O valor do resultado da multiplicacao das variaveis X e Y e = %d\n", resultado);
}