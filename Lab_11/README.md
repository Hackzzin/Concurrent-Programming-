# Lab 11 – Programação Concorrente

## Objetivo 
Projetar, implementar e avaliar uma solução concorrente para o problema de checagem de primos em uma sequência de números em Java (além de aprender concorrência em Java).

### Explicação sobre as atividades
`atividade_1/MyPool.java` -> em um número N estabelecido dentro da main, as T threads (também definidas dentro do sistema) executam concorrentemente a análise de todos os números de 0 até N para ver se são primos ou não.

`atividade_3/FutureHello.java` ->  em um número N estabelecido dentro da main, as T threads (também definidas dentro do sistema) fazem a checagem de quantos primos achados dentro da sua parte local, e no final todas as partes locais são somadas, atingindo o número total de primos de 0 até N.
### Como rodar 
`atividade_1/MyPool.java`
<pre> javac MyPool.java  
java MyPool</pre>

`atividade_3/FutureHello.java`
<pre> javac FutureHello.java  
java FutureHello</pre>
