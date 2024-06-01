#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(){

    printf("***************************************\n");
    printf("* Bem vindo ao jogo do número secreto *\n");
    printf("***************************************\n");

    int segundos = time(0);
    srand(segundos);
    int numerorandomico = rand();
    int numeroSecreto = numerorandomico % 100;
    int chute;
    int ganhou = 0;
    int tentativas = 0;
    double pontos = 1000;
    
    while (ganhou == 0){
        printf("Informe qual é o número secreto!\n");
        scanf("%d", &chute);
        printf("O seu chute foi %d!\n", chute);
        if (chute < 0){
            printf("Você não pode digitar números negativos\n");
            continue;
        }
        if (chute == numeroSecreto){
            printf("Parabéns, você acertou o número secreto com %d tentativas!\n", tentativas+1);
            ganhou = 1;
        } else if (chute < numeroSecreto){
            printf("O número secreto é maior que %d\n", chute);
            printf("Tente novamente!\n");
        } else if (chute > numeroSecreto) {
            printf("O número secreto é menor que %d\n", chute);
            printf("Tente novamente!\n");
        }
        tentativas++;
        double pontosperdidos = ((double)(chute - numeroSecreto) / (double)2);
        if (pontosperdidos <0){
            pontosperdidos = pontosperdidos * (-1);
        }   
        pontos = pontos - pontosperdidos;
    }
    printf("Fim de jogo!\n");
    printf("Total de pontos: %.2f\n", pontos);
}