#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "treinador.h"

typedef struct Escalacao
{
  int idPartida;
  Time *time;
  //Minimo 7 jogadores
  int idJogadoresEscalados[12];
} Escalacao;

typedef struct Partida
{
  int id;
  Time *time1;
  Time *time2;
  Escalacao *escTime1;
  Escalacao *escTime2;
  int golsTime1;
  int golsTime2;
  bool ocorreu;
} Partida;

bool partidasIguais(void *partida1, void *partida2);
Partida *criarPartida(Time *time1, Time *time2);
Partida *buscarPartida(Lista *partidas, int id);
void imprimirPartidas(Lista *partidas);

#endif