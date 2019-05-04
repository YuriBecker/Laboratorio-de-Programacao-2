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
  printf("-------Menu Inicial--------\n");
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Menu de Times");
  printf("\n2- Menu de Jogadores");
  printf("\n3- Menu de Treinadores");
  printf("\n4- Iniciar Campeonato Mata Mata");
  printf("\n0- Sair");
  printf("\n\nOpcao: ");
}

void menuPrincipal(Lista **times, Lista **jogadores, Lista **treinadores, Lista **rodadas, bool *sair)
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
  case 4:
    textoAvisoCampeonato();
    if (verificarTimes(*times))
    {
      int opc;
      printf("\nTUDO CERTO! DESEJA INICIAR O CAMPEONATO ?\n  1- SIM\n  2-NAO\n\nOpc:");
      scanf("%d", &opc);
      if (opc == 1)
      {
        iniciarCampeonato(*jogadores, *times, *rodadas);
      }
      else
      {
        return;
      }
    }
    else
    {
      aguardarTecla();
    }
    break;
  case 0:
    *sair = true;
    break;
  default:
    printf("Entrada invalida!\n");
    sleep(1);
  }
}

void textoAvisoCampeonato()
{
  limpaTela();
  printf("\n\n Para iniciar o campeonato voce precisa de:\n");
  printf(" * 2, 4, 8, 16, 32 ou 64 Times cadastrados (Alguma potencia de 2)\n");
  printf(" * Todos times devem ter no minimo 7 e no maximo 25 jogadores\n");
  printf(" * Todos times precisam de pelo menos um goleiro\n");
  printf(" * Todos times precisam de um tecnico\n");
  printf(" * Depois de iniciar o campeonato voce nao podera alterar (Adicionar ou Remover)\n os jogadores, times ou treinadores!\n");
  printf(" * A unica mudanca que podera fazer é a troca da escalacao dos times antes de \ncada partida!\n");
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
  printf("\n7- Adicionar jogadores e colocar nos times automaticamente");
  printf("\n0- Voltar para o menu principal");
  printf("\n\nOpcao: ");
}

