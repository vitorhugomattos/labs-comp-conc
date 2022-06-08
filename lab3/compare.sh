#!/bin/sh

gcc atividade1.c -o prog -lpthread -Wall

for dimensao in 100000 10000000 100000000
do
    for threads in 1 2 4;
    do
        echo "Comparando vetor aleatorio de $dimensao elementos com $threads thread(s)"
        ./prog $dimensao $threads;
        echo ""
    done
done

rm prog
