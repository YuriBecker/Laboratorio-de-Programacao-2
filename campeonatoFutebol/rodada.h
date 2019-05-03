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
#include "treinador.h"
#include "partida.h"

typedef struct Rodada
{
  int id;
  Lista *partidas;
  bool preenchida;
} Rodada;

bool rodadasIguais(void *rodada1, void *rodada2);
Rodada *criarRodada();
Rodada *buscarRodada(Lista *rodadas, int id);
void imprimirRodadas(Lista *rodadas);

#endif