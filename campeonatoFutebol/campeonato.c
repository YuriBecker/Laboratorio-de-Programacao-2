#include "campeonato.h"

void textoMenuCampeonato()
{
  limpaTela();
  printf("------Menu Campeonato-------\n");
  printf("\nEscolha uma opcao:\n");
  printf("\n1- Visualizar rodadas");
  printf("\n2- Classificacao geral dos times");
  printf("\n3- Relatorio de artilharia");
  printf("\n4- Relatorio dos times");
  printf("\n5- Relatorio dos jogadores");
  printf("\n6- Narrar proxima partida");
  printf("\n0- Sair");
  printf("\n\nOpcao: ");
}

void iniciarCampeonato(Lista *jogadores, Lista *times, Lista *rodadas)
{
  int numTimes = 0;
  int numPartidas;
  int numRodadas = 0;
  int aux = 0;

  Lista *temp = times;
  while (!vazia(temp))
  {
    temp = temp->prox;
    numTimes++;
  }

  aux = numTimes;
  while (aux != 1)
  {
    aux = aux / 2;
    numRodadas++;
  }
  //Cria todas as rodadas sem as partidas
  for (size_t i = 0; i < numRodadas; i++)
  {
    rodadas = inserirFim(rodadas, criarRodada());
  }

  Rodada *rodada = buscarRodada(rodadas, 1);

  temp = times;
  //Gera as partidas da primeira rodada
  while (!vazia(temp))
  {
    rodada->partidas = inserirFim(rodada->partidas, criarPartida(((Time *)temp->info), ((Time *)temp->prox->info)));
    rodada->preenchida = true;
    temp = temp->prox->prox;
  }

  menuCampeonato(jogadores, times, rodadas);
}

void menuCampeonato(Lista *jogadores, Lista *times, Lista *rodadas)
{
  while (1)
  {
    limpaTela();
    // verificaRodadas(rodadas, times);
    textoMenuCampeonato();
    int opc;
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      limpaTela();
      imprimirRodadas(rodadas);
      aguardarTecla();
      break;
    case 2:
      classificacaoGeralTimes(times);
      break;
    case 3:
      relatorioArtilharia(jogadores);
      break;
    case 4:
      relatorioTimes(times);
      break;
    case 5:
      relatorioJogadores(jogadores);
      break;
    case 6:
      rodadas = iniciarNarracao(rodadas, times);
      break;
    case 0:
      exit(0);
      break;
    default:
      printf("Entrada invalida!\n");
      sleep(1);
    }
  }
}

Lista *iniciarNarracao(Lista *rodadas, Lista *times)
{
  int opc;
  Lista *temp = rodadas;
  //Procura a rodada mais atualizada
  while (((Rodada *)temp->prox->info)->preenchida)
  {
    // if (((Rodada *)ultimo(rodadas))->id != ((Rodada *)temp->prox->info)->id)
    //   temp = temp->prox;
    // else
    // {
    //   printf("\n\nULTIMA RODADA");
    // }
    temp = temp->prox;
  }
  Rodada *rodada = (Rodada *)temp->info;
  Lista *partidasAux = rodada->partidas;
  // if (partidasAux == NULL)
  // {
  //   Lista *tAux = times;
  //   Lista *t = criar();
  //   while (!vazia(tAux))
  //   {
  //     if (((Time *)tAux->info)->eliminado == false)
  //       t = inserirFim(t, tAux->info);
  //     tAux = tAux->prox;
  //   }
  //   while (!vazia(t))
  //   {
  //     rodada->partidas = inserirFim(rodada->partidas, criarPartida(((Time *)t->info), ((Time *)t->prox->info)));
  //     t = t->prox->prox;
  //   }
  // }
  //Procura a proxima partida da rodada
  while (((Partida *)partidasAux->info)->ocorreu)
  {
    partidasAux = partidasAux->prox;
  }
  //Captura proxima partida
  Partida *proxPartida = (Partida *)partidasAux->info;

  printf("\nDeseja narrar a partida %s X %s\n", ((Time *)proxPartida->time1)->nome, ((Time *)proxPartida->time2)->nome);
  printf("\n1- Sim\n2- Nao\n\nOpc:");
  scanf("%d", &opc);
  if (opc == 1)
  {
    narrarPartida(proxPartida, (Rodada *)temp->info);
    int qtd = 0;
    int qtd2 = 0;
    partidasAux = rodada->partidas;
    Lista *t = times;
    while (!vazia(partidasAux))
    {
      qtd++;
      partidasAux = partidasAux->prox;
    }
    while (!vazia(t))
    {
      if (((Time *)t->info)->pontos == rodada->id)
        qtd2++;
      t = t->prox;
    }
    if (qtd == qtd2)
    {
      Rodada *proxRodada = (Rodada *)temp->prox->info;
      proxRodada->preenchida = true;
      int *vet = (int *)malloc(sizeof(int) * qtd);
      t = times;
      int val = 0;
      while (!vazia(t))
      {
        if (((Time *)t->info)->pontos == rodada->id)
        {
          vet[val] = ((Time *)t->info)->id;
          val++;
        }
      }
      for (int i = 0; i < val; i = i + 2)
      {
        proxRodada->partidas = inserirFim(proxRodada->partidas, criarPartida(buscarTime(times, vet[i]), buscarTime(times, vet[i + 1])));
      }
      printf("\n\n Proxima rodada preenchida!");
      aguardarTecla();
    }

    aguardarTecla();
  }
  else
  {
    return rodadas;
  }
  return rodadas;
}

