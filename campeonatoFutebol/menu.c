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
  printf("\n3- Menu de Treinadores");
  printf("\n0- Sair");
  printf("\n\nOpcao: ");
}

void menuPrincipal(Lista **times, Lista **jogadores, Lista **treinadores, bool *sair)
{
  int opc;
  textoMenuPrincipal();
  scanf("%d", &opc);
  switch (opc)
  {
  case 1:
    *times = menuTimes(*jogadores, *times);
    break;
  case 2:
    *jogadores = menuJogadores(*jogadores, *times);
    break;
  case 3:
    *treinadores = menuTreinadores(*treinadores, *times);
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
  printf("\n6- Remover jogador do time");
  printf("\n7- Adicionar jogadores automaticamente");
  printf("\n0- Voltar para o menu principal");
  printf("\n\nOpcao: ");
}

Lista *menuJogadores(Lista *jogadores, Lista *times)
{
  int opc = 1;
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
        Jogador *aux = buscarJogador(jogadores, id);
        if (aux->idTime > 0)
        {
          Time *aux2 = buscarTime(times, aux->idTime);
          desinscrever(aux2, aux->id);
          printf("\nJogador removido do time %s!\n", aux2->nome);
        }
        printf("\nJogador %s excluido com sucesso!\n", buscarJogador(jogadores, id)->nome);
        jogadores = retirarJogador(jogadores, id);
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
        imprimirJogadores(aux);
      }
      else
        printf("\n\nJogador nao encontrado!\n\n");
      aguardarTecla();
      break;
    case 5:
      limpaTela();
      printf("\n\nDigite o ID do jogador: ");
      scanf("%d", &id);
      if (buscarJogador(jogadores, id) != NULL)
      {
        Jogador *jogador = buscarJogador(jogadores, id);
        if (jogador->idTime > 0)
        {
          printf("\n\nJogador ja esta em algum time\n");
        }
        else
        {
          printf("\n\nDigite o ID do time: ");
          scanf("%d", &id);
          if (buscarTime(times, id) != NULL)
          {
            Time *t = buscarTime(times, id);
            inscrever(t, jogador);
            printf("\n\nJogador %s entrou para o time %s!\n", jogador->nome, t->nome);
          }
          else
            printf("\n\nTime nao encontrado!\n\n");
        }
      }
      else
      {
        printf("\n\nJogador nao encontrado!\n\n");
      }
      aguardarTecla();
      break;
    case 6:
      limpaTela();
      printf("\n\nDigite o ID do jogador: ");
      scanf("%d", &id);
      if (buscarJogador(jogadores, id) != NULL)
      {
        Jogador *aux = buscarJogador(jogadores, id);
        if (aux->idTime > 0)
        {
          Time *aux2 = buscarTime(times, aux->idTime);
          desinscrever(aux2, aux->id);
          printf("\nJogador %s removido do time %s!\n", aux->nome, aux2->nome);
        }
        else
        {
          printf("\nJogador nao faz parte de nenhum time!\n");
        }
      }
      else
      {
        printf("\nJogador nao encontrado!\n");
      }
      aguardarTecla();
      break;
    case 7:
      jogadores = criaJogadoresAutomaticamente(jogadores);
      break;
    case 0:
      return jogadores;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}

Lista *criaJogadoresAutomaticamente(Lista *jogadores)
{
  limpaTela();
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  jogadores = inserirFim(jogadores, criarJogador("Paulo", GOLEIRO, 20, 1));
  jogadores = inserirFim(jogadores, criarJogador("Mario", ZAGUEIRO, 25, 3));
  jogadores = inserirFim(jogadores, criarJogador("Miguel", ATACANTE, 21, 4));
  jogadores = inserirFim(jogadores, criarJogador("Fernando", ZAGUEIRO, 22, 5));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ATACANTE, 25, 6));
  jogadores = inserirFim(jogadores, criarJogador("Eduardo", ZAGUEIRO, 25, 7));
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  jogadores = inserirFim(jogadores, criarJogador("Marcos", GOLEIRO, 20, 1));
  jogadores = inserirFim(jogadores, criarJogador("Daniel", ZAGUEIRO, 25, 3));
  jogadores = inserirFim(jogadores, criarJogador("Lucas", ATACANTE, 21, 4));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ZAGUEIRO, 22, 5));
  jogadores = inserirFim(jogadores, criarJogador("Ze", ATACANTE, 25, 6));
  jogadores = inserirFim(jogadores, criarJogador("Marcelo", ZAGUEIRO, 25, 7));
  printf("\nJogadores adicionados com sucesso!\n");
  aguardarTecla();
  return jogadores;
}

void textoMenuTimes()
{
  limpaTela();
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Criar time");
  printf("\n2- Remover time");
  printf("\n3- Listar times");
  printf("\n4- Buscar time pelo id");
  printf("\n5- Adicionar times automaticamente");
  printf("\n0- Voltar para o menu principal");
  printf("\n\nOpcao: ");
}

