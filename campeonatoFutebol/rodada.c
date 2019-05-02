
#include "rodada.h"

void imprimirRodada(void *rodada)
{
  Rodada *r = (Rodada *)rodada;
  printf("\n--------------RODADA %d-------------\n", r->id);
  imprimirPartidas(r->partidas);
  printf("\n------------------------------------\n\n");
}

bool rodadasIguais(void *rodada1, void *rodada2)
{
  return ((Rodada *)rodada1)->id == ((Rodada *)rodada2)->id;
}

unsigned int gerarIdRodada()
{
  static int ID = 1;
  return ID++;
}

Rodada *criarRodada()
{
  Rodada *r = (Rodada *)malloc(sizeof(Rodada));
  r->id = gerarIdRodada();
  r->partidas = criar();
  return r;
}

Rodada *buscarRodada(Lista *rodadas, int id)
{
  Rodada *p = (Rodada *)malloc(sizeof(Rodada));
  p->id = id;
  return (Rodada *)buscar(rodadas, p, &rodadasIguais);
}

void imprimirRodadas(Lista *rodadas)
{
  imprimir(rodadas, &imprimirRodada);
}
