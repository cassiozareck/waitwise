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

int main(){
    int ciclo = 0;  //Tempo de simulação
    int ciclos = 0; //Quantidade de entrada de clientes na fila
    entradaDados(&ciclos, &ciclo);
    dNODO *filaClientes;
    inicializaFila(&filaClientes);

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
inicializaFila(){
       
}
