// Crie um programa para controle de um campeonato de futebol, que atenda aos seguintes requisitos mínimos:
// Deve ser possível cadastrar times, treinadores, jogadores, rodadas e partidas. Cada cadastro deve possibilitar inclusão, exclusão e busca.
// Deve ser possível montar as escalações dos times de cada jogo.
// Deve ser possível narrar as partidas textualmente, informando o minuto e o lance e gravando informações relativas à gols, cartões amarelos, vermelhos, faltas e substituições.
// Um time não pode ter mais de 25 jogadores relacionados.
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
#include "treinador.h"

int main(int argc, char *argv[])
{
  bool sair = false;
  Lista *times = criar();
  Lista *jogadores = criar();
  Lista *treinadores = criar();

  while (!sair)
  {
    menuPrincipal(&times, &jogadores, &treinadores, &sair);
  }
}