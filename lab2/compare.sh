#!/bin/sh

gcc atividade1.c -o prog -lpthread

for dimension in 500 1000 2000
do
    for threads in 1 2;
    do
        echo "Multiplicando matriz $dimension x $dimension com $threads thread(s)"
        ./prog $dimension $threads;
    done
done

rm prog
