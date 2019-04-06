#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct matriz
{
  bool bomba;
  bool aberto;
  bool checked;
  bool flag;
  int bombasProximas;
} Matriz;

typedef struct gameInfo
{
  int linhas;
  int colunas;
  int numBombas;
  int totalPosicoes;
  bool perdeu;
  bool ganhou;
} GameInfo;

#endif