#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Lista
{
   void *info;
   struct Lista *prox;
} Lista;

Lista *criar();
Lista *inserirInicio(Lista *lista, void *elemento);
Lista *inserirFim(Lista *lista, void *elemento);
bool vazia(Lista *lista);
Lista *liberar(Lista *lista);

void imprimir(Lista *lista, void imprimirElemento(void *));
void *buscar(Lista *lista, void *elemento, bool iguais(void *, void *));
Lista *retirar(Lista *lista, void *elemento, bool iguais(void *, void *));

#endif