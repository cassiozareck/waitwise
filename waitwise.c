/***********************************************/ 
/* Definição das Bibliotecas                    */
/***********************************************/ 
#include <stdio.h>
#include <stdlib.h>
/***********************************************/ 
/* Definição dos Registros                     */
/***********************************************/ 
typedef struct {           // registro para uma pessoa
    int cliente;
} INFORMACAO;
       
typedef struct nodo {
    INFORMACAO info;    // dados do registro
    struct nodo* prox;  // ponteiro para o próximo registro
} NODO; 

typedef struct {
    NODO* inicio;      // ponteiro para o início da estrutura
    NODO* fim;         // ponteiro para o fim da estrutura
} dNODO;                  // com descritor

/***********************************************/ 
/* Definição das Funções                       */
/***********************************************/ 
void entradaDados(int *ciclos, int *ciclo);
void inicializaFila(dNODO **filaClientes);
void insereNaFila(dNODO **filaClientes);

int main(){
    int ciclo = 0;  //Tempo de simulação
    int ciclos = 0; //Quantidade de entrada de clientes na fila
    entradaDados(&ciclos, &ciclo);
    dNODO *filaClientes;
    inicializaFila(&filaClientes);
    insereNaFila(&filaClientes);
}
void entradaDados(int *ciclos, int *ciclo){
    printf("##########################  Bem-vindo ao WaitWise  ##########################");
    printf(" \n");
    printf(" \n");
    printf("\nInsira a quantidade de simualção (ciclos).....................: ");
    scanf("%i", &(*ciclos));
    printf("Insira a quantidade de entrada de clientes na fila (por ciclo): ");
    scanf("%i", &(*ciclo));
}
void inicializaFila(dNODO **filaClientes){
    dNODO *ptDescritor = (dNODO*) malloc(sizeof(dNODO));
    if(ptDescritor != NULL){ //se há espaço disponivel na memoria para alocar o ponteiro ptDescritor
       ptDescritor->inicio = NULL; //inicializa cabeça da fista
       ptDescritor->fim = NULL;    //inicializa cauda da fila
       *filaClientes = ptDescritor; //cabeça da fila passa a apontar para um endereço que possui um ponteiro para o inicio e outro para o fim da fila
    }else{
       printf("Espaço de memoria insuficiente!");
       return;
    }
}
//insere registro no fim da fila
void insereNaFila(dNODO **filaClientes){
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if(novo != NULL){ //se ouver espaço suficiente na memoria para criar um novo nodo
       if((*filaClientes)->fim == NULL){//Se a fila não possuir nodo algum
           (*filaClientes)->fim = novo;
           (*filaClientes)->inicio = novo;
           novo->prox = NULL;
        }else{
           (*filaClientes)->fim->prox = novo; //o nodo que esta no fim da fila, passa a apontar para o novo nodo
           (*filaClientes)->fim = novo; //o fim da fila passa a apontar para o novo fim da fila, ou seja, passa a apontar para o nodo novo
           novo->prox = NULL; //o novo fim da fila passa a apontar para NULL
        }
    }else{
        printf("Espaço de memoria insuficiente!");
        return;
    }
}