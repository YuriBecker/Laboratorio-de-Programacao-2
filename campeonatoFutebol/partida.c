
#include "partida.h"

void imprimirPartida(void *partida)
{
  Partida *p = (Partida *)partida;
  if (p->ocorreu == false)
  {
    printf("\n--------------------------------");
    printf("\n %s X %s \n", p->time1->nome, p->time2->nome);
    printf("--------------------------------");
  }
  else
  {
    printf("\n--------------------------------");
    printf("\n %s X %s -> ", p->time1->nome, p->time2->nome);
    printf(" %d X %d \n", p->golsTime1, p->golsTime2);
    printf("--------------------------------");
  }
}

bool partidasIguais(void *partida1, void *partida2)
{
  return ((Partida *)partida1)->id == ((Partida *)partida2)->id;
}

unsigned int gerarIdPartida()
{
  static int ID = 1;
  return ID++;
}

Partida *criarPartida(Time *time1, Time *time2)
{
  Partida *p = (Partida *)malloc(sizeof(Partida));
  p->id = gerarIdPartida();
  p->escTime1 = (Escalacao *)malloc(sizeof(Escalacao));
  for (size_t i = 0; i < 12; i++)
  {
    p->escTime1->idJogadoresEscalados[i] = -1;
  }
  p->escTime2 = (Escalacao *)malloc(sizeof(Escalacao));
  for (size_t i = 0; i < 12; i++)
  {
    p->escTime2->idJogadoresEscalados[i] = -1;
  }
  p->golsTime1 = 0;
  p->golsTime2 = 0;
  p->time1 = time1;
  p->time2 = time2;
  p->ocorreu = false;
  return p;
}

Partida *buscarPartida(Lista *partidas, int id)
{
  Partida *p = (Partida *)malloc(sizeof(Partida));
  p->id = id;
  return (Partida *)buscar(partidas, p, &partidasIguais);
}

void imprimirPartidas(Lista *partidas)
{
  imprimir(partidas, &imprimirPartida);
}
