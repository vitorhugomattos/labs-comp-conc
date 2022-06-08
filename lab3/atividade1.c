// compara os minimos e maximos de um vetor de numeros reais
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

long int dim;  // dimensao do vetor de entrada
int nthreads;  // numero de threads
double *vetor; // vetor de entrada com dimensao dim

typedef struct
{
    int id;
    double max;
    double min;
} tArgs;

// fluxo das threads
void *tarefa(void *arg)
{
    tArgs *args = (tArgs *)arg;                     // estrutura com argumentos da thread
    double *min = (double *)malloc(sizeof(double)); // variavel com minimo local
    double *max = (double *)malloc(sizeof(double)); // variavel com maximo local

    if (min == NULL || max == NULL)
        exit(1);

    long int tamBloco = dim / nthreads; // tamanho do bloco de cada thread
    long int ini = args->id * tamBloco; // elemento inicial do bloco da thread
    long int fim;                       // elemento final (nao processado) do bloco da thread

    if (args->id == nthreads - 1)
        fim = dim;
    else
        fim = ini + tamBloco; // trata o resto se houver

    // compara os elementos do bloco da thread
    for (long int i = ini; i < fim; i++)
    {
        if (vetor[i] > args->max)
            args->max = vetor[i];
        else if (vetor[i] < args->min)
            args->min = vetor[i];
    }

    // retorna o resultado da comparacao local
    pthread_exit((void *)args);
}

// fluxo principal
int main(int argc, char *argv[])
{
    double minSeq = 500;  // minimo sequencial
    double maxSeq = 0;    // maximo sequencial
    double minConc = 500; // minimo concorrente
    double maxConc = 0;   // maximo concorrente
    double ini, fim;      // tomada de tempo
    pthread_t *tid;       // identificadores das threads no sistema
    tArgs *retorno;       // valor de retorno das threads

    // recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
    if (argc < 3)
    {
        fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
        return 1;
    }
    dim = atoll(argv[1]);
    nthreads = atoi(argv[2]);

    // aloca o vetor de entrada
    vetor = (double *)malloc(sizeof(double) * dim);
    if (vetor == NULL)
    {
        fprintf(stderr, "[ERRO] malloc\n");
        return 2;
    }

    // preenche o vetor de entrada
    srand((unsigned int)time(NULL));
    for (long int i = 0; i < dim; i++)
        vetor[i] = ((float)rand() / (float)(RAND_MAX)) * 500;

    // comparacao sequencial dos elementos
    GET_TIME(ini);
    for (long int i = 0; i < dim; i++)
    {
        if (vetor[i] > maxSeq)
            maxSeq = vetor[i];
        else if (vetor[i] < minSeq)
            minSeq = vetor[i];
    }
    GET_TIME(fim);
    printf("tempo sequencial:   %lf\n", fim - ini);

    // comparacao concorrente dos elementos
    if (nthreads > 1)
    {
        GET_TIME(ini);
        tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
        if (tid == NULL)
        {
            fprintf(stderr, "[ERRO] malloc\n");
            return 2;
        }

        // criar as threads
        for (long int i = 0; i < nthreads; i++)
        {
            tArgs *args = (tArgs *)malloc(sizeof(tArgs));
            args->id = i;
            args->max = 0;
            args->min = 500;

            if (pthread_create(tid + i, NULL, tarefa, (void *)args))
            {
                fprintf(stderr, "[ERRO] pthread_create\n");
                return 3;
            }
        }

        // aguardar o termino das threads
        for (long int i = 0; i < nthreads; i++)
        {
            if (pthread_join(*(tid + i), (void **)&retorno))
            {
                fprintf(stderr, "[ERRO] pthread_create\n");
                return 3;
            }

            // printf("min conc: %lf\n", retorno->min);

            // comparacao global
            if (retorno->max > maxConc)
                maxConc = retorno->max;
            else if (retorno->min < minConc)
                minConc = retorno->min;
        }
        GET_TIME(fim);
        printf("tempo concorrente:  %lf\n", fim - ini);
        free(tid);
    }

    // exibir os resultados
    printf("minimo sequencial:  %.12lf; maximo sequencial:  %.12lf\n", minSeq, maxSeq);
    if (nthreads > 1)
        printf("minimo concorrente: %.12lf; maximo concorrente: %.12lf\n", minConc, maxConc);

    // libera as areas de memoria alocadas
    free(vetor);

    return 0;
}