Lista *menuTimes(Lista *jogadores, Lista *times)
{
  int opc;
  int id;
  while (opc != 0)
  {
    textoMenuTimes();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:

      break;
    case 2:
      limpaTela();
      printf("\n\nDigite o ID do time a ser excluido: ");
      scanf("%d", &id);
      if (buscarTime(times, id) != NULL)
      {
        if (buscarTime(times, id)->jogadores == NULL)
        {
          printf("\nTime %s excluido com sucesso!\n", (buscarTime(times, id))->nome);
          times = retirarTime(times, id);
        }
        else
        {
          printf("\nRemova antes os jogadores do %s para poder excluir o time!\n", (buscarTime(times, id))->nome);
        }
      }
      else
        printf("\n\nTime nao encontrado, verifique o ID na lista de times!\n\n");
      aguardarTecla();
      break;
    case 3:
      limpaTela();
      printf("\n----- Lista de Times -----\n");
      imprimirTimes(times);
      aguardarTecla();
      break;
    case 4:
      limpaTela();
      printf("\n\nDigite o ID do time a ser buscado: ");
      scanf("%d", &id);
      if (buscarTime(times, id) != NULL)
      {
        printf("\nTime encontrado!\n\n");
        Lista *aux = criar();
        aux = inserirFim(aux, buscarTime(times, id));
        imprimirTimes(aux);
      }
      else
        printf("\n\nTime nao encontrado!\n\n");
      aguardarTecla();
      break;
    case 5:
      times = criaTimesAutomaticamente(times);
      break;
    case 0:
      return times;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}

Lista *criaTimesAutomaticamente(Lista *times)
{
  times = inserirFim(times, criarTime("Gremio"));
  times = inserirFim(times, criarTime("Inter"));
  times = inserirFim(times, criarTime("Flamengo"));
  times = inserirFim(times, criarTime("Sao Paulo"));
  times = inserirFim(times, criarTime("Sport"));
  limpaTela();
  printf("\nTimes criados com sucesso!\n");
  aguardarTecla();
  return times;
}

void textoMenuTreinadores()
{
  limpaTela();
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Adicionar treinador");
  printf("\n2- Remover treinador");
  printf("\n3- Listar treinadores");
  printf("\n4- Buscar treinador pelo id");
  printf("\n5- Associar treinador com algum time");
  printf("\n6- Remover treinador do time");
  printf("\n0- Voltar para o menu principal");
  printf("\n\nOpcao: ");
}

Lista *menuTreinadores(Lista *treinadores, Lista *times)
{
  int opc = 1;
  int id;
  while (opc != 0)
  {
    textoMenuTreinadores();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      limpaTela();
      char nome[50];
      printf("\nDigite o nome do treinador: ");
      scanf("%s", nome);
      treinadores = inserirFim(treinadores, criarTreinador(nome));
      printf("\nTreinador criado com sucesso!\n");
      aguardarTecla();
      break;
    case 2:
      limpaTela();
      printf("\n\nDigite o ID do treinador a ser removido: ");
      scanf("%d", &id);
      if (buscarTreinador(treinadores, id) != NULL)
      {
        Treinador *aux = buscarTreinador(treinadores, id);
        if (aux->idTime > 0)
        {
          Time *aux2 = buscarTime(times, aux->idTime);
          aux2->idTreinador = -1;
          printf("\nTreinador removido do time %s!\n", aux2->nome);
        }
        printf("\nTreinador %s excluido com sucesso!\n", buscarTreinador(treinadores, id)->nome);
        treinadores = retirarTreinador(treinadores, id);
      }
      else
        printf("\n\nJogador nao encontrado, verifique na lista de jogadores!\n\n");
      aguardarTecla();
      break;
    case 3:
      limpaTela();
      printf("\n----- Lista de Treinadores -----\n");
      imprimirTreinadores(treinadores);
      aguardarTecla();
      break;
    case 4:
      limpaTela();
      printf("\n\nDigite o ID do jogador a ser buscado: ");
      scanf("%d", &id);
      if (buscarTreinador(treinadores, id) != NULL)
      {
        printf("\nTreinador encontrado!\n\n");
        Lista *aux = criar();
        aux = inserirFim(aux, buscarTreinador(treinadores, id));
        imprimirTreinadores(aux);
      }
      else
        printf("\n\nTreinador nao encontrado!\n\n");
      aguardarTecla();
      break;
    case 5:
      limpaTela();
      printf("\n\nDigite o ID do treinador: ");
      scanf("%d", &id);
      if (buscarTreinador(treinadores, id) != NULL)
      {
        Treinador *treinador = buscarTreinador(treinadores, id);
        if (treinador->idTime > 0)
        {
          printf("\n\nTreinador ja esta treinando algum time\n");
        }
        else
        {
          printf("\n\nDigite o ID do time: ");
          scanf("%d", &id);
          if (buscarTime(times, id) != NULL)
          {
            if (buscarTime(times, id)->idTreinador < 0)
            {
              Time *t = buscarTime(times, id);
              t->idTreinador = treinador->id;
              treinador->idTime = t->id;
              printf("\n\n%s agora treina o time %s!\n", treinador->nome, t->nome);
            }
            else
            {
              printf("\n\nTime %s ja possui treinador!\n", buscarTime(times, id)->nome);
            }
          }
          else
            printf("\n\nTime nao encontrado!\n\n");
        }
      }
      else
      {
        printf("\n\nJogador nao encontrado!\n\n");
      }
      aguardarTecla();
      break;
    case 6:
      limpaTela();
      printf("\n\nDigite o ID do treinador: ");
      scanf("%d", &id);
      if (buscarTreinador(treinadores, id) != NULL)
      {
        Treinador *aux = buscarTreinador(treinadores, id);
        Time *aux2 = buscarTime(times, aux->idTime);
        if (aux->idTime > 0)
        {
          aux2->idTreinador = -1;
          aux->idTime = -1;
          printf("\n%s não é mais o treinador do time %s!\n", aux->nome, aux2->nome);
        }
        else
        {
          printf("\n%s não é treinador de nenhum time!\n", aux->nome);
        }
      }
      else
        printf("\n\nJogador nao encontrado, verifique na lista de jogadores!\n\n");
      aguardarTecla();
      break;
      break;
    case 0:
      return treinadores;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}