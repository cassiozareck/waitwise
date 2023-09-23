/***********************************************/ 
/* Definição das Bibliotecas                    */
/***********************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
void retiraDaFila(dNODO **filaClientes);
int velocidadeDeAtendimento();

int main(){
    int ciclo = 0;  //Tempo de simulação
    int ciclos = 0; //Quantidade de entrada de clientes na fila
    entradaDados(&ciclos, &ciclo);
    dNODO *filaClientes;
    inicializaFila(&filaClientes);
    int velocidade = velocidadeDeAtendimento();
    simulacao(&velocidade, &ciclos, &ciclo, &filaClientes);
    insereNaFila(&filaClientes);//tirar daqui
    retiraDaFila(&filaClientes);//tirar daqui
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
void retiraDaFila(dNODO **filaClientes){
    if((*filaClientes)->inicio == NULL){
        printf("A fila não possui nodos!");
        return;
    }else{
        if((*filaClientes)->inicio->prox == NULL){//se tiver somente um nodo
            free((*filaClientes)->inicio); //libera espaço de memoria do unico nodo
            (*filaClientes)->inicio = NULL;
            (*filaClientes)->fim = NULL;
        }else{
            NODO *aux = (NODO*) malloc(sizeof(NODO));
            if(aux == NULL){
                printf("Espaço de memoria insuficiente!");
                return;
            }else{
                aux = (*filaClientes)->inicio;
                (*filaClientes)->inicio = (*filaClientes)->inicio->prox;
                free(aux);
            }
        }
    }
}
//esta função deve fazer a simulação de uma fila de supermercado, mostrando os ciclos de entrada de clientes,
//a saida dos clientes e por fim deve apresentar os resuldados da simulação, isto é, as estatisticas
void simulacao(int *velocidade, int *ciclos, int *ciclo, dNODO **filaClientes){

}
//esta funcao deve retornar um numero aleatorio, que representará a velocidade com que os clientes saem da fila
int velocidadeDeAtendimento(){
    srand(time(NULL));
    return (rand() % 6 + 1);
}