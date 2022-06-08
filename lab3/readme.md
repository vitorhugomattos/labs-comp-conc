# Laboratório 3
## Comparação de desempenho entre versões sequencial e concorrente

### Execução com vetor aleatório de 100000 elementos
    - 1 thread: menor tempo da versão sequencial: 0.000153 segundo.
    - 2 threads:
        - menor tempo da versão concorrente: 0.000274 segundo.
        - melhora do desempenho*: 0.558394 **(o desempenho piorou)**.
    - 4 threads:
        - menor tempo da versão concorrente: 0.000174 segundo.
        - melhora do desempenho*: 0.879310 **(o desempenho piorou)**.

### Execução com vetor aleatório de 10000000 elementos
    - 1 thread: menor tempo da versão sequencial: 0.015370 segundo.
    - 2 threads:
        - menor tempo da versão concorrente: 0.013173 segundo.
        - melhora do desempenho*: 1.166780.
    - 4 threads:
        - menor tempo da versão concorrente: 0.008530 segundo.
        - melhora do desempenho*: 1.801875.

### Execução com vetor aleatório de 100000000 elementos
    - 1 thread: menor tempo da versão sequencial: 0.157311 segundo.
    - 2 threads:
        - menor tempo da versão concorrente: 0.100600 segundo.
        - melhora do desempenho*: 1.563727.
    - 4 threads:
        - menor tempo da versão concorrente: 0.051356 segundo.
        - melhora do desempenho*: 3.063147.

*cálculo da melhora do desempenho pela fórmula: **Tsequencial / Tconcorrente**, sendo _Tsequencial_ o menor tempo para a versão sequencial terminar sua execução e _Tconcorrente_ o menor tempo da versão concorrente terminar sua execução.