#include <stdio.h>

int maiorMenor(int *v, int *maior, int *menor) {
    int soma = 0, media;
    
    for(int i = 0; i < 10; i++) {
        soma += v[i];
    }

    media = soma/10;
    
    //Cálculo do valor de maior e menor
    *maior = v[0];
    *menor = v[0];
    for(int i = 0; i < 10; i++) {
        if(v[i] > *maior) {
            *maior = v[i];
        }

        if(v[i] < *menor) {
            *menor = v[i];
        }
    }

    printf("Maior valor do vetor: %d, seu endereco de memoria: %d", *maior, maior);
    printf("\nMenor valor do vetor: %d, seu endereco de memoria: %d", *menor, menor);
    printf("\nEndereco da primeira posicao: %d", &v[0]);
    printf("\nEndereco da ultima posicao: %d", &v[9]);

    return media;
}

void main() {
   int vetor[10];

   printf("Digite os valores:\n");

   //Digita os valores do vetor
   for(int i = 0; i < 10; i++) {
       scanf("%d", &vetor[i]);
   }
   int *pVetor = &vetor;
   int maiorV = 0, menorV = 0;
   int *pMaiorV = &maiorV, *pMenorV = &menorV;

   //Chamada da função passando os ponteiros
   int mediaVetor = maiorMenor(pVetor, pMaiorV, pMenorV);
   

    //Substraindo a média dos valores que estão abaixo dela
    for(int i = 0; i < 10; i++) {
        if(pVetor[i] < mediaVetor) {
            pVetor[i] = pVetor[i] - mediaVetor;
        }
    }


    //Calculando os novos valores de Maior e Menor
    maiorV = pVetor[0];
    menorV = pVetor[0];
    for(int i = 0; i < 10; i++) {
        if(pVetor[i] > maiorV) {
            maiorV = pVetor[i];
        }

        if(pVetor[i] < menorV) {
            menorV = pVetor[i];
        }
    }
    printf("\n");
    printf("\nMaior valor do novo vetor: %d, seu endereco de memoria: %d", *pMaiorV, pMaiorV);
    printf("\nMenor valor do novo vetor: %d, seu endereco de memoria: %d", *pMenorV, pMenorV);

    printf("\nMedia = %d", mediaVetor);
}

