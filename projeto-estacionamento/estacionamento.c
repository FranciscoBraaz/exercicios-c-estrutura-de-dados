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

int saldo = 0;
int faturamento = 300;


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
            printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a): %s", aux->placaCarro, auxFunc->nome);
            auxFunc = auxFunc->prox;
        } else {
            auxFunc = auxFunc->prox;
            printf("O carro %c foi entregue ao cliente pelo(a) funcionario(a): %s", aux->placaCarro, auxFunc->nome);
            auxFunc = auxFunc->prox;
            encontrou = 1;
            horaEntrada = aux->horaEntrada;
            horaSaida = aux->horaEntrada + rand() % (24 - aux->horaEntrada + 1);
            p->topo = removerCarroPilha_aux(aux);
            
            p->n--;
        }
    }

   

    Carro* auxRua;
    for(auxRua = rua->topo; auxRua != NULL; auxRua = auxRua->prox) {
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
                printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a): %s", i->placaCarro , auxFunc->nome);
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
                printf("O carro %c foi manobrado para a rua pelo(a) funcionario(a): %s", i->placaCarro , auxFunc->nome);
                auxFunc = auxFunc->prox;
            } else {
                printf("O carro %c foi entregue ao cliente pelo(a) funcionario(a): %s", i->placaCarro, auxFunc->nome);
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

//===================== Função Main ========================
int main() {
    srand(time(NULL));
    int capacidade;
    PilhaCar* estacionamentoPilha;
    PilhaCar* ruaPilha;
    ListaCar* ruaLista;
    ListaCar* estacionamentoLista = inicializaListaEst();
    Func* funcionario = inicializaFunc();
    int qtdLista = 0;
    int existeFuncionario = 0;
    printf("Digite a quantidade de carros: ");
    scanf(" %d", &capacidade);

    printf("############## MENU ##############\n");
    printf("Abrir estacionamento--- (0)\n");
    printf("Adicionar carro-------- (1)\n");
    printf("Listar carros---------- (2)\n");
    printf("Retirar carro---------- (3)\n");
    printf("Cadastrar funcionarios- (4)\n");
    printf("Listar funcionarios---- (5)\n");
    printf("Ordenar funcionarios--- (6)\n");
    printf("Fechar estacionamento-- (-1)\n");

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
                            qtdLista++;
                            saldo += 12;
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
                        ruaLista = inicializaListaEst();
                        estacionamentoLista = removerCarroLista(estacionamentoLista, ruaLista, funcionario, placa, qtdLista);
                        qtdLista--;
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
                scanf("%s", optionOrdenation);
                if(strcmp(optionOrdenation,"id") == 0) {
                    selectSortID(funcionario);
                } else if(strcmp(optionOrdenation,"idade") == 0){
                    selectSortIdade(funcionario);
                } else if((strcmp(optionOrdenation,"nome") == 0)){
                    selectSortNome(funcionario);
                }
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

