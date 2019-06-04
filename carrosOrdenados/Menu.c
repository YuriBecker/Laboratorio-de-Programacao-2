#include "Menu.h"

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
  printf("\n");
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

void menuPrincipal(Lista **carros, Arv **arvPlaca, Arv **arvMarca, Arv **arvAno, bool *sair)
{
  int opc;
  //infos para cadastro
  Carro *c = NULL;
  Arv *arvAux = NULL;
  char placa[7];
  char marca[15];
  int ano;

  textoMenuPrincipal();
  scanf("%d", &opc);
  limpaTela();
  switch (opc)
  {
  case 1:
    do
    {
      limpaTela();
      printf("\nADICIONANDO NOVO CARRO\n\n");
      printf("PLACA: ");
      scanf(" %[^\n]s", placa);
    } while (placaJaExiste(*carros, placa));
    printf("\nMARCA: ");
    scanf(" %[^\n]s", marca);
    printf("\nANO: ");
    scanf("%d", &ano);
    c = novoCarro(placa, marca, ano);
    *carros = inserirOrdenado(*carros, c);
    *arvAno = insere(*arvAno, c, ANO);
    *arvMarca = insere(*arvMarca, c, MARCA);
    *arvPlaca = insere(*arvPlaca, c, PLACA);
    limpaTela();
    printf("\n\nCARRO ADICIONADO COM SUCESSO!");
    aguardarTecla();
    break;
  case 2:
    printf("\n\nREMOVER CARRO COM A PLACA: ");
    scanf(" %[^\n]s", placa);
    c = novoCarro(placa, "", 0);
    arvAux = busca(*arvPlaca, c, PLACA);
    free(c);
    if (arvAux == NULL)
    {
      printf("\n\nPLACA NAO ENCONTRADA!");
    }
    else
    {
      *arvMarca = retira(*arvMarca, arvAux->carro);
      *arvAno = retira(*arvAno, arvAux->carro);
      *arvPlaca = retira(*arvPlaca, arvAux->carro);
      *carros = retirar(*carros, arvAux->carro->placa);
      printf("\n\nCARRO REMOVIDO COM SUCESSO!");
    }
    aguardarTecla();
    break;
  case 3:
    printf("\n\nBUSCAR PLACA: ");
    scanf(" %[^\n]s", placa);
    c = novoCarro(placa, "", 0);
    arvAux = busca(*arvPlaca, c, PLACA);
    free(c);
    if (arvAux == NULL)
    {
      printf("\n\nPLACA NAO ENCONTRADA!");
    }
    else
    {
      printf("\n\nCarro: %s - %s - %d", arvAux->carro->placa, arvAux->carro->marca, arvAux->carro->ano);
    }
    aguardarTecla();
    break;
  case 4:
    printf("\nLISTA DE CARROS ORDENADOS PELA PLACA!\n\n");
    imprimir(*carros);
    aguardarTecla();
    break;
  case 5:
    printf("\nLISTA DE CARROS ORDENADOS PELA MARCA!\n\n");
    imprime(*arvMarca);
    aguardarTecla();
    break;
  case 6:
    printf("\nLISTA DE CARROS ORDENADOS PELO ANO!\n\n");
    imprime(*arvAno);
    aguardarTecla();
    break;
  case 0:
    *sair = true;
    break;
  }
}
