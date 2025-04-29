# Lab04 – Programação Concorrente

## Objetivo 
Projetar, implementar e avaliar a implementação de um problema de contagem de primos em uma sequência de maneira concorrente.

### Explicação sobre o que cada arquivo faz

`primeCheck.c` -> este arquivo será responsável por criar receber pela linha de comando o maior número da sequência de números a serem checadas e o número de threads. O resultado é colocado no arquivo "results.txt". 
`results.txt` -> este arquivo será responsável por conter os tempos de execução de cada tentativa e o número de primos vistos na sequências.
`primeCheck.c`
<pre> gcc -o nome_executavel primeCheck.c -lrt -lm 
./nome_executavel dimensao_n num_threads</pre>
Substitua `nome_executavel` por qualquer nome que quiser, `dimensao_n` por um inteiro que será o maior número da sequência.
Exemplo de execução: 
`gcc -o prime primeCheck.c -lrt -lm`
`./prime 1000000 2`

### Resultado
Para 10.000.000 de elementos na sequência, foi rodado 5 vezes o programa para os seguintes valores de threads: 1 (sequencial/base), 2 e 4. Os resultados obtidos estão no arquivo .txt.

| Threads | Tempo médio (s) | Aceleração  | Eficiência (%) |
|---------|---------------|------------------------|----------------|
| 1       | 2,188552      | 1,00×                  | 100,00%        |
| 2       | 1,449690      | 1,51×                  | 75,75%         |
| 4       | 0,909185      | 2,41×                  | 60,14%         |


Para 10.000 de elementos na sequência:

| Threads | Tempo médio (ms) | Aceleração  | Eficiência (%) |
|---------|----------------|------------------------|----------------|
| 1       | 0,766 ms       | 1,00×                  | 100,00%        |
| 2       | 0,437 ms       | 1,75×                  | 87,49%         |
| 4       | 0,417 ms       | 1,83×                  | 45,87%         |

