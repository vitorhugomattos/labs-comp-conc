# Laboratório 2
## Comparação de desempenho entre versões sequencial e concorrente

### Execução com matriz aleatória 500 × 500
    - 1 thread: menor tempo da versão sequencial: 0.491112 segundo.
    - 2 threads:
        - menor tempo da versão concorrente: 0.171478 segundo.
        - melhora do desempenho*: 2.863994.
    - 4 threads:
        - menor tempo da versão concorrente: 0.087142 segundo.
        - melhora do desempenho*: 5.635766.

### Execução com matriz aleatória 1000 × 1000
    - 1 thread: menor tempo da versão sequencial: 3.922926 segundos.
    - 2 threads:
        - menor tempo da versão concorrente: 1.336775 segundos.
        - melhora do desempenho*: 2.934619.
    - 4 threads:
        - menor tempo da versão concorrente: 0.676567 segundo.
        - melhora do desempenho*: 5.798281.

### Execução com matriz aleatória 2000 × 2000
    - 1 thread: menor tempo da versão sequencial: 35.003421 segundos.
    - 2 threads:
        - menor tempo da versão concorrente: 12.475287 segundos.
        - melhora do desempenho*: 2.80582.
    - 4 threads:
        - menor tempo da versão concorrente: 6.522781 segundos.
        - melhora do desempenho*: 5.366333.

*cálculo da melhora do desempenho pela fórmula: **Tsequencial / Tconcorrente**, sendo _Tsequencial_ o menor tempo para a versão sequencial terminar sua execução e _Tconcorrente_ o menor tempo da versão concorrente terminar sua execução.