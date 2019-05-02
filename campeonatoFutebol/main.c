#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "menu.h"
#include "treinador.h"
#include "rodada.h"
#include "partida.h"

int main(int argc, char *argv[])
{
  bool sair = false;
  Lista *times = criar();
  Lista *jogadores = criar();
  Lista *treinadores = criar();
  Lista *rodadas = criar();
  Lista *partidas = criar();

  while (!sair)
  {
    menuPrincipal(&times, &jogadores, &treinadores, &rodadas, &partidas, &sair);
  }
}