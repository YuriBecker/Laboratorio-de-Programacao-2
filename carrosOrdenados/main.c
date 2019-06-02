// Considere uma lista de carros, onde cada carro possui os seguintes campos: placa, marca e ano. Crie um programa com os seguintes requisitos:
// 1. A lista deve ser ordenada fisicamente pela placa dos carros.
// 2. Deve ser possivel incluir e excluir carros na lista.
// 3. Deve ser mantida em memória uma árvore binária relativa à placa dos carros.
// 4. Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pelo marca.
// 5. Deve ser mantida em memória uma árvore binária cujo percurso seja equivalente à lista ordenada pela ano.
// 6. Deve ser possível buscar carros pela placa, usando a árvore binária auxiliar.
// 7. Deve ser possivel listar os carros ordenadamente pela placa, percorrendo a lista.
// 8. Deve ser possivel listar os carros ordenadamente pelo marca, através da árvore auxiliar.
// 9. Deve ser possivel listar os carros ordenadamente pela ano, através da árvore auxiliar.

// scanf(" %[^\n]s", nome);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Carro.h"

int main()
{
  Lista *carros = criar();
  carros = inserirOrdenado(carros, novoCarro("C", "P1", 2019));
  carros = inserirOrdenado(carros, novoCarro("A", "P1", 2019));
  carros = inserirOrdenado(carros, novoCarro("B", "P1", 2019));
  imprimir(carros);
  carros = retirar(carros, "B");
  imprimir(carros);
  printf("\n %d", placaJaExiste(carros, "B"));
}