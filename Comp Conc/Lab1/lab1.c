/* Nome: Matheus Oliveira Silva */
/* Dre: 119180151 */
/* Lab 1 */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS 2 //numero de threads que vamos usar 
#define ARRAYSIZE 10000 //tamanho do vetor


int array[ARRAYSIZE];
pthread_t tid[NTHREADS]; //identificadores das threads

//inicializa o array com valores sequenciais de 1 a 10000
void inicializaArray() {
    for(int i = 0; i < ARRAYSIZE; i++) {
        array[i] = i+1;
    }
}

//função executada pelas threads (eleva ao quadrado cada elemento de um array)
void *ElementoAoQuadrado (void *arg) {
    int primeiroElemento = *((int *) arg);

    for(int i = primeiroElemento; i < ARRAYSIZE; i+=2) {
        array[i] = array[i] * array[i];
    }

    free(arg); //aqui pode liberar a alocação feita na main
    pthread_exit(NULL);
}

//cria as threads
void criaThread() {
    for(int i = 0; i < NTHREADS; i++) {
        int *thread = malloc(sizeof(int));
        *thread = i;

        if (pthread_create(&tid[i], NULL, ElementoAoQuadrado, (void *) thread)) {
            printf("Erro na pthread_create()\n"); exit(-1);
        }
    }
}

//espera as threads terminarem
void waitThreadToJoin() {
    for(int i = 0; i < NTHREADS; i++) {        
        if (pthread_join(tid[i], NULL)) {
            printf("Erro na pthread_join()\n");
            exit(-1);
        }
    }
}

//verifica se os valores finais do array
void verificaArray() {
    for(int i = 0; i < ARRAYSIZE; i++) {
        int elementoEsperado = (i+1) * (i+1);
        if(array[i] != elementoEsperado) {
            printf("Erro na posição %d. Esperávamos %d, recebemos %d.\n", i, elementoEsperado, array[i]);
            return;
        }
    }
    printf("A verificação não achou erros.\n");
}

//chama todas as funções criadas anteriormente
void AllFunctions() {

    inicializaArray();

    criaThread();

    waitThreadToJoin();

    verificaArray();
}

int main() {
    
    callFunctions();
    
    return 0;
}