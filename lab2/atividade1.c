/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 2 */
/* Codigo: Multiplicar 2 matrizes quadradas paralelamente usando threads */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"

// struct para guardar dados das matrizes
typedef struct
{
    size_t dimension;
    float *elements;
} Matrix;

// struct para guardar os argumentos para as threads
typedef struct
{
    size_t threadNumber;
    size_t threadsQuantity;
    Matrix *A;
    Matrix *B;
    Matrix *C;
} tArgs;

void multiply_matrices_sequential(tArgs *arg);
void *multiply_matrices_parallel(void *arg);

int main(int argc, char const *argv[])
{
    // garante que o programa foi chamado com o número certo de argumentos
    if (argc != 3)
    {
        printf("[ERRO] Utilização: %s <dimensão das matrizes> <quantidade de threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // converte os argumentos para inteiros
    size_t matricesDimension = (size_t)atoi(argv[1]);
    size_t threadsQuantity = (size_t)atoi(argv[2]);

    // inicialização do gerador de números randômicos
    long int zero = time(NULL);
    srand((unsigned)zero);

    // criação das variáveis
    tArgs *arg = (tArgs *)malloc(sizeof(tArgs));
    Matrix *A = (Matrix *)malloc(sizeof(Matrix));
    A->elements = (float *)malloc(sizeof(float) * matricesDimension * matricesDimension);
    Matrix *B = (Matrix *)malloc(sizeof(Matrix));
    B->elements = (float *)malloc(sizeof(float) * matricesDimension * matricesDimension);
    Matrix *sequentialResult = (Matrix *)malloc(sizeof(Matrix));
    sequentialResult->elements = (float *)malloc(sizeof(float) * matricesDimension * matricesDimension);
    Matrix *parallelResult = (Matrix *)malloc(sizeof(Matrix));
    parallelResult->elements = (float *)malloc(sizeof(float) * matricesDimension * matricesDimension);

    if (A == NULL || B == NULL || sequentialResult == NULL || parallelResult == NULL || A->elements == NULL || B->elements == NULL || sequentialResult->elements == NULL || parallelResult->elements == NULL)
    {
        printf("[ERRO] malloc()\n");
        exit(EXIT_FAILURE);
    }

    double start, end, delta = 0; // variáveis para contagem de tempo

    // inicialização das variáveis
    A->dimension = B->dimension = sequentialResult->dimension = parallelResult->dimension = matricesDimension;

    for (size_t position = 0; position < (matricesDimension * matricesDimension); position++)
    {
        A->elements[position] = (float)rand() / (float)(RAND_MAX)*50;
        B->elements[position] = (float)rand() / (float)(RAND_MAX)*50;
        sequentialResult->elements[position] = 0;
        parallelResult->elements[position] = 0;
    }

    // multiplicação sequencial das matrizes

    if (arg == NULL)
    {
        printf("[ERRO] malloc()\n");
        exit(EXIT_FAILURE);
    }

    GET_TIME(start);
    arg->threadNumber = 0;
    arg->threadsQuantity = 1;
    arg->A = A;
    arg->B = B;
    arg->C = sequentialResult;

    multiply_matrices_sequential(arg);
    GET_TIME(end);

    printf("Tempo do algoritmo sequencial: %f\n", end - start);

    free(arg);

    // multiplicação paralela das matrizes
    start = end = delta = 0;
    pthread_t threadsIdentifiers[threadsQuantity];
    tArgs *args = (tArgs *)malloc(sizeof(tArgs) * threadsQuantity);

    GET_TIME(start);
    for (size_t threadNumber = 0; threadNumber < threadsQuantity; threadNumber++)
    {
        (&args[threadNumber])->threadNumber = threadNumber;
        (&args[threadNumber])->threadsQuantity = threadsQuantity;
        (&args[threadNumber])->A = A;
        (&args[threadNumber])->B = B;
        (&args[threadNumber])->C = parallelResult;

        if (pthread_create(&threadsIdentifiers[threadNumber], NULL, multiply_matrices_parallel, (void *)&args[threadNumber]))
        {
            printf("[ERRO] pthread_create()\n");
            exit(EXIT_FAILURE);
        }
    }

    for (size_t threadNumber = 0; threadNumber < threadsQuantity; threadNumber++)
    {
        if (pthread_join(threadsIdentifiers[threadNumber], NULL))
        {
            printf("[ERRO] pthread_join()\n");
            exit(EXIT_FAILURE);
        }
    }
    GET_TIME(end);

    printf("Tempo do algoritmo paralelo: %f\n", end - start);

    printf("Checando matrizes finais...\n");
    int errorFound = 0;
    for (int index = 0; index < (matricesDimension * matricesDimension); index++)
    {
        if (sequentialResult->elements[index] != parallelResult->elements[index])
        {
            errorFound = 1;
            printf("\t[ERRO] Valores diferentes encontrados no índice %d: algoritmo sequencial: %f / algoritmo paralelo: %f;\n", index, sequentialResult->elements[index], parallelResult->elements[index]);
        }
    }

    if (!errorFound)
        printf("[INFO] Nenhum erro encontrado.\n");

    free(A);
    free(B);
    free(sequentialResult);
    free(parallelResult);
    free(args);

    return 0;
}

void multiply_matrices_sequential(tArgs *arg)
{
    size_t matricesDimension = arg->A->dimension;

    for (size_t i = 0; i < matricesDimension; i++)
    {
        for (size_t j = 0; j < matricesDimension; j++)
        {
            for (size_t k = 0; k < matricesDimension; k++)
            {
                arg->C->elements[i * matricesDimension + j] += arg->A->elements[i * matricesDimension + k] * arg->B->elements[k * matricesDimension + j];
            }
        }
    }
}

void *multiply_matrices_parallel(void *arg)
{
    // definição das variáves
    tArgs *args = (tArgs *)arg;
    size_t matricesDimension = args->A->dimension;

    float temporary = 0.0;

    for (size_t i = args->threadNumber; i < matricesDimension; i += args->threadsQuantity)
    {
        for (size_t j = 0; j < matricesDimension; j++)
        {
            for (size_t k = 0; k < matricesDimension; k++)
            {
                temporary += args->A->elements[i * matricesDimension + k] * args->B->elements[k * matricesDimension + j];
            }

            args->C->elements[i * matricesDimension + j] = temporary;
            temporary = 0;
        }
    }

    pthread_exit(NULL);
}
