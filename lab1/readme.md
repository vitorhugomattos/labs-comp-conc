# Laboratório 1
Vitor Hugo Mattos // 117054396
## Respostas das questões 

### Atividade 1
Sim, há mudança na ordem de execução. Isso ocorre porque fica a cargo do sistema operacional organizar a execução das threads, ou seja, está fora do escopo e do controle da thread "pai".

### Atividade 2
Dessa vez cada thread recebeu e imprimiu o íncide do `for` que a thread principal estava rodando ao criá-la.

### Atividade 3
Não, pois há um erro na hora da thread imprimir sua "apresentação": ela conta seu próprio índice começando pelo 0, o que impede que o último índice seja igual ao número de total de threads.

### Atividade 4
Dessa vez a thread principal foi sempre a última a terminar, pois esperou o fim da execução de todas as outras threads que ela mesma havia criado.