void narrarPartida(Partida *partida, Rodada *rodada)
{
  bool acabou = false;
  int opc;
  int escolhido;
  Time *t;
  partida->ocorreu = true;
  escalarJogadores(partida);
  while (!acabou)
  {
    escolhido = 0;
    limpaTela();
    printf("\n\n PARTIDA %s X %s = ", ((Time *)partida->time1)->nome, ((Time *)partida->time2)->nome);
    printf(" %d X %d\n", (partida->golsTime1), (partida->golsTime2));
    printf("\nEscolha um time para informar um lance\n");
    printf("\n1- %s", ((Time *)partida->time1)->nome);
    printf("\n2- %s", ((Time *)partida->time2)->nome);
    printf("\n0- Finalizar partida\n");
    printf("\nOpc: ");
    scanf("%d", &opc);
    switch (opc)
    {
    case 1:
      t = (Time *)partida->time1;
      escolhido = 1;
      break;
    case 2:
      t = (Time *)partida->time2;
      escolhido = 2;
      break;
    case 0:
      if (partida->golsTime1 != partida->golsTime2)
      {

        if (partida->golsTime1 > partida->golsTime2)
        {
          partida->time2->eliminado = true;
          partida->time1->pontos++;
        }
        else
        {
          partida->time1->eliminado = true;
          partida->time2->pontos++;
        }
        return;
      }
      else
      {
        printf("\n\nTimes nao podem empatar na partida mata-mata\n");
        aguardarTecla();
      }
      break;
    }

    if (opc != 0)
    {
      limpaTela();
      int opc;
      int id;
      bool confirmado = false;
      printf("\n\n PARTIDA %s X %s = ", ((Time *)partida->time1)->nome, ((Time *)partida->time2)->nome);
      printf(" %d X %d\n", (partida->golsTime1), (partida->golsTime2));
      printf("\nQual o lance ?\n");
      printf("\n1- Gol");
      printf("\n2- Falta");
      printf("\n3- Cartao Vermelho");
      printf("\n4- Cartao Amarelo");
      printf("\n5- Substituicao");
      printf("\nOpc: ");
      scanf("%d", &opc);
      switch (opc)
      {
      case 1:
        confirmado = false;
        limpaTela();
        printf("\nLista de jogadores \n");
        imprimirJogadores(t->jogadores);
        printf("\nDigite o ID do jogador que marcou o gol\n");
        printf("\nID: ");
        scanf("%d", &id);
        if (buscarJogador(t->jogadores, id))
        {
          if (escolhido == 1)
          {
            if (verificaEscalacao(partida->escTime1, id))
              confirmado = true;
          }
          if (escolhido == 2)
          {
            if (verificaEscalacao(partida->escTime2, id))
              confirmado = true;
          }
        }

        if (confirmado)
        {
          buscarJogador(t->jogadores, id)->gols++;
          t->golsFeitos++;
          if (escolhido == 1)
          {
            ((Time *)partida->time2)->golsSofridos++;
            partida->golsTime1++;
          }
          if (escolhido == 2)
          {
            ((Time *)partida->time1)->golsSofridos++;
            partida->golsTime2++;
          }
        }
        else
        {
          printf("\nJogador nao encontrado!\n");
        }
        break;
      case 2:
        confirmado = false;
        limpaTela();
        printf("\nLista de jogadores \n");
        imprimirJogadores(t->jogadores);
        printf("\nDigite o ID do jogador que cometeu falta\n");
        printf("\nID: ");
        scanf("%d", &id);

        if (buscarJogador(t->jogadores, id))
        {
          if (escolhido == 1)
          {
            if (verificaEscalacao(partida->escTime1, id))
              confirmado = true;
          }
          if (escolhido == 2)
          {
            if (verificaEscalacao(partida->escTime2, id))
              confirmado = true;
          }
        }

        if (confirmado)
        {
          buscarJogador(t->jogadores, id)->faltas++;
        }
        else
        {
          printf("\nJogador nao encontrado!\n");
        }
        break;
      case 3:
        confirmado = false;
        limpaTela();
        printf("\nLista de jogadores \n");
        imprimirJogadores(t->jogadores);
        printf("\nDigite o ID do jogador que recebeu cartao vermelho\n");
        printf("\nID: ");
        scanf("%d", &id);

        if (buscarJogador(t->jogadores, id))
        {
          if (escolhido == 1)
          {
            if (verificaEscalacao(partida->escTime1, id))
              confirmado = true;
          }
          if (escolhido == 2)
          {
            if (verificaEscalacao(partida->escTime2, id))
              confirmado = true;
          }
        }

        if (confirmado)
        {
          buscarJogador(t->jogadores, id)->cartaoVermelho++;
        }
        else
        {
          printf("\nJogador nao encontrado!\n");
        }
        break;
      case 4:
        confirmado = false;
        limpaTela();
        printf("\nLista de jogadores \n");
        imprimirJogadores(t->jogadores);
        printf("\nDigite o ID do jogador que recebeu cartao amarelo\n");
        printf("\nID: ");
        scanf("%d", &id);

        if (buscarJogador(t->jogadores, id))
        {
          if (escolhido == 1)
          {
            if (verificaEscalacao(partida->escTime1, id))
              confirmado = true;
          }
          if (escolhido == 2)
          {
            if (verificaEscalacao(partida->escTime2, id))
              confirmado = true;
          }
        }

        if (confirmado)
        {
          buscarJogador(t->jogadores, id)->cartaoAmarelo++;
        }
        else
        {
          printf("\nJogador nao encontrado!\n");
        }
        break;
      case 5:
        limpaTela();

        break;
      default:
        printf("\nComando invalido!\n");
        aguardarTecla();
        break;
      }
    }
  }
}

