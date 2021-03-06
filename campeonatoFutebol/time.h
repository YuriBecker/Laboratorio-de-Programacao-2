#ifndef TIME_H
#define TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "jogador.h"
#include "lista.h"
#include "treinador.h"

typedef struct Time
{
  int id;
  char *nome;
  char *estadio;
  char *cidade;
  char *dataFundacao;
  Lista *jogadores;
  int idTreinador;
  int golsFeitos;
  int golsSofridos;
  bool eliminado;
  int pontos;
} Time;

Time *criarTime(const char *nome, const char *estadio, const char *cidade, const char *dataFundacao);
Time *buscarTime(Lista *times, int id);
Lista *retirarTime(Lista *times, int id);
Lista *retirarTimeP(Lista *times, Time *time);

void desinscrever(Time *time, int id);
void inscrever(Time *time, Jogador *jogador);
void imprimirTimes(Lista *times);
bool verificarTimes(Lista *times);
bool potenciaDeDois(int num);
#endif