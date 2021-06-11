/*
    Observações: Antes de abrir o estacionamento deve-se cadastrar pelo menos 1 funcionário. Então os passos seriam:
    - Cadastrar funcionários (2)
    - Abrir estacionamento   (0)
    - Fazer qualquer operação
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define MAXCARACTER 40

int saldo = 400;
int faturamento = 300;
int qtdCarros = 0;
int pos = 0;
int verificacoesLista = 0;
int verificacoesArvBi = 0;
int verificacoesArvAvl = 0;
int iteracoesArvBi = 0;
int iteracoesArvAvl = 0;


struct carro {
    char placaCarro;
    int horaEntrada;
    struct carro* prox;
};
typedef struct carro Carro;

struct pilhaCarros {
    Carro* topo;
    int n;
};
typedef struct pilhaCarros PilhaCar;

struct pilhaRua {
    Carro* topo;
    int n;
};
typedef struct pilhaCarros PilhaRua;

struct funcionario {
    char nome[MAXCARACTER];
    int id;
    int idade;
    struct funcionario* prox;
};
typedef struct funcionario Func;

struct listaEstacionamento {
    char placaCarro;
    int horaEntrada;
    struct listaEstacionamento* ant;
    struct listaEstacionamento* prox;
};
typedef struct listaEstacionamento ListaCar;

struct nodeArvBi {
    char placaCarro;
    struct nodeArvBi* esquerda;
    struct nodeArvBi* direita;
};
typedef struct nodeArvBi NodeArvBi;

struct listaBusca {
    char placaCarro;
    struct listaBusca* prox;
};
typedef struct listaBusca ListaBusca;

struct nodeArvAvl {
    char placaCarro;
    int altura;
    struct nodeArvAvl* esquerda;
    struct nodeArvAvl* direita;
};
typedef struct nodeArvAvl NodeArvAvl;






//================== Métodos relacionados a implementação da Árvore AVL ======================

NodeArvAvl* inicializaArvAvl() {
    return NULL;
}

int altura(NodeArvAvl* no) {
    if(no == NULL) {
        return 0;
    }

    return no->altura;
}

int maior(int x, int y) {
    return (x > y ? x : y);
}

int fatorBalanceamento(NodeArvAvl* no) {
    if(no == NULL) {
        return 0;
    }

    return altura(no->esquerda) - altura(no->direita);
}

NodeArvAvl* rotacaoEsquerda(NodeArvAvl* no) {
    NodeArvAvl* aux = no->direita;
    NodeArvAvl* temp = aux->esquerda;

    aux->esquerda = no;
    no->direita = temp;

    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    aux->altura = 1 + maior(altura(aux->esquerda), altura(aux->direita));

    return aux;
}

NodeArvAvl* rotacaoDireita(NodeArvAvl* no) {
    NodeArvAvl* aux = no->esquerda;
    NodeArvAvl* temp = aux->direita;

    aux->direita = no;
    no->esquerda = temp;

    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    aux->altura = 1 + maior(altura(aux->esquerda), altura(aux->direita));
   
    return aux;
}

NodeArvAvl* duplaRotacaoDireita(NodeArvAvl* no) {
    no->esquerda = rotacaoEsquerda(no->esquerda);
    return rotacaoDireita(no);
}

NodeArvAvl* duplaRotacaoEsquerda(NodeArvAvl* no) {
    no->direita = rotacaoDireita(no->direita);
    return rotacaoEsquerda(no);
}

NodeArvAvl* inserirArvAvl(NodeArvAvl* no, char placa) {
    if(no == NULL) {
        NodeArvAvl* aux = (NodeArvAvl*) malloc(sizeof(NodeArvAvl));
        aux->placaCarro = placa;
        aux->direita = NULL;
        aux->esquerda = NULL;
        aux->altura = 1;
        return aux;
    }

    if(placa < no->placaCarro) {
        no->esquerda = inserirArvAvl(no->esquerda, placa);
    } else if (placa > no->placaCarro) {
        no->direita = inserirArvAvl(no->direita, placa);
    } else {
        return no;
    }

    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    int equilibrio = fatorBalanceamento(no);

    //Desbalanceado para esquerda - rotação direita simples
    if(equilibrio > 1 && placa < no->esquerda->placaCarro) {
        return rotacaoDireita(no);
    }

    //Desbalanceado para esquerda (algum nó filho desbalanceado para direita) - rotação direita dupla
    if(equilibrio > 1 && placa > no->esquerda->placaCarro) {
        return duplaRotacaoDireita(no);
    }

    //Desbalanceado para direita - rotação esquerda simples
    if(equilibrio < -1 && placa > no->direita->placaCarro) {
        return rotacaoEsquerda(no);
    }

    //Desbalanceado para direita (algum nó filho desbalanceado para direita) - rotação direita dupla
    if(equilibrio < -1 && placa < no->direita->placaCarro) {
       return duplaRotacaoEsquerda(no);
    }
    return no;
}

NodeArvAvl* buscarArvAvl(NodeArvAvl* no, char placa) {
    
    iteracoesArvAvl++;
    if(no != NULL) {
        if(no->placaCarro == placa) {
            printf("O Carro %c foi encontrado\n", no->placaCarro);
            printf("Position: %d\n", pos);
            if(pos > qtdCarros/2) {
                printf("Recomendavel retirar o carro pelo portao 1\n");
            } else {
                printf("Recomendavel retirar o carro pelo portao 2\n");
            }
            printf("\nQuantidade de iteracoes: %d\n", iteracoesArvAvl);
            verificacoesArvAvl += iteracoesArvAvl;
            iteracoesArvAvl = 0;
            return no;
        } else {
            printf("Checando o Carro %c\n", no->placaCarro);
            if(placa > no->placaCarro) {
                return buscarArvAvl(no->direita, placa);
            } else {
                return buscarArvAvl(no->esquerda, placa);
            }
        }
    }

    return NULL;
}

NodeArvAvl* arvMinAvl(NodeArvAvl* no) {
    if(no != NULL) {
        NodeArvAvl* aux = no;
        while(aux->esquerda != NULL) {
            aux = aux->esquerda;
        }
        return aux;
    }
    
    return NULL;
}

NodeArvAvl* removeAvl(NodeArvAvl* no, char placa) {
    if(no == NULL) {
        return NULL;
    }

    if(placa > no->placaCarro) {
        no->direita = removeAvl(no->direita, placa);
    } else if(placa < no->placaCarro) {
        no->esquerda = removeAvl(no->esquerda, placa);
    } else {
        if(no->esquerda == NULL && no->direita == NULL) {
            free(no);
            return NULL;
        } else if(no->esquerda == NULL && no->direita != NULL) {
            NodeArvAvl* aux = no->direita;
            free(no);
            return aux;
        } else if(no->esquerda != NULL && no->direita == NULL) {
            NodeArvAvl* aux = no->esquerda;
            free(no);
            return aux;
        } else {
            NodeArvAvl* aux = arvMinAvl(no->direita);
            int elemento = aux->placaCarro;
            removeAvl(no, elemento);
            no->placaCarro = elemento;
        }
    }

    if (no == NULL) {
        return no;  
    }
      

    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
    int equilibrio = fatorBalanceamento(no);

    //Desbalanceado para esquerda - rotação direita simples
    if (equilibrio > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no); 
    }
        
    //Desbalanceado para esquerda (algum nó filho desbalanceado para direita) - rotação esquerda dupla
    if (equilibrio > 1 && fatorBalanceamento(no->esquerda) < 0) { 
        return duplaRotacaoDireita(no);
    } 
    
    //Desbalanceado para direita - rotação esquerda simples
    if (equilibrio < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }
    
    //Desbalanceado para direita (algum nó filho desbalanceado para direita) - rotação direita dupla
    if (equilibrio < -1 && fatorBalanceamento(no->direita) > 0) { 
        return duplaRotacaoEsquerda(no);
    } 

    return no;
}

void printTreeAvl(NodeArvAvl* no) {
    if(no != NULL) {
        printf("%c ", no->placaCarro);
        printTreeAvl(no->esquerda);
        printTreeAvl(no->direita); 
    }
}


void imprimeMediaVerificacoesArvAvl(float qtdBuscaArvAvl) {
    float mediaVerificacoes = verificacoesArvAvl/qtdBuscaArvAvl;
    printf("\nMedia de verificacoes = %.2f\n", mediaVerificacoes);
}


//================== Métodos relacionados a implementação da Árvore Binária ======================

NodeArvBi* inicializaArvBi() {
    return NULL;
}

NodeArvBi* inserirArvEst(NodeArvBi* root, char placa) {
    if(root == NULL) {
        NodeArvBi* aux = (NodeArvBi*) malloc(sizeof(NodeArvBi));
        aux->placaCarro = placa;
        aux->direita = NULL;
        aux->esquerda = NULL;
        return aux;
    } else {
        if(placa > root->placaCarro) {
            root->direita = inserirArvEst(root->direita, placa);
        } else {
            root->esquerda = inserirArvEst(root->esquerda, placa);
        }
    }

    return root;
}

void buscarArvEst(NodeArvBi* root, char placa) {
    
    iteracoesArvBi++;
    if(root != NULL) {
        if(root->placaCarro == placa) {
            printf("O Carro %c foi encontrado\n", root->placaCarro);
            printf("Position: %d\n", pos);
            if(pos > qtdCarros/2) {
                printf("Recomendavel retirar o carro pelo portao 1\n");
            } else {
                printf("Recomendavel retirar o carro pelo portao 2\n");
            }
            printf("\nQuantidade de iteracoes: %d\n", iteracoesArvBi);
            verificacoesArvBi += iteracoesArvBi;
            iteracoesArvBi = 0;
        } else {
            if(root!=NULL) {
                printf("Checando o Carro %c\n", root->placaCarro);
            }
            if(placa > root->placaCarro) {
                return buscarArvEst(root->direita, placa);
            } else {
                return buscarArvEst(root->esquerda, placa);
            }
        }
    }
}

NodeArvBi* arvMin(NodeArvBi* root) {
    if(root != NULL) {
        NodeArvBi* aux = root;
        while(aux->esquerda != NULL) {
            aux = aux->esquerda;
        }
        return aux;
    }
    
    return NULL;
}

NodeArvBi* removeArvEst(NodeArvBi* root, char placa) {
    if(root != NULL) {
        if(placa > root->placaCarro) {
            root->direita = removeArvEst(root->direita, placa);
        } else if(placa < root->placaCarro) {
            root->esquerda = removeArvEst(root->esquerda, placa);
        } else {
            if(root->esquerda == NULL && root->direita == NULL) {
                free(root);
                return NULL;
            } else if(root->esquerda == NULL && root->direita != NULL) {
                NodeArvBi* aux = root->direita;
                free(root);
                return aux;
            } else if(root->esquerda != NULL && root->direita == NULL) {
                NodeArvBi* aux = root->esquerda;
                free(root);
                return aux;
            } else {
                NodeArvBi* menor = arvMin(root->direita);
                char elemento = menor->placaCarro;
                removeArvEst(root, elemento);
                root->placaCarro = elemento;
            }
        }
        return root;
    }

    return NULL;
}

void percorrerEst(ListaCar* est, char placa) {
    for(ListaCar* aux = est; aux->placaCarro != placa; aux = aux->prox) {
        pos++;
    }
}

void imprimeMediaVerificacoesArvBi(float qtdBuscaArvBi) {
    float mediaVerificacoes = verificacoesArvBi/qtdBuscaArvBi;
    printf("\nMedia de verificacoes = %.2f\n", mediaVerificacoes);
}


void printTree(NodeArvBi* no) {
    if(no != NULL) {
        printf("%c ", no->placaCarro);
        printTree(no->esquerda);
        printTree(no->direita); 
    }
}


//================== Métodos relacionados a implementação da Lista Encadeada ======================
ListaBusca* inicializaListaBusca() {
    return NULL;
}

ListaBusca* inserirListaBusca(ListaBusca* est, char placa) {
    ListaBusca* novo = (ListaBusca*) malloc(sizeof(ListaBusca));
    novo->placaCarro = placa;
    novo->prox = est;

    return novo;
}

void buscarLista(ListaBusca* est, char placa) {
    ListaBusca* aux;
    printf("\n--------------- Busca pela lista encadeada ---------------\n");
    int iteracoes = 0;
    int encontrou = 0;
    for(aux = est; aux != NULL && encontrou != 1; aux = aux->prox) {
        iteracoes++;
        if(aux->placaCarro == placa) {
            printf("O Carro %c foi encontrado\n", aux->placaCarro);
            printf("Position: %d\n", pos);
            encontrou = 1;
            if(pos > qtdCarros/2) {
                printf("Recomendavel retirar o carro pelo portao 1\n");
            } else {
                printf("Recomendavel retirar o carro pelo portao 2\n");
            }
        } else {
            printf("Checando o Carro %c\n", aux->placaCarro);
        }
    }

    verificacoesLista += iteracoes; 
    printf("\nQuantidade de iteracoes: %d\n", iteracoes);
}

ListaBusca* removeListaBusca(ListaBusca* listaEst, char placa) {
    ListaBusca* ant = NULL; 
    ListaBusca* aux = listaEst; 
    
    while (aux != NULL && aux->placaCarro != placa) {
        ant = aux;
        aux = aux->prox;
    }
    
    if (aux == NULL) {
        return listaEst; 
    }
        
    if (ant == NULL) {
        listaEst = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux);
    return listaEst;
}

void imprimeMediaVerificacoesLista(float qtdBuscaLista) {
    float mediaVerificacoes = verificacoesLista/qtdBuscaLista;
    printf("\nMedia de verificacoes = %.2f\n", mediaVerificacoes);
}



void imprimeListaBusca (ListaBusca* l)
{
    ListaBusca* p; 
    for (p = l; p != NULL; p = p->prox)
    printf("info = %c\n", p->placaCarro);
}




//================== Métodos relacionados aos funcionários ======================

Func* inicializaFunc() {
    return NULL;
}

Func* cadastrarFuncionario(Func* func) {
    setbuf(stdin, NULL);
    char nomeFunc[30];
    printf("Nome: ");
    fgets(nomeFunc, 30, stdin);

    int idFunc;
    printf("ID: ");
    scanf(" %d", &idFunc);

    int idadeFunc;
    printf("Idade: ");
    scanf(" %d", &idadeFunc);

    Func* novoFunc = (Func*) malloc(sizeof(Func));
    strcpy(novoFunc->nome, nomeFunc);
    novoFunc->id = idFunc;
    novoFunc->idade = idadeFunc;
    //Implementação lista circular
    if(func == NULL) {
        novoFunc->prox = novoFunc;
    } else {
        Func* aux = func;
        while(aux->prox != func) {
            aux = aux->prox;
        }
        aux->prox = novoFunc;
        novoFunc->prox = func;
    }
    
    return novoFunc;
}

void listarFuncionarios(Func* func) {
    Func* aux = func;
    printf("--------------- Funcionarios ---------------");
    do{
        printf("\n");
        printf("Nome: %s", aux->nome);
        printf("ID: %d\n", aux->id);
        printf("Idade: %d", aux->idade);
        printf("\n");
        aux = aux->prox;
    }while(aux != func);
}





//===================== Métodos para ordenar os funcionarios ========================
void selectSortID(Func* funcionario) {
    
    for(Func* i = funcionario; i->prox != funcionario; i = i->prox){
        Func* menor = i;
        for(Func* j = i->prox; j != funcionario; j = j->prox) {
            if(menor->id > j->id) {
                menor = j;
            }
        }

        int auxId = i->id;
        i->id = menor->id;
        menor->id = auxId;
        int auxIdade= i->idade;
        i->idade = menor->idade;
        menor->idade = auxIdade;
        char auxNome[MAXCARACTER];
        strcpy(auxNome, i->nome);
        strcpy(i->nome, menor->nome);
        strcpy(menor->nome, auxNome);
    }
}

void selectSortIdade(Func* funcionario) {
    
    for(Func* i = funcionario; i->prox != funcionario; i = i->prox){
        Func* menor = i;
        for(Func* j = i->prox; j != funcionario; j = j->prox) {
            if(menor->idade > j->idade) {
                menor = j;
            }
        }

        int auxId = i->id;
        i->id = menor->id;
        menor->id = auxId;
        int auxIdade= i->idade;
        i->idade = menor->idade;
        menor->idade = auxIdade;
        char auxNome[MAXCARACTER];
        strcpy(auxNome, i->nome);
        strcpy(i->nome, menor->nome);
        strcpy(menor->nome, auxNome);
    }
}

void selectSortNome(Func* funcionario) {
    
    for(Func* i = funcionario; i->prox != funcionario; i = i->prox){
        Func* menor = i;
        for(Func* j = i->prox; j != funcionario; j = j->prox) {
            if(strcmp(menor->nome, j->nome) > 0) {
                menor = j;
            }
        }

        int auxId = i->id;
        i->id = menor->id;
        menor->id = auxId;
        int auxIdade= i->idade;
        i->idade = menor->idade;
        menor->idade = auxIdade;
        char auxNome[MAXCARACTER];
        strcpy(auxNome, i->nome);
        strcpy(i->nome, menor->nome);
        strcpy(menor->nome, auxNome);
    }
}





//===================== Métodos para estacionamento até atingir a meta ========================
PilhaCar* inicializaEst() {
    PilhaCar* p = (PilhaCar*) malloc(sizeof(PilhaCar));
    p->topo = NULL;
    p->n = 0;
    return p;
}

void liberarPilha(PilhaCar* p) {
    Carro* aux = p->topo;
    while(aux != NULL) {
        Carro* auxTwo = aux->prox;
        free(aux);
        aux = auxTwo;
    }
    free(p);
}

void verificaSaldo(int taxa) {
    saldo += taxa;
    if(saldo >= faturamento){
        printf("Faturamento alcancado! Estacionamento fechou!");
    }
}

Carro* inserirCarroPilha_aux(Carro* car, char placa, int hora)  {
    Carro* novoCarro = (Carro*) malloc(sizeof(Carro));
    novoCarro->placaCarro = placa;
    novoCarro->horaEntrada = hora;
    novoCarro->prox = car;

    return novoCarro;
}

void inserirCarroPilha(PilhaCar* p, char placa, int hora, int quantidade) {
        p->topo = inserirCarroPilha_aux(p->topo, placa, hora);
}

Carro* removerCarroPilha_aux(Carro* p) {
    Carro* aux = p->prox;
    free(p);
    return aux;
}

void removerCarroPilha(PilhaCar* p, PilhaCar* rua, Func* funcionario, char placa, int quantidade) {
    int encontrou = 0;
    Carro* aux;
    int horaEntrada = 0;
    int horaSaida = 0;
    Func* auxFunc = funcionario;
    printf("\n--------------- Processo de entrega do carro ---------------\n");
    for(aux = p->topo; aux != NULL && encontrou == 0; aux = aux->prox) {
        if(aux->placaCarro != placa) {
            char carroManobrado = aux->placaCarro;
            inserirCarroPilha(rua, aux->placaCarro, aux->horaEntrada, quantidade);
            printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a) %s", aux->placaCarro, auxFunc->nome);
            auxFunc = auxFunc->prox;
        } else {
            auxFunc = auxFunc->prox;
            printf("O carro %c foi entregue ao cliente pelo(a) funcionario(a) %s", aux->placaCarro, auxFunc->nome);
            auxFunc = auxFunc->prox;
            encontrou = 1;
            horaEntrada = aux->horaEntrada;
            horaSaida = aux->horaEntrada + rand() % (24 - aux->horaEntrada + 1);
            p->topo = removerCarroPilha_aux(aux);
            
            p->n--;
        }
    }

   

    Carro* auxRua = rua->topo;
    for(auxRua; auxRua != NULL; auxRua = auxRua->prox) {
        inserirCarroPilha(p, auxRua->placaCarro, auxRua->horaEntrada, quantidade);
        printf("O Carro %c foi manobrado de volta para o estacionamento pelo funcionario(a): %s",  auxRua->placaCarro, auxFunc->nome);
        auxFunc = auxFunc->prox;
    }   

    if(encontrou == 0) {
        printf("\n********* Carro nao encontrado! *********\n");
    } else {
        printf("\nHora entrada: %d\n", horaEntrada);
        printf("Hora saida: %d\n", horaSaida);
        verificaSaldo((horaSaida - horaEntrada) * 12);
        liberarPilha(rua);
    } 
}

void listarCarros(PilhaCar* p) {
    printf("\n");
    printf("--------------- Carros no estacionamento ---------------\n");
    for(Carro* aux = p->topo; aux !=NULL; aux = aux->prox) {
        printf("Carro %c  Entrada: %d \n", aux->placaCarro, aux->horaEntrada);
    }
}

bool verificaCheio(PilhaCar* p, int capacidade) {
    return p->n == capacidade;
}

bool verificaVazio(PilhaCar* p) {
    return p->n == 0;
}




//===================== Métodos para estacionamento após atingir a meta ========================
ListaCar* inicializaListaEst() {
    return NULL;
}

ListaCar* inserirCarroListaRua(ListaCar* estacionamento, char placa, int hora) {
    ListaCar* novoCarro = (ListaCar*) malloc(sizeof(ListaCar));
    novoCarro->placaCarro = placa;
    novoCarro->horaEntrada = hora;
    novoCarro->prox = estacionamento;
    novoCarro->ant = NULL;
    if(estacionamento != NULL) {
        estacionamento->ant = novoCarro;
    }
    return novoCarro;
}

ListaCar* inserirCarroLista(ListaCar* estacionamento, char placa, int hora) {
    ListaCar* novoCarro = (ListaCar*) malloc(sizeof(ListaCar));
    novoCarro->placaCarro = placa;
    novoCarro->horaEntrada = hora;
    //Implementação lista duplamente encadeada
    novoCarro->prox = estacionamento;
    novoCarro->ant = NULL;
    if(estacionamento != NULL) {
        estacionamento->ant = novoCarro;
    }
    return novoCarro;
}

ListaCar* liberarLista(ListaCar* lista) {
    ListaCar* aux = lista;

    while(aux != NULL) {
        ListaCar* auxTwo = aux->prox;
        free(aux);
        aux = auxTwo;
    }

    return NULL;
}

ListaCar* removerCarroLista(ListaCar* estacionamento, ListaCar* rua, Func* funcionario, char placa, int qtdLista) {
    int pos = 0;
    int encontrou = 0;
    int horaEntrada = 0;
    int horaSaida = 0;
    ListaCar* auxEst;
    Func* auxFunc = funcionario;
    for(auxEst = estacionamento; auxEst->placaCarro != placa; auxEst = auxEst->prox) {
        pos++;
    }
    printf("\n--------------- Processo de entrega do carro ---------------\n");
    if(pos < qtdLista/2) {
        for(ListaCar* i = estacionamento; i != NULL && encontrou == 0; i = i->prox){
            if(i->placaCarro != placa) {
                rua = inserirCarroListaRua(rua, i->placaCarro, i->horaEntrada);
                printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a) %s", i->placaCarro , auxFunc->nome);
                auxFunc = auxFunc->prox;
            } else {
                encontrou = 1;
                estacionamento = i->prox;
                i->prox->ant = NULL;
                printf("O carro %c foi entregue ao cliente pelo(a) funcionario(a) %s", i->placaCarro, auxFunc->nome);
                horaEntrada = i->horaEntrada;
                horaSaida = i->horaEntrada + rand() % (24 - i->horaEntrada + 1);
                auxFunc = auxFunc->prox;
            } 
        }
        
      
        ListaCar* auxRua;
        for(auxRua = rua; auxRua != NULL; auxRua = auxRua->prox) {
            estacionamento = inserirCarroLista(estacionamento, auxRua->placaCarro, auxRua->horaEntrada);
            printf("O Carro %c foi manobrado de volta para o estacionamento pelo funcionario(a): %s",  auxRua->placaCarro, auxFunc->nome);
            auxFunc = auxFunc->prox;
        }

        if(encontrou == 0) {
            printf("\n********* Carro nao encontrado! *********\n");
        } 
    
        rua = liberarLista(rua);
    } else {
        ListaCar* ultimoEl;
        int posUltimo = 0;
        for(ListaCar* i = estacionamento;  i != NULL; i = i->prox) {
            ultimoEl = i;
            posUltimo++;
        }
        for(ListaCar* i = ultimoEl; i != NULL && encontrou == 0; i = i->ant){
            if(i->placaCarro != placa) {
                rua = inserirCarroListaRua(rua, i->placaCarro, i->horaEntrada);
                printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a) %s", i->placaCarro , auxFunc->nome);
                auxFunc = auxFunc->prox;
            } else {
                printf("O carro %c foi entregue ao cliente pelo(a) funcionario(a) %s", i->placaCarro, auxFunc->nome);
                encontrou = 1;
                horaEntrada = i->horaEntrada;
                horaSaida = i->horaEntrada + rand() % (24 - i->horaEntrada + 1);
                i->ant->prox = NULL; 
                auxFunc = auxFunc->prox;
            } 
        }

        if(pos != posUltimo-1) {
             ListaCar* ultimoElNovo;
            for(ListaCar* i = estacionamento;  i != NULL; i = i->prox) {
                    ultimoElNovo = i;
            }

            for(ListaCar* i = ultimoElNovo; i != NULL; i = i->ant){
                rua = inserirCarroListaRua(rua, i->placaCarro, i->horaEntrada);
                printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a) %s", i->placaCarro , auxFunc->nome);
                auxFunc = auxFunc->prox;
            }
                
            estacionamento = liberarLista(estacionamento);
                
            ListaCar* ultimoRua;
            for(ListaCar* i = rua;  i != NULL; i = i->prox) {
                ultimoRua = i;
            }

            ListaCar* auxRua;
            for(auxRua = ultimoRua; auxRua != NULL; auxRua = auxRua->ant) {
                estacionamento = inserirCarroLista(estacionamento, auxRua->placaCarro, auxRua->horaEntrada);
                printf("O Carro %c foi manobrado de volta para o estacionamento pelo funcionario(a): %s",  auxRua->placaCarro, auxFunc->nome);
                auxFunc = auxFunc->prox;
            }
        }
        rua = liberarLista(rua);
    }

    return estacionamento;
}

void listarCarrosLista(ListaCar* estacionamento) {
    printf("\n");
    printf("--------------- Carros no estacionamento ---------------\n");
    for(ListaCar* aux = estacionamento; aux != NULL; aux = aux->prox) {
        printf("Carro %c\n", aux->placaCarro);
    }
}

bool verificaCheioLista(int qtdLista, int capacidade) {
    return qtdLista == capacidade;
}

bool verificaVazioLista(int qtdLista) {
    return qtdLista < 0;
}



//===================== Métodos auxiliares ========================

void imprimeMediaVerificacoesGeral(float qtdBuscaLista, float qtdBuscaArvBi, float qtdBuscaArvAvl) {
    printf("\nteste: %d\n", qtdBuscaLista);
    printf("\nteste2: %d\n", verificacoesLista);
    float mediaVerificacoesLista = verificacoesLista/qtdBuscaLista;
    float mediaVerificacoesArvBi = verificacoesArvBi/qtdBuscaArvBi;
    float mediaVerificacoesArvAvl = verificacoesArvAvl/qtdBuscaArvAvl;
    printf("\nMedia de verificacoes da lista = %.2f\n", mediaVerificacoesLista);
    printf("\nMedia de verificacoes da arvore binaria = %.2f\n", mediaVerificacoesArvBi);
    printf("\nMedia de verificacoes da arvore avl = %.2f\n", mediaVerificacoesArvAvl);
}

void printListaBusca(ListaBusca* lista) {
    ListaBusca* p; /* variável auxiliar para percorrer a lista */
    for (p = lista; p != NULL; p = p->prox){
        printf("%c ", p->placaCarro);
    }
    
}

