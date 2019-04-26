// Crie um programa para controle de um campeonato de futebol, que atenda aos seguintes requisitos mínimos:
// Os dados devem ser armazenados em listas em memória (não será usado acesso a BD neste trabalho).
// Obs.: Para facilitar os testes, podem ser criadas várias listas no main, antes de iniciar o programa.
// Deve ser possível cadastrar times, treinadores, jogadores, rodadas e partidas. Cada cadastro deve possibilitar inclusão, exclusão e busca.
// Deve ser possível montar as escalações dos times de cada jogo.
// Deve ser possível narrar as partidas textualmente, informando o minuto e o lance e gravando informações relativas à gols, cartões amarelos, vermelhos, faltas e substituições.
// Um time não pode ter mais de 25 jogadores relacionados.
// Cada time deve ter os ao menos seguintes dados: nome, estádio, cidade, data de fundacao.
// Cada treinador deve ter ao menos os seguintes dados: nome.
// Cada jogador deve ter ao menos os seguintes dados: nome, posicao, idade, nr camisa.
// Deve ser possível gerar um relatório contendo a classificação geral dos clubes, de acordo com as informações das partidas narradas.
// Deve ser possível gerar relatórios de artilharia, contendo uma lista ordenada de jogadores e seus respectivos gols.
// Deve ser possível gerar um relatório de estatísticas, com as seguintes informações (por time): gols feitos, gols sofridos, cartões amarelos, cartões vermelhos e faltas cometidas.
// Deve ser possível gerar um relatório de estatísticas, com as seguintes informações (por jogador): gols feitos, cartões amarelos, cartões vermelhos e faltas cometidas.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "menu.h"

int main(int argc, char *argv[])
{
  bool *sair;
  sair = (bool *)malloc(sizeof(bool));
  *sair = false;
  Lista *times = criar();
  Lista *jogadores = criar();

  while (!*sair)
  {
    menuPrincipal(times, jogadores, sair);
  }

  // printf("----- Lista de Times (sem Jogadores) -----\n");
  // times = inserirFim(times, criarTime("Gremio"));
  // times = inserirFim(times, criarTime("Inter"));
  // times = inserirFim(times, criarTime("Flamengo"));
  // times = inserirFim(times, criarTime("Sao Paulo"));
  // times = inserirFim(times, criarTime("Sport"));
  // imprimirTimes(times);

  // printf("\n----- Adicao de jogadores -----\n");

  // /* Sem testar os retornos, caso se tenha certeza se o time ou
  //    o jogador existem - como agora, com dados de teste. */

  // // Adiciona os jogadores 1, 2, 3 ao time 1.
  // Time *t = buscarTime(times, 1);
  // inscrever(t, buscarJogador(jogadores, 1));
  // inscrever(t, buscarJogador(jogadores, 2));
  // inscrever(t, buscarJogador(jogadores, 3));

  // // Adiciona os jogadores 4, 5 e 6 ao time 2.
  // t = buscarTime(times, 2);
  // inscrever(t, buscarJogador(jogadores, 4));
  // inscrever(t, buscarJogador(jogadores, 5));
  // inscrever(t, buscarJogador(jogadores, 6));

  // // Adiciona os jogadores 7 e 8 ao time 3.
  // t = buscarTime(times, 3);
  // inscrever(t, buscarJogador(jogadores, 7));
  // inscrever(t, buscarJogador(jogadores, 8));

  // /*
  //    Testando os retornos, caso não se tenha certeza se o time ou
  //    o jogador existem - normalmente quando há entrada de dados
  //    pelo usuario.
  // */
  // t = buscarTime(times, 5);
  // if (t != NULL)
  // {
  //   Jogador *j = buscarJogador(jogadores, 11);
  //   if (j != NULL)
  //     inscrever(t, j);
  //   j = buscarJogador(jogadores, 12);
  //   if (j != NULL)
  //     inscrever(t, j);
  // }

  // printf("\n----- Lista de Times (com Jogadores) -----\n");
  // imprimirTimes(times);

  // printf("\n----- Alteracao de jogadores -----\n");

  // // Retira o time 4 da lista geral de times.
  // times = retirarTime(times, 4);


  // // Desinscreve o jogador 3 do time 1.
  // t = buscarTime(times, 1);
  // desinscrever(t, 3);

  // // Desinscreve o jogador 6 do time 2.
  // t = buscarTime(times, 2);
  // desinscrever(t, 6);

  // printf("\n----- Lista de Jogadores -----\n");
  // imprimirJogadores(jogadores);

  // // Retira o time 5 (os jogadores permanecem na lista geral)
  // t = buscarTime(times, 5);
  // if (t != NULL)
  //   times = retirarTimeP(times, t);

  // printf("\n----- Lista de Times (com Jogadores) -----\n");
  // imprimirTimes(times);

  // printf("\n----- Lista de Jogadores -----\n");
  // imprimirJogadores(jogadores);
}