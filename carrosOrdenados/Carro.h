#ifndef CARRO_H
#define CARRO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
  char *placa;
  char *marca;
  int ano;
} Carro;

typedef struct Lista
{
  Carro *c;
  struct Lista *prox;
} Lista;

Lista *criar();
Lista *inserirOrdenado(Lista *lista, Carro *c);
bool vazia(Lista *lista);
void imprimir(Lista *lista);
Carro *buscar(Lista *lista, char *placa);
Lista *liberar(Lista *lista);
Lista *ultimo(Lista *lista);
Lista *retirar(Lista *lista, char *placa);
Carro *novoCarro(char *placa, char *marca, int ano);
bool carrosIguais(Carro *c1, Carro *c2);

#endif