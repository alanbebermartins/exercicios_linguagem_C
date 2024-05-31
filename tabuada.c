#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Loop for 

int main(void){
    int tabuada, contador = 0;
    printf("Informe um valor para a tabuada: ");
    scanf("%d", &tabuada);

    for (contador = 0; contador <= 10; contador++){
        printf("%d X %d = %d\n", tabuada, contador , contador*tabuada);
    }
    return 0;
}