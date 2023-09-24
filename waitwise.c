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
void entradaDados(int *ciclos, int *clientesPorCiclo);
void inicializaFila(dNODO **filaClientes);
void insereNaFila(dNODO **filaClientes, int numeroDoCliente);
int retiraDaFila(dNODO **filaClientes);
int velocidadeDeAtendimento();
void simulacao(int *velocidade, int *ciclos, int *clientesPorCiclo, dNODO **filaClientes);

int main(){
    int clientesPorCiclo = 0;  //numero de clientes que entram por ciclo de simulação
    int ciclos = 0; //Quantidade de simulações de entrada de clientes
    entradaDados(&ciclos, &clientesPorCiclo);
    dNODO *filaClientes;
    inicializaFila(&filaClientes);
    int velocidade = velocidadeDeAtendimento();
    simulacao(&velocidade, &ciclos, &clientesPorCiclo, &filaClientes);
}
void entradaDados(int *ciclos, int *clientesPorCiclo){
    printf("#####################################  Bem-vindo ao WaitWise  #####################################");
    printf(" \n");
    printf(" \n");
    printf("\n        Insira a quantidade de simualção (ciclos).....................: ");
    scanf("%i", &(*ciclos));
    printf("        Insira a quantidade de entrada de clientes na fila (por ciclo): ");
    scanf("%i", &(*clientesPorCiclo));

    // ambos inputs não podem ser menores que 0, caso contrário um erro de core dump será gerado
    if ((*ciclos) < 0 || (*clientesPorCiclo) < 0) {
        printf("\t\nPor favor entre com um número de inputs válido na próxima vez! \n");
        exit(EXIT_FAILURE);
    } 
}
void inicializaFila(dNODO **filaClientes){
    dNODO *ptDescritor = (dNODO*) malloc(sizeof(dNODO));
    if(ptDescritor != NULL){ //se há espaço disponivel na memoria para alocar o ponteiro ptDescritor
       ptDescritor->inicio = NULL; //inicializa cabeça da fila
       ptDescritor->fim = NULL;    //inicializa cauda da fila
       *filaClientes = ptDescritor; //cabeça da fila passa a apontar para um endereço que possui um ponteiro para o inicio e outro para o fim da fila
    }else{
       printf("Espaço de memoria insuficiente!");
       return;
    }
}
//recebe a fila e o numero do clinte que esta entrando na fila. Insere este cliente na fila
void insereNaFila(dNODO **filaClientes, int numeroDoCliente){
    NODO *novo = (NODO*) malloc(sizeof(NODO));
    if(novo != NULL){ //se ouver espaço suficiente na memoria para criar um novo nodo
       if((*filaClientes)->fim == NULL){//Se a fila não possuir nodo algum
           novo->info.cliente = numeroDoCliente;
           (*filaClientes)->fim = novo;
           (*filaClientes)->inicio = novo;
           novo->prox = NULL;
        }else{
            novo->info.cliente = numeroDoCliente;
           (*filaClientes)->fim->prox = novo; //o nodo que esta no fim da fila, passa a apontar para o novo nodo
           (*filaClientes)->fim = novo; //o fim da fila passa a apontar para o novo fim da fila, ou seja, passa a apontar para o nodo novo
           novo->prox = NULL; //o novo fim da fila passa a apontar para NULL
        }
    }else{
        printf("Espaço de memoria insuficiente!");
        return;
    }
}
//retorna 0 caso ocorra um erro
int retiraDaFila(dNODO **filaClientes){
    int numeroDoClienteQueSaiu;
    if((*filaClientes)->inicio == NULL){
        printf("A fila não possui nodos!");
        return 0;
    }else{
        if((*filaClientes)->inicio->prox == NULL){//se tiver somente um nodo
            numeroDoClienteQueSaiu = (*filaClientes)->inicio->info.cliente;
            free((*filaClientes)->inicio); //libera espaço de memoria do unico nodo
            (*filaClientes)->inicio = NULL;
            (*filaClientes)->fim = NULL;
        }else{
            NODO *aux = (NODO*) malloc(sizeof(NODO));
            if(aux == NULL){
                printf("Espaço de memoria insuficiente!");
                return 0;
            }else{
                numeroDoClienteQueSaiu = (*filaClientes)->inicio->info.cliente;
                aux = (*filaClientes)->inicio;
                (*filaClientes)->inicio = (*filaClientes)->inicio->prox;
                free(aux);
            }
        }
    }
    return ( numeroDoClienteQueSaiu );
}
//esta função deve fazer a simulação de uma fila de supermercado, mostrando os ciclos de entrada de clientes,
//a saida dos clientes e por fim deve apresentar os resuldados da simulação, isto é, as estatisticas
void simulacao(int *velocidade, int *ciclos, int *clientesPorCiclo, dNODO **filaClientes){
    int clientesAtendidos = 0; //contador, conta o numero de clientes que foram atendidos
    int clientes = 0; //contador, conta numero de clientes que entraram
    int ciclosExecutados = 0; //contador, conta o numero de ciclos executados após a ultima saida de um cliente, ou seja, sempre é zerado depois da saida de um cliente
    int i, j, clienteQueSaiu;
    for(i = 0; i < *ciclos; i++){
        printf("\n        Ciclo[%i]", i+1);
        for(j = 0; j < *clientesPorCiclo; j++){
            insereNaFila(filaClientes, clientes+1);
            printf("\n        Entrou na fila o cliente: %i", clientes+1);
            clientes++;
        }
        ciclosExecutados++;
        if (ciclosExecutados == *velocidade){ //verifica se esta na hora de tirar alguem da fila, conforme velocidade definida pela funcao velocidadeDeAtendimento
            clienteQueSaiu = retiraDaFila(filaClientes);
            printf("\n        Saiu o cliente %i", clienteQueSaiu);
            clientesAtendidos++;
            ciclosExecutados = 0;
        }
    }
    printf(" \n");
    printf(" \n");
    printf("##########################  Resultados da simulação da fila do WaitWIse  ##########################\n");
    printf("\n");
    printf("        Inicio da fila [%p].: %i\n", &(*filaClientes)->inicio,(*filaClientes)->inicio->info.cliente);
    printf("        Fim da fila    [%p].: %i\n", &(*filaClientes)->fim,(*filaClientes)->fim->info.cliente);
    printf(" \n");
    printf("        Numero de clientes atendidos........: %i\n", clientesAtendidos);
    printf("        Numero de clientes restantes na fila: %i\n", clientes - clientesAtendidos); //FAZER acho que é clientes - clientesAtendidos
    printf("        Tempo de espera na fila(ciclos).....: %i\n", *velocidade);
}
//esta funcao deve retornar um numero aleatorio, que representará a velocidade com que os clientes saem da fila
int velocidadeDeAtendimento(){
    srand(time(NULL));
    return (rand() % 6 + 1);
}