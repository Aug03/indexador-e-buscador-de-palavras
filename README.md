# indexador-e-buscador-de-palavras
É um indexador e um buscador de palavras escrito em C.

Encontre o número de comparações feitas para buscar de uma palavra em um texto qualquer usando duas estruturas de dados diferentes para construir o índice: Lista ligada ou Árvore Binária. É possível, assim, testar empiricamente sua complexidade assintótica.
Também obtenha o número de comparações realizadas para a inserção dos elementos em cada um dos índices, para comparar o custo de inserção.

Lista Ligada:
  -Custo de Inserção: O(N^2) pois, é necessário comparar N elementos com M já inseridos, para que não hajam elementos repetidos.
  -Custo de Busca:  O(N) pois, é necessário percorrer todos os elementos da lista, caso o elemento procurado esteja na posição (n-1).

Árvore Binária:
  -Custo de Inserção: O(N.logN) pois, é necessário comparar N elementos com H elementos, sendo H a altura da árvore. Idealmente balanceada, a altura H tem logN elementos.
  -Custo de Busca:  O(logN) pois, o número de comparações é igual à altura da árvore, e idealmente, H = logN.
