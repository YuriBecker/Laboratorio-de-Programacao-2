#include "menu.h"

//Só assim pra funcionar essa desgraça
void aguardarTecla()
{
  fflush(NULL);
  printf("\nPressione enter para continuar!\n");
  getchar();
  getchar();
}

void limpaTela()
{
  system("clear");
}

void textoMenuPrincipal()
{
  limpaTela();
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Menu de Times");
  printf("\n2- Menu de Jogadores");
  printf("\n3- Menu de Tecnicos");
  printf("\n0- Sair");
  printf("\n\nOpcao: ");
}

void menuPrincipal(Lista *times, Lista *jogadores, bool *sair)
{
  int opc;
  textoMenuPrincipal();
  scanf("%d", &opc);
  switch (opc)
  {
  case 1:
    // menuTimes(times);
    break;
  case 2:
    menuJogadores(jogadores, times);
    break;
  case 0:
    *sair = true;
    break;
  default:
    printf("Entrada invalida!\n");
    sleep(1);
  }
}

void textoMenuJogadores()
{
  limpaTela();
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Adicionar jogador");
  printf("\n2- Remover jogador");
  printf("\n3- Listar jogadores");
  printf("\n4- Buscar jogador pelo id");
  printf("\n5- Adicionar jogador em um time");
  printf("\n6- Adicionar jogadores automaticamente");
  printf("\n0- Voltar para o menu principal");
  printf("\n\nOpcao: ");
}

void menuJogadores(Lista *jogadores, Lista *times)
{
  int opc;
  int id;
  while (opc != 0)
  {
    textoMenuJogadores();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:

      break;
    case 2:
      limpaTela();
      printf("\n\nDigite o ID do jogador a ser removido: ");
      scanf("%d", &id);
      if (buscarJogador(jogadores, id) != NULL)
      {
        jogadores = retirarJogador(jogadores, id);
        printf("\nJogador excluido com sucesso!\n");
      }
      else
        printf("\n\nJogador nao encontrado, verifique na lista de jogadores!\n\n");
      aguardarTecla();
      break;
    case 3:
      limpaTela();
      printf("\n----- Lista de Jogadores -----\n");
      imprimirJogadores(jogadores);
      aguardarTecla();
      break;
    case 4:
      limpaTela();
      printf("\n\nDigite o ID do jogador a ser buscado: ");
      scanf("%d", &id);
      if (buscarJogador(jogadores, id) != NULL)
      {
        printf("\nJogador encontrado!\n\n");
        Lista *aux = criar();
        aux = inserirFim(aux, buscarJogador(jogadores, id));
        imprimirJogador(aux->info);
        free(aux);
      }
      else
        printf("\n\nJogador nao encontrado!\n\n");
      aguardarTecla();
      break;
    case 5:

      break;
    case 6:
      jogadores = criaJogadoresAutomaticamente(jogadores);
      break;
    case 0:
      return;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}
// void menuTimes(Lista *times);
// void textoMenuTimes();
Lista *criaJogadoresAutomaticamente(Lista *jogadores)
{
  limpaTela();
  jogadores = inserirFim(jogadores, criarJogador("Pedro"));
  jogadores = inserirFim(jogadores, criarJogador("Paulo"));
  jogadores = inserirFim(jogadores, criarJogador("Mario"));
  jogadores = inserirFim(jogadores, criarJogador("Miguel"));
  jogadores = inserirFim(jogadores, criarJogador("Fernando"));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo"));
  jogadores = inserirFim(jogadores, criarJogador("Eduardo"));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo"));
  jogadores = inserirFim(jogadores, criarJogador("Jao"));
  jogadores = inserirFim(jogadores, criarJogador("Carlos"));
  jogadores = inserirFim(jogadores, criarJogador("Fabricio"));
  jogadores = inserirFim(jogadores, criarJogador("Rogerio"));
  printf("\nJogadores adicionados com sucesso!\n");
  aguardarTecla();
  return jogadores;
}