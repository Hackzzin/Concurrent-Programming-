# Lab08 – Programação Concorrente

## Objetivo 
Projetar, implementar e avaliar a implementação de um problema de contagem de primos em uma sequência de maneira concorrente com o uso de uma thread produtora e nCons threads consumidoras.

### Explicação sobre o que cada arquivo faz

`primeCocProd.c` -> este arquivo será responsável por criar receber pela linha de comando o maior número da sequência de números a serem checadas,  o número de threads consumidoras e o tamanho do buffer em que as threads irão manusear. O resultado é colocado no arquivo "results.txt". 

`results.txt` -> este arquivo será responsável por conter os tempos de execução de cada tentativa, o número de primos vistos na sequências, a thread consumidora que mais achou primos, o tamanho do buffer e o número total de threads consumidoras.
`primeCocProd.c`
<pre> gcc -o nome_executavel primeCocDot.c -lpthread -lm 
./nome_executavel número_de_elementos número_de_consumidores tamanho_do_buffer</pre>
Substitua `nome_executavel` por qualquer nome que quiser, `número_de_elementos` por um inteiro que será o maior número da sequência, `número_de_consumidores` pelo número de threads consumidoras no programa, e `tamanho_do_buffer`.
Exemplo de execução: 
`gcc -o prime primeCocProd.c -lpthread -lm`
`./prime 1000000 8 100`

### Resultado
Além do arquivo criado que contém o exemplo de algumas execuções, o programa também da print em alguns resultados encontrados. Segue abaixo um exemplo desse print para 10.000.000 de elementos:
`
Total primes found: 664579
Winner consumer thread: 1 (with 167771 primes found)
`

Um fato interessante que ficou evidenciado no `results.txt` é que as vezes, apesar do número de threads consumidoras aumentar, ao invés do programa ficar mais rápido (que é mais intuitivo), ele acaba ficando mais devagar! Isso se dá pelo tamanho do buffer não ser grande o suficiente, o que acaba gerando muita espera.

