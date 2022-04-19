/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Módulo 1 - Laboratório: 1 */
/* Codigo: Elevar ao quadrado todos elementos de um vetor usando threads */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2
#define NELEMENTS 10000

void *make_square(void *arg);

typedef struct
{
    size_t threadNumber;
    int *arr_ptr;
} t_Args;

int main(int argc, char const *argv[])
{
    // declara e preenche o array para fazer os quadrados
    int *arr = (int *)malloc(NELEMENTS * sizeof(int));
    for (size_t index = 0; index < NELEMENTS; index++)
    {
        arr[index] = (int)index + 1;
    }

    pthread_t threadsIdentifiers[NTHREADS];
    t_Args *arg;

    for (size_t threadNumber = 0; threadNumber < NTHREADS; threadNumber++)
    {
        arg = malloc(sizeof(t_Args));
        if (arg == NULL)
        {
            printf("[ERRO] malloc()\n");
            exit(-1);
        }
        arg->threadNumber = threadNumber;
        arg->arr_ptr = arr;

        if (pthread_create(&threadsIdentifiers[threadNumber], NULL, make_square, (void *)arg))
        {
            printf("[ERRO] pthread_create()\n");
            exit(-1);
        }
    }

    // espera as threads terminarem
    for (size_t thread = 0; thread < NTHREADS; thread++)
    {
        if (pthread_join(threadsIdentifiers[thread], NULL))
        {
            printf("[ERRO] pthread_join()\n");
            exit(-1);
        }
    }

    printf("Checando vetor final...\n");
    int errorFound = 0;
    for (int index = 0; index < NELEMENTS; index++)
    {
        int value = (index + 1) * (index + 1);
        if (value != arr[index])
        {
            errorFound = 1;
            printf("\t[ERRO] Valor %d encontrado no índice %d, deveria ser %d;\n", arr[index], index, value);
        }
    }

    if (!errorFound)
        printf("[INFO] Nenhum erro encontrado.\n");

    return 0;
}

void *make_square(void *arg)
{
    t_Args *args = (t_Args *)arg;

    for (size_t index = args->threadNumber; index < NELEMENTS; index += NTHREADS)
    {
        args->arr_ptr[index] = args->arr_ptr[index] * args->arr_ptr[index];
    }

    free(arg);
    pthread_exit(NULL);
}