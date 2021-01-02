#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alterarParagrafo(char **paragrafos, int numPar) {
    fflush(stdin);
    int linha = numPar - 1;
    paragrafos[linha] = (char*) realloc(paragrafos[linha], 100 * sizeof(char));
    int tam = 0, coluna = 0, capacidade = 100;

    printf("Digite o paragrafo %d:\n", linha + 1);
    while ((paragrafos[linha][coluna] = getchar()) != '\n'){
        tam++;
        coluna++;
        //verifica se a quantidade digitada é igual ou superior a capacidade previamente determinada
        if(tam >= capacidade) {

            //realoca o atual vetor reservando mais memória
            paragrafos[linha] = (char*) realloc(paragrafos[linha], (capacidade*2) * sizeof(char));

            //verifica se a realocação foi feita, caso não tenha dado erro tenta fazer novamente
            while (paragrafos[linha] == NULL){
                paragrafos[linha] = (char*) realloc(paragrafos[linha], (capacidade*2) * sizeof(char));
            }   

            capacidade *= 2;
        }     
    }
    paragrafos[linha][coluna] = '\0';

    //Caso o tamanho seja menor do que nossa capacidade (Ou seja, sobre muito espaço alocado que não será usado), vamos realocar a memória reservada para o vetor para seu tamanho real
    if(tam < capacidade) {
        paragrafos[linha] = (char*) realloc(paragrafos[linha], (tam) * sizeof(char));
    }
    printf("\n");
}

void main() {

    int n;
    char **paragrafos;

    printf("Digite a quantidade de paragrafos: ");
    scanf("%d", &n);
    fflush(stdin);

    paragrafos = (char**) malloc(n * sizeof(char*));
    
    while (paragrafos == NULL){
        paragrafos = (char**) malloc(n * sizeof(char*));
    }
        
    for(int i = 0; i < n; i++) {
        paragrafos[i] = (char*) malloc(100 * sizeof(char));

        while (paragrafos == NULL){
            paragrafos[i] = (char*) malloc(100 * sizeof(char));
        }
    }

    for (int linha = 0; linha < n; linha++) {
        int tam = 0, coluna = 0, capacidade = 100; 
        printf("Digite o paragrafo %d:\n", linha + 1);

        while ((paragrafos[linha][coluna] = getchar()) != '\n')
        {
            tam++;
            coluna++;
            
            //verifica se a quantidade digitada é igual ou superior a capacidade previamente determinada
            if(tam >= capacidade) {

                //realoca o atual vetor reservando mais memória
                paragrafos[linha] = (char*) realloc(paragrafos[linha], (capacidade*2) * sizeof(char));

                //verifica se a realocação foi feita, caso não tenha dado erro tenta fazer novamente
                while (paragrafos[linha] == NULL){
                    paragrafos[linha] = (char*) realloc(paragrafos[linha], (capacidade*2) * sizeof(char));
                }   

                capacidade *= 2;
            }     
        }
        paragrafos[linha][coluna] = '\0';
        fflush(stdin); 

        //Caso o tamanho seja menor do que nossa capacidade (Ou seja, sobre muito espaço alocado que não será usado), vamos realocar a memória reservada para o vetor para seu tamanho real
        if(tam < capacidade) {
            paragrafos[linha] = (char*) realloc(paragrafos[linha], (tam) * sizeof(char));
        }
    }

    //imprimi os parágrafos inicialmente digitados
    for (int z = 0; z < n; z++) {
        printf("\nParagrafo %d:\n", z+1);
        printf("%s\n", paragrafos[z]);
        printf("\n");
    }

    char resp = "";
    int numeroParagrafo = 0;
    do{
        printf("Deseja alterar algum paragrafo?(s/n)");
        scanf(" %c", &resp);

        if(resp == 's') {
            printf("Qual paragrafo?");
            scanf("%d", &numeroParagrafo);
            while (numeroParagrafo <= 0)
            {
                printf("Digite um numero valido: ");
                scanf("%d", &numeroParagrafo);
            }

            //chamada da função (passando nossa matriz e o número do parágrafo a ser alterado) para alterar o parágrafo escolhido
            alterarParagrafo(paragrafos, numeroParagrafo);
            
            //imprimi os parágrafos sempre que algum for alterado
            for (int z = 0; z < n; z++) {
                printf("Paragrafo %d:\n", z+1);
                printf("%s\n", paragrafos[z]);
                printf("\n");
            }
            
        }

    } while(resp != 'n');
    free(paragrafos);
}