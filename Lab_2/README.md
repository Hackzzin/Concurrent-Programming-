# Lab02 – Programação Concorrente

## Objetivo 
Projetar, implementar e avaliar uma solução concorrente para o problema de calcular o produto interno de dois vetores de números reais.

### Explicação sobre o que cada arquivo faz

`randVecGen.c` -> este arquivo será responsável por criar dois vetores aleatórios, de tamanho N (providenciado na chamada pelo usuário), calcular o produto interno de ambos de forma sequencial, e colocar num arquivo ".bin" (cujo nome também deve ser providenciado pelo usuário na chamada) o tamanho dos vetores, os vetores em si e, por fim o produto interno.

`concDotProd.c` -> este arquivo será responsável por ler os dados do arquivo binário e, de forma concorrente, calcular o produto interno dos dois vetores aleatórios. Por fim, é tirado a diferença relativa entre o resultado sequencial e o resultado concorrente.

### Como rodar 
`randVecGen.c`
<pre> gcc -o nome_executavel randVecGen.c  
./nome_executavel dimensao_n arquivoNome.bin</pre>
Substitua `nome_executavel` por qualquer nome que quiser, `dimensao_n` por um inteiro que será o número de elementos em cada vetor, e `arquivoNome` pelo nome que deseja dar ao seu arquivo binário. *É necessário a inclusão da extensão .bin logo após o nome.*
Exemplo de execução: 
`gcc -o rand randVecGen.c`
`./rand 10000 randVecGen.bin`

`randVecGen.c`
<pre> gcc -o nome_executavel concDotProd.c  
./nome_executavel nThreads arquivoNome.bin</pre>
Substitua `nome_executavel` por qualquer nome que quiser, `nThreads` por um inteiro que será o número de threads criada para a tarefa, e `arquivoNome` pelo nome do arquivo binário que deseja ler. *É necessário a inclusão da extensão .bin logo após o nome.*
Exemplo de execução:
`gcc -o dot concDotProd.c`
`./dot 10 randVecGen.bin`

### Resultado
Após a execução de ambos os códigos, segue aqui a saída do `randVecGen.c`:
<pre>Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Creating thread 8
Creating thread 9
Size of the vectors: 10000
Dot Product Read: -17042768.0000000000
Dot Product Computed Concurrently: -17042706.0000000000
Relative Error: 0.0000036379</pre>

Erro Relativo, este que é calculado da seguinte forma:
e = |(Vs - Vc) / Vs|, onde Vs é o produto interno calculado sequencialmente; e Vc, o produto interno calculado concorrentemente.

Para avaliar o código, foram testados vetores de tamanhos diferentes ao longo da execução. Contudo, o erro relativo só veio a ser (comparativamente) expressivo na casa dos 10.000 elementos. Em testes anteriores, foram testados vetores de diversos tamanhos — nas casas das unidades, dezenas, centenas e milhares —, mas o erro relativo sempre ficou muito próximo de 0. Contudo, tal fenômeno é explicável! Quantos mais dimensões temos de tratar, e quanto mais threads temos envolvidas no cálculo, mais perceptível fica a imprecisão do resultado conseguido de forma concorrente.
Outro fator que, embora não testado à vera, esteve perceptível a olhos nús, foi o quão mais rápido a computação do produto interno ficou no método concorrente conforme o número de elementos dos vetores aumentavam.
