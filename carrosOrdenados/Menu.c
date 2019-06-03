#include "Menu.h"

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

void limpaTela()
{
  system("clear");
}

void aguardarTecla()
{
  fflush(NULL);
  printf("\n\nPressione enter para continuar!\n");
  getchar();
  getchar();
}

void textoMenuPrincipal()
{
  printf("\n\n");
  printf("MENU PRINCIPAL\n");
  printf("---------------\n");
  printf("Selecione uma opcao abaixo\n\n");
  printf("1- Adicionar carro\n");
  printf("2- Remover carro\n");
  printf("3- Buscar carro pela placa - usando a Arvore Aux\n");
  printf("4- Listar carros pela placa - usando a Lista\n");
  printf("5- Listar carros pela marca - usando a Arvore Aux\n");
  printf("6- Listar carros pelo ano - usando a Arvore Aux\n");
  printf("0- SAIR\n\n");
  printf("Opc: ");
}

void menuPrincipal(Lista **carros, bool *sair)
{
  int opc;
  textoMenuPrincipal();
  scanf("%d", &opc);
  limpaTela();

  switch (opc)
  {
  case 1:
    aguardarTecla();
    break;
  case 2:
    /* code */
    aguardarTecla();
    break;
  case 3:
    /* code */
    aguardarTecla();
    break;
  case 4:
    aguardarTecla();
    break;
  case 5:
    /* code */
    aguardarTecla();
    break;
  case 6:
    /* code */
    aguardarTecla();
    break;
  case 0:
    *sair = true;
    break;
  }
}
