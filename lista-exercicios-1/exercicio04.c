#include <stdio.h>
#include <stdlib.h>

void imprimeDecrescente(int v[], int tamanho) {
    //Colocar array em ordem decrescente
    for(int i = 1; i < tamanho; i++) {
        int ref = v[i];
        int j = i - 1;

        while ((j >= 0) && (ref > v[j])){
            v[j+1] = v[j];
            j = j-1;
        }
        v[j + 1] = ref;
    }

    //imprimir array
    printf("[ ");

    for (int i = 0; i < tamanho; i++){
        printf("%d ", v[i]);
    } 

    printf("]");
}


void main() {
    int n;
    printf("Digite a quantidade de numeros: ");
    scanf("%d", &n);
    int *vetor = (int) malloc(n * sizeof(int));
    int i = 0, tam = 0, capacidade = n;

    printf("Digite os numeros:\n");

    //While para armazenar os valores digitados pelo usuário
    while(i < n){
        scanf(" %d", &vetor[tam]);
        tam++;
        i++;

        //Quando a quantidade definida inicialmente for alcançada, é perguntado se o usuário deseja digitar mais números
        if(i == n) {
            char resp;
            printf("Deseja digitar mais numeros?(s/n) ");
            scanf(" %c", &resp);

            if(resp == 's'){
                printf("Quantos?");
                scanf("%d", &n);
                i = 0;
                printf("\nDigite os numeros: \n");
            }    
        }

        //verifica se a quantidade digitada é igual ou superior a capacidade previamente determinada
        if (tam >= capacidade) {
             
            //realoca o atual vetor reservando mais memória
            vetor = (int*) realloc(vetor, (capacidade*2) * sizeof(int));

            //verifica se a realocação foi feita, caso não tenha dado erro tenta fazer novamente
            while (vetor == NULL){
                vetor = (int*) realloc(vetor, (capacidade*2) * sizeof(int));
            } 

            capacidade *= 2;
        }
    }

    //Caso o tamanho seja menor do que nossa capacidade (Ou seja, sobre muito espaço alocado que não será usado), vamos realocar a memória reservada para o vetor para seu tamanho real
    if(tam < capacidade) {
        vetor = (int*) realloc(vetor, (tam) * sizeof(int));

        while(vetor == NULL) {
            vetor = (int*) realloc(vetor, (tam) * sizeof(int));
        }
    }
    
    
    //chamada da função passando o vetor e o tamanho dele
    imprimeDecrescente(vetor, tam);
    free(vetor);
}