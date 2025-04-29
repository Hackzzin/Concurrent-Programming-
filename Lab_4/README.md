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
Para 1.000.000 de elementos na sequência, foram rodado 5 vezes o programa para os seguintes valores de threads: 1 (sequencial/base), 2 e 4. Os resultados obtidos estão no arquivo .txt.

Aceleração(n, t) = Ts(n) / Tp(n, t)
Eficiência(n, t) = A(n, t)/t

Para 1 thread:
Ts = 90,4758612 ms
Tp = 90,4758612 ms
Aceleração = 1
Eficiência = 1

Para 2 threads:
Ts = 90,4758612 ms
Tp = 92,536362 ms
Aceleração = 0,9777330688664852
Eficiência = 0,4888665344332426

Para 4 threads:
Ts = 90,4758612 ms
Tp = 55,071165 ms
Aceleração = 1,642889907994501
Eficiência = 0,4107224769986253

