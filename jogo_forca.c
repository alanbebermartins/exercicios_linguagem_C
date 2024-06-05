#include <stdio.h>
#include <string.h>

int main(){

    printf("************************************\n");
    printf("*****Bem vindo ao jogo da forca*****\n");
    printf("************************************\n");

    char palavrasecreta[20];

    sprintf(palavrasecreta, "MELANCIA");
    int acertou = 0;
    int enforcou = 0;
    char chutesdousuario[26];
    int tentativas = 0;

    do {
        
        for (int i = 0; i < strlen(palavrasecreta); i++){
            
            int achou = 0;

            for (int j = 0; j < tentativas; j++) {
                if(chutesdousuario[j] == palavrasecreta[i]){
                    achou = 1;
                    break;
                }
            }

            if (achou) {
                printf("%c ", palavrasecreta[i]);
            } else {            
                printf("_ ");
            }
        }
        printf("\n");
        char chute;
        printf("Qual letra? ");
        scanf(" %c", &chute);    



        chutesdousuario[tentativas] = chute;
        tentativas++;



    } while (!acertou && !enforcou);
    
    
    
    
}