void imprimirMenu() {
    printf("############## MENU ##############\n");
    printf("Abrir estacionamento----------------------- (0)\n");
    printf("Adicionar carro---------------------------- (1)\n");
    printf("Listar carros------------------------------ (2)\n");
    printf("Retirar carro------------------------------ (3)\n");
    printf("Cadastrar funcionarios--------------------- (4)\n");
    printf("Listar funcionarios------------------------ (5)\n");
    printf("Ordenar funcionarios----------------------- (6)\n");
    printf("Buscar pela arvore binaria----------------- (7)\n");
    printf("Buscar pala lista-------------------------- (8)\n");
    printf("Buscar pela arvore AVL--------------------- (9)\n");
    printf("Imprimir MENU------------------------------ (10)\n");
    printf("Limpar tela-------------------------------- (11)\n");
    printf("Verificacoes Lista------------------------- (12)\n");
    printf("Verificacoes Arvore Binaria---------------- (13)\n");
    printf("Verificacoes Arvore Avl-------------------- (14)\n");
    printf("Verificacoes Gerais------------------------ (15)\n");
    printf("Fechar estacionamento---------------------- (-1)\n");
}

//===================== Função Main ========================
int main() {
    srand(time(NULL));
    int capacidade;
    PilhaCar* estacionamentoPilha;
    PilhaCar* ruaPilha;
    ListaCar* ruaLista;
    ListaCar* estacionamentoLista = inicializaListaEst();
    Func* funcionario = inicializaFunc();
    NodeArvBi* arvEst = inicializaArvBi();
    ListaBusca* listaBusca = inicializaListaBusca();
    NodeArvAvl* arvAvlEst = inicializaArvAvl();
    int qtdLista = 0;
    int existeFuncionario = 0;
    float qtdBuscaLista = 0.0;
    float qtdBuscaArvBi = 0.0;
    float qtdBuscaArvAvl = 0.0;
    printf("Digite a quantidade de carros: ");
    scanf(" %d", &capacidade);

    imprimirMenu();

    int option = 0;
    char placa;
    char optionOrdenation[5];
    int horaEntrada = 0;
    int estacionamentoAberto = 0;

    do {
        setbuf(stdin, NULL);
        printf("\nDigite a opcao: ");
        scanf("%d", &option);

        setbuf(stdin, NULL);
        switch(option) {
            case 0:
                if(existeFuncionario) {
                    estacionamentoPilha = inicializaEst();
                    printf("Estacionamento aberto!\n");
                    estacionamentoAberto = 1;
                } else {
                    printf("\n================= ATENCAO =================\n");
                    printf("Nao eh permitido abrir o estacionamento sem funcionarios!!");
                }
                break;
            case 1:
                setbuf(stdin, NULL);
                if(estacionamentoAberto) {
                    if(saldo < faturamento) {
                        if(verificaCheio(estacionamentoPilha, capacidade)){
                            printf("Estacionamento lotado!");
                        } else {
                            setbuf(stdin, NULL);
                            printf("Digite a placa: ");
                            scanf("%c", &placa);
                            horaEntrada = rand() % 24;
                            inserirCarroPilha(estacionamentoPilha, placa, horaEntrada, capacidade);
                            estacionamentoPilha->n++;
                            verificaSaldo(12);
                        }
                    } else {
                        if(verificaCheioLista(qtdLista, capacidade)){
                            printf("Estacionamento lotado!");
                        } else {
                            setbuf(stdin, NULL);
                            printf("Digite a placa: ");
                            scanf("%c", &placa);
                            horaEntrada = rand() % 24;
                            estacionamentoLista = inserirCarroLista(estacionamentoLista, placa, horaEntrada);
                            arvEst = inserirArvEst(arvEst, placa);
                            listaBusca = inserirListaBusca(listaBusca, placa);
                            arvAvlEst = inserirArvAvl(arvAvlEst, placa);
                            qtdLista++;
                            saldo += 12;
                            qtdCarros++;
                        }  
                    }
                } else {
                    printf("\nEstacionamento ainda nao foi aberto!!\n");
                }
                break;
            case 2: 
                if(saldo < faturamento) {
                    listarCarros(estacionamentoPilha);
                } else {
                    listarCarrosLista(estacionamentoLista);
                }
                
                break;
            case 3: 
                if(saldo < faturamento) {
                    if(verificaVazio(estacionamentoPilha)) {
                        printf("Estacionamento vazio!");
                    } else {
                        setbuf(stdin, NULL);
                        printf("Digite a placa: ");
                        scanf("%c", &placa);
                        ruaPilha = inicializaEst();
                        removerCarroPilha(estacionamentoPilha, ruaPilha, funcionario, placa, capacidade);
                    }
                } else {
                    if(verificaVazioLista(qtdLista)) {
                        printf("Estacionamento vazio!");
                    } else {
                        setbuf(stdin, NULL);
                        printf("Digite a placa: ");
                        scanf("%c", &placa);
                        percorrerEst(estacionamentoLista, placa);
                        pos = (qtdCarros - pos) - 1;
                        buscarLista(listaBusca, placa);
                        printf("\n--------------- Busca pela Arvore binaria ---------------\n");
                        buscarArvEst(arvEst, placa);
                        printf("\n--------------- Busca pela Arvore AVL ---------------\n");
                        buscarArvAvl(arvAvlEst, placa);
                        qtdBuscaArvBi++;
                        qtdBuscaArvAvl++;
                        qtdBuscaLista++;
                        ruaLista = inicializaListaEst();
                        estacionamentoLista = removerCarroLista(estacionamentoLista, ruaLista, funcionario, placa, qtdLista);
                        listaBusca = removeListaBusca(listaBusca, placa);
                        removeArvEst(arvEst, placa);
                        removeAvl(arvAvlEst, placa);
                        qtdLista--;
                        qtdCarros--;
                        pos = 0;
                    }
                }
                break;
            case 4: 
                printf("Cadastrar funcionario: \n");
                funcionario = cadastrarFuncionario(funcionario);
                existeFuncionario = 1;
                break;
            case 5:
                setbuf(stdin, NULL);
                listarFuncionarios(funcionario);
                break;
            case 6:

                setbuf(stdin, NULL);
                printf("Deseja ordenar por ID, Idade ou nome?(id,idade,nome): ");
                scanf("%s", &optionOrdenation);
                if(strcmp(optionOrdenation,"id") == 0) {
                    selectSortID(funcionario);
                } else if(strcmp(optionOrdenation,"idade") == 0){
                    selectSortIdade(funcionario);
                } else if((strcmp(optionOrdenation,"nome") == 0)){
                    selectSortNome(funcionario);
                }
                break;
            case 7:
                setbuf(stdin, NULL);
                printf("Digite a placa: ");
                scanf("%c", &placa);
                printf("\n--------------- Busca pela arvore binaria ---------------\n");
                percorrerEst(estacionamentoLista, placa);
                pos = (qtdCarros - pos) - 1;
                qtdBuscaArvBi++;
                buscarArvEst(arvEst, placa);
                pos = 0;
                break;
            case 8:
                setbuf(stdin, NULL);
                printf("Digite a placa: ");
                scanf("%c", &placa);
                percorrerEst(estacionamentoLista, placa);
                pos = (qtdCarros - pos) - 1;
                buscarLista(listaBusca, placa);
                qtdBuscaLista++;
                pos = 0;
                break;
            case 9:
                setbuf(stdin, NULL);
                printf("Digite a placa: ");
                scanf("%c", &placa);
                percorrerEst(estacionamentoLista, placa);
                pos = (qtdCarros - pos) - 1;
                buscarArvAvl(arvAvlEst, placa);
                qtdBuscaArvAvl++;
                pos = 0;
                break;
            case 10:
                imprimirMenu();
                break;
            case 11:
                system("cls");
                break;
            case 12:
                imprimeMediaVerificacoesLista(qtdBuscaLista);
                break;
            case 13:
                imprimeMediaVerificacoesArvBi(qtdBuscaArvBi);
                break;
            case 14: 
                imprimeMediaVerificacoesArvAvl(qtdBuscaArvAvl);
                break;
            case 15: 
                imprimeMediaVerificacoesGeral(qtdBuscaLista,qtdBuscaArvBi,qtdBuscaArvAvl);
                break;
            case 16:
                printListaBusca(listaBusca);
                break;
            case -1:
                printf("ATE LOGO!!");
                break;
            default:
                printf("Valor invalido!!");
                exit(1);
                break;
        }
    } while(option != -1);

    return 1;
}