Lista *menuJogadores(Lista *jogadores, Lista *times)
{
  int opc = 1;
  int id;
  char nome[50];
  int posicao;
  int idade;
  int numCamisa;
  while (opc != 0)
  {
    textoMenuJogadores();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      limpaTela();
      printf("\n\nDigite o nome do jogador: ");
      scanf(" %[^\n]s", nome);
      do
      {
        printf("\n\nQual a posicao do jogador (0- Goleiro, 1- Atacante, 2- Zagueiro) : ");
        scanf("%d", &posicao);
      } while (posicao < 0 || posicao > 2);
      do
      {
        printf("\n\nIdade do jogador: ");
        scanf("%d", &idade);
      } while (idade < 1);
      do
      {
        printf("\n\nNumero da camisa: ");
        scanf("%d", &numCamisa);
      } while (numCamisa < 1 || numCamisa > 99);
      jogadores = inserirFim(jogadores, criarJogador(nome, posicao, idade, numCamisa));
      printf("\nJogador adicionado com sucesso!\n");
      aguardarTecla();
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
      jogadores = criaJogadoresAutomaticamente(jogadores, times);
      break;
    case 0:
      return jogadores;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}

Lista *criaJogadoresAutomaticamente(Lista *jogadores, Lista *times)
{
  limpaTela();
  //TIME 1
  jogadores = inserirFim(jogadores, criarJogador("Paulo", GOLEIRO, 20, 1));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 1));
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 2));
  jogadores = inserirFim(jogadores, criarJogador("Mario", ZAGUEIRO, 25, 3));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 3));
  jogadores = inserirFim(jogadores, criarJogador("Miguel", ATACANTE, 21, 4));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 4));
  jogadores = inserirFim(jogadores, criarJogador("Fernando", ZAGUEIRO, 22, 5));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 5));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ATACANTE, 25, 6));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 6));
  jogadores = inserirFim(jogadores, criarJogador("Eduardo", ZAGUEIRO, 25, 7));
  inscrever(buscarTime(times, 1), buscarJogador(jogadores, 7));
  //TIME 2
  jogadores = inserirFim(jogadores, criarJogador("Marcos", GOLEIRO, 20, 1));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 8));
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 9));
  jogadores = inserirFim(jogadores, criarJogador("Daniel", ZAGUEIRO, 25, 3));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 10));
  jogadores = inserirFim(jogadores, criarJogador("Lucas", ATACANTE, 21, 4));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 11));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ZAGUEIRO, 22, 5));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 12));
  jogadores = inserirFim(jogadores, criarJogador("Ze", ATACANTE, 25, 6));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 13));
  jogadores = inserirFim(jogadores, criarJogador("Marcelo", ZAGUEIRO, 25, 7));
  inscrever(buscarTime(times, 2), buscarJogador(jogadores, 14));
  //TIME 3
  jogadores = inserirFim(jogadores, criarJogador("Paulo", GOLEIRO, 20, 1));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 15));
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 16));
  jogadores = inserirFim(jogadores, criarJogador("Mario", ZAGUEIRO, 25, 3));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 17));
  jogadores = inserirFim(jogadores, criarJogador("Miguel", ATACANTE, 21, 4));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 18));
  jogadores = inserirFim(jogadores, criarJogador("Fernando", ZAGUEIRO, 22, 5));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 19));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ATACANTE, 25, 6));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 20));
  jogadores = inserirFim(jogadores, criarJogador("Eduardo", ZAGUEIRO, 25, 7));
  inscrever(buscarTime(times, 3), buscarJogador(jogadores, 21));
  //TIME 4
  jogadores = inserirFim(jogadores, criarJogador("Marcos", GOLEIRO, 20, 1));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 22));
  jogadores = inserirFim(jogadores, criarJogador("Pedro", ATACANTE, 19, 2));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 23));
  jogadores = inserirFim(jogadores, criarJogador("Daniel", ZAGUEIRO, 25, 3));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 24));
  jogadores = inserirFim(jogadores, criarJogador("Lucas", ATACANTE, 21, 4));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 25));
  jogadores = inserirFim(jogadores, criarJogador("Ricardo", ZAGUEIRO, 22, 5));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 26));
  jogadores = inserirFim(jogadores, criarJogador("Ze", ATACANTE, 25, 6));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 27));
  jogadores = inserirFim(jogadores, criarJogador("Marcelo", ZAGUEIRO, 25, 7));
  inscrever(buscarTime(times, 4), buscarJogador(jogadores, 28));
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
  char nome[50], estadio[50], cidade[50], data[50];
  while (opc != 0)
  {
    textoMenuTimes();
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      limpaTela();
      printf("\n\nDigite o nome do time: ");
      scanf(" %[^\n]s", nome);
      printf("\n\nDigite o nome do estadio: ");
      scanf(" %[^\n]s", estadio);
      printf("\n\nDigite o nome da cidade de origem do time: ");
      scanf(" %[^\n]s", cidade);
      printf("\n\nDigite a data de fundacao do time: ");
      scanf(" %[^\n]s", data);
      times = inserirFim(times, criarTime(nome, estadio, cidade, data));
      printf("\nTime criado com sucesso!\n");
      aguardarTecla();
      break;
    case 2:
      limpaTela();
      printf("\n\nDigite o ID do time a ser excluido: ");
      scanf("%d", &id);
      if (buscarTime(times, id) != NULL)
      {
        if (buscarTime(times, id)->jogadores == NULL)
        {
          if (buscarTime(times, id)->idTreinador == -1)
          {
            printf("\nTime %s excluido com sucesso!\n", (buscarTime(times, id))->nome);
            times = retirarTime(times, id);
          }
          else
          {
            printf("\nRemova antes o treinador do %s para poder excluir o time!\n", (buscarTime(times, id))->nome);
          }
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
  times = inserirFim(times, criarTime("Gremio", "Arena do Gremio", "Porto Alegre", "15 de setembro de 1903 "));
  times = inserirFim(times, criarTime("Inter", "Beira Rio", "Porto Alegre", "4 de abril de 1909 "));
  times = inserirFim(times, criarTime("Flamengo", "Estádio da Gavea", "Rio de Janeiro", "17 de novembro de 1895"));
  times = inserirFim(times, criarTime("Sao Paulo", "Estádio do Morumbi", "Sao Paulo", "25 de janeiro de 1930"));
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
      printf("\nDigite o nome do treinador (Max 50): ");
      scanf(" %[^\n]s", nome);
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