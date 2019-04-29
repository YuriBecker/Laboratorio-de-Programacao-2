
#ifndef TREINADOR_H
#define TREINADOR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"
#include "time.h"

typedef struct
{
  int id;
  char *nome;
  int idTime;
} Treinador;

Treinador *criarTreinador(const char *nome);
Treinador *buscarTreinador(Lista *treinadores, int id);
Lista *retirarTreinador(Lista *treinadores, int id);
Lista *retirarTreinadorP(Lista *treinadores, Treinador *t);
void imprimirTreinadores(Lista *treinadores);

#endif