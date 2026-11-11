# indexador-e-buscador-de-palavras
É um indexador e um buscador de palavras escrito em C.

Encontre todas as ocorrências de uma palavra em um texto qualquer (em quais linhas ela apareceu e quantas vezes), além do número de comparações feitas para buscá-la, usando duas estruturas de dados diferentes para construir o índice remissivo: Lista ligada ou Árvore Binária. É possível, assim, testar empiricamente sua complexidade assintótica.
Também obtenha o número de comparações realizadas para a inserção dos elementos em cada um dos índices, para comparar o custo de inserção. 

Lista Ligada:

  -Custo de Inserção: O(N^2) pois, é necessário comparar N elementos com M já inseridos, para que não hajam elementos repetidos.
  
  -Custo de Busca:  O(N) pois, é necessário percorrer todos os elementos da lista, caso o elemento procurado esteja na posição (n-1).
  

Árvore Binária:


  -Custo de Inserção: O(N.logN) pois, é necessário comparar N elementos com H elementos, sendo H a altura da árvore. Idealmente balanceada, a altura H tem logN elementos.


  -Custo de Busca:  O(logN) pois, o número de comparações é igual à altura da árvore, e idealmente, H = logN.



                                                    --------- Como compilar e rodar ---------

Compilação com lista:

gcc -Wall -o ep main2.c texto2.c indice_lista2.c 


Compilação com árvore:

gcc -Wall -o ep main2.c texto2.c indice_arvore2.c 


Execução no terminal (obs: o arquivo deve ser de formato .txt):

./ep <arquivo> <lista|arvore>


Utilização pós execução:

busca <palavra>


Para finalizar o programa:

fim
