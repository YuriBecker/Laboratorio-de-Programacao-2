#ifndef RODADA_H
#define RODADA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "partida.h"

typedef struct Rodada
{
  int id;
  Lista *partidas;
} Rodada;

#endif