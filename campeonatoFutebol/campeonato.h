#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "rodada.h"

typedef struct Campeonato
{
  int id;
  Lista *rodadas;
} Campeonato;

#endif