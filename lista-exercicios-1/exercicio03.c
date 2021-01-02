#include <stdio.h>
#include <stdlib.h>

void somenteVogais(char *s, int tam) {
    
    for(int i = 0; i < tam; i++) {
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U'){
            printf("%c", s[i]);        
        }   
    }
}

void main() {
    char *string = (char*) malloc (50 * sizeof(char));

    while(string == NULL) {
        char *string = (char*) malloc(50 * sizeof(char));
    }

    int i = 0, tam = 0, capacidade = 50;

    printf("Digite a String:\n");
    
    while((string[i] = getchar()) != '\n') {
        tam++;
        i++;

        //verifica se a quantidade digitada é igual ou superior a capacidade previamente determinada
        if(tam >= capacidade) {

            //realoca o atual vetor reservando mais memória
            string = (char*) realloc(string, (capacidade*2) * sizeof(char));

            //verifica se a realocação foi feita, caso não tenha dado erro tenta fazer novamente
            while (string == NULL){
                string = (char*) realloc(string, (capacidade*2) * sizeof(char));
            }

            capacidade *= 2;
        }
    }
    string[tam] = '\0';

    //Caso o tamanho seja menor do que nossa capacidade (Ou seja, sobre muito espaço alocado que não será usado), vamos realocar a memória reservada para o vetor para seu tamanho real
    if(tam < capacidade) {
        string = (char*) realloc(string, (tam) * sizeof(char));
    }
    
    //chamada da função passando o vetor e o tamanho dele
    somenteVogais(string, tam);
    free(string);
}