bool verificaEscalacao(Escalacao *esc, int id)
{
  for (size_t i = 0; i < 12; i++)
  {
    if (esc->idJogadoresEscalados[i] == id)
    {
      return true;
    }
  }
  return false;
}

void escalarJogadores(Partida *partida)
{
  bool sair = false;
  int total = 0;
  int id;
  Lista *jogadores1 = ((Time *)partida->time1)->jogadores;
  Lista *jogadores2 = ((Time *)partida->time2)->jogadores;
  Time *time1 = (Time *)partida->time1;
  Time *time2 = (Time *)partida->time2;

  while (sair == false)
  {
    jogadores1 = ((Time *)partida->time1)->jogadores;
    limpaTela();
    printf("\nEscalacao do %s\n", time1->nome);
    printf("\nLista de jogadores \n");
    imprimirJogadores(jogadores1);
    printf("\nDigite o ID do jogador que sera escalado ou 0 para \nfinalizar (Deve ter pelo menos 7 jogadores no time)\n");
    printf("\nID: ");
    scanf("%d", &id);
    if (id != 0)
    {
      if (buscarJogador(jogadores1, id) != NULL)
      {
        bool jaEscalado = false;
        for (size_t i = 0; i < 12; i++)
        {
          if (partida->escTime1->idJogadoresEscalados[i] == id)
          {
            jaEscalado = true;
          }
        }
        if (!jaEscalado)
        {
          printf("\n %s foi escalado!\n", buscarJogador(jogadores1, id)->nome);
          partida->escTime1->idJogadoresEscalados[total] = id;
          total++;
        }
        else
        {
          printf("\n %s já foi escalado!\n", buscarJogador(jogadores1, id)->nome);
        }
        aguardarTecla();
      }
      else
      {
        printf("\n Jogador nao foi encontrado, verifique o ID!\n");
        aguardarTecla();
      }
    }
    else
    {
      if (total >= 7)
        sair = true;
      else
      {
        printf("\n Minimo 7 jogadores!!\n");
        aguardarTecla();
      }
    }
  }
  total = 0;
  sair = false;
  while (sair == false)
  {
    jogadores2 = ((Time *)partida->time2)->jogadores;
    limpaTela();
    printf("\nEscalacao do %s\n", time2->nome);
    printf("\nLista de jogadores \n");
    imprimirJogadores(jogadores2);
    printf("\nDigite o ID do jogador que sera escalado ou 0 para \nfinalizar (Deve ter pelo menos 7 jogadores no time)\n");
    printf("\nID: ");
    scanf("%d", &id);
    if (id != 0)
    {
      if (buscarJogador(jogadores2, id) != NULL)
      {
        bool jaEscalado = false;
        for (size_t i = 0; i < 12; i++)
        {
          if (partida->escTime2->idJogadoresEscalados[i] == id)
          {
            jaEscalado = true;
          }
        }

        if (!jaEscalado)
        {
          printf("\n %s foi escalado!\n", buscarJogador(jogadores2, id)->nome);
          partida->escTime2->idJogadoresEscalados[total] = id;
          total++;
        }
        else
        {
          printf("\n %s já foi escalado!\n", buscarJogador(jogadores2, id)->nome);
        }
        aguardarTecla();
      }
      else
      {
        printf("\n Jogador nao foi encontrado, verifique o ID!\n");
        aguardarTecla();
      }
    }
    else
    {
      if (total >= 7)
        sair = true;
      else
      {
        printf("\n Minimo 7 jogadores!!\n");
        aguardarTecla();
      }
    }
  }
}

