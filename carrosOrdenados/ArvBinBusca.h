#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Carro.h"

#define PLACA 1
#define MARCA 2
#define ANO 3

typedef struct arv
{
  int ordenacao;
  Carro *carro;
  struct arv *esq;
  struct arv *dir;
} Arv;

Arv *cria(void);
void imprime(Arv *a);
Arv *insere(Arv *a, Carro *c, int ordem);
Arv *retira(Arv *r, Carro *c);
Arv *busca(Arv *a, Carro *c, int ordem);