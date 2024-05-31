#include <stdio.h>
#include<stdbool.h>

int main(){
    // Imprime o cabecalho do jogo
    printf("***************************************\n");
    printf("* Bem vindo ao jogo do numero secreto *\n");
    printf("***************************************\n");

    // A palavra reservada int serve para tipar a variavel do tipo inteiro
    int numeroSecreto = 25;
    int chute;
    int ganhou = 0;
    int tentativas = 0;
    while (ganhou == 0){
        printf("Informe qual e o numero secreto!\n");
        // printf("O numero %d e o secreto!\n", numeroSecreto);
        // a função scanf serve para ler o que foi digitado no teclado, e recebe 2 parametros, e obrigatoriamente precisa do & comercial antes da variaviavel que está lendo
        scanf("%d", &chute);
        printf("O seu chute foi %d!\n", chute);
        if (chute < 0){
            printf("Voce nao pode digitar numeros negativos\n");
            continue;
        }
        if (chute == numeroSecreto){
            printf("Parabens, voce acertou o numero secreto com %d tentativas!\n", tentativas+1);
            ganhou = 1;
        } else if (chute < numeroSecreto){
            printf("O numero secreto é maior que %d\n", chute);
            printf("Tente novamente!\n");
        } else if (chute > numeroSecreto) {
            printf("O numero secreto é menor que %d\n", chute);
            printf("Tente novamente!\n");
        }
        tentativas++;   
    }
    printf("Fim de jogo!");
}