void classificacaoGeralTimes(Lista *times)
{
  limpaTela();
  Lista *temp = times;
  while (temp != NULL)
  {
    if (((Time *)temp->info)->eliminado == false)
      printf("\n %s: %d pontos", ((Time *)temp->info)->nome, ((Time *)temp->info)->pontos);
    temp = temp->prox;
  }
  temp = times;
  while (temp != NULL)
  {
    if (((Time *)temp->info)->eliminado)
      printf("\n %s (Eliminado) : %d pontos", ((Time *)temp->info)->nome, ((Time *)temp->info)->pontos);
    temp = temp->prox;
  }
  printf("\n\n");
  aguardarTecla();
}

void relatorioArtilharia(Lista *jogadores)
{
  //lista ordenada
}

void relatorioTimes(Lista *times)
{
  int id;
  Time *t;
  limpaTela();
  printf("\nDigite o id do time\n");
  printf("\nOpc: ");
  scanf("%d", &id);
  t = buscarTime(times, id);
  if (t == NULL)
  {
    printf("\nTime nao encontrado!\n");
    aguardarTecla();
  }
  else
  {
    limpaTela();
    printf("\n\nNome: %s", t->nome);
    printf("\nCidade: %s", t->cidade);
    printf("\nData de Fundacao: %s", t->dataFundacao);
    printf("\nEstadio: %s", t->estadio);
    printf("\nID Treinador: %d", t->idTreinador);
    printf("\nQuantidade de gols feitos: %d", t->golsFeitos);
    printf("\nQuantidade de gols tomados: %d", t->golsSofridos);
    if (t->eliminado)
    {
      printf("\n\nTIME FOI ELIMINADO");
    }
    else
    {
      printf("\n\nTIME COMPETINDO");
    }

    aguardarTecla();
  }
}

void relatorioJogadores(Lista *jogadores)
{
  int id;
  Jogador *j;
  limpaTela();
  printf("\nDigite o id do jogador\n");
  printf("\nOpc: ");
  scanf("%d", &id);
  j = buscarJogador(jogadores, id);
  if (j == NULL)
  {
    printf("\nJogador nao encontrado!\n");
    aguardarTecla();
  }
  else
  {
    if (j->idTime > 0)
    {
      limpaTela();
      printf("\n\nNome: %s", j->nome);
      printf("\nIdade: %d", j->idade);
      printf("\nNumero Camisa: %d", j->numCamisa);
      printf("\nNumero de Gols: %d", j->gols);
      printf("\nNumero de Faltas Cometidas: %d", j->faltas);
      printf("\nNumero de Cartoes Vermelhos: %d", j->cartaoAmarelo);
      printf("\nNumero de Cartoes Amarelos: %d", j->cartaoVermelho);
      aguardarTecla();
    }
    else
    {
      printf("\nJogador nao faz parte de nenhum time!\n");
      aguardarTecla();
    }
  }
}