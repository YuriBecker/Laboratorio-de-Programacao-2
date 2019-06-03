#include "ArvBinBusca.h"

Arv *cria(void)
{
  return NULL;
}

Arv *busca(Arv *a, Carro *c, int ordem)
{
  int retornoStrcmp;
  if (a == NULL)
    return NULL;
  switch (ordem)
  {
  case PLACA:
    if (strcmp(a->carro->placa, c->placa) < 0)
      a = buscaPlaca(a->dir, c);
    else if (strcmp(a->carro->placa, c->placa) > 0)
      a = busca(a->esq, c, ordem);
    break;
  case MARCA:
    if (strcmp(a->carro->marca, c->marca) < 0)
      a = buscaPlaca(a->dir, c);
    else if (strcmp(a->carro->marca, c->marca) > 0)
      a = busca(a->esq, c, ordem);
    break;
  case ANO:
    if (a->carro->ano < c->ano)
      a = busca(a->dir, c, ordem);
    else if (a->carro->ano > c->ano)
      a = busca(a->esq, c, ordem);
    break;
  }
  return a;
}

//imprime na ordem crescente
void imprime(Arv *a)
{
  if (a != NULL)
  {
    imprime(a->esq);
    printf("%s %s %d\n", a->carro->placa, a->carro->marca, a->carro->ano);
    imprime(a->dir);
  }
}

Arv *insere(Arv *a, Carro *c, int ordem)
{
  if (a == NULL)
  {
    a = (Arv *)malloc(sizeof(Arv));
    a->carro = c;
    a->esq = a->dir = NULL;
  }
  else
  {
    switch (ordem)
    {
    case PLACA:
      if (strcmp(c->placa, a->carro->placa) < 0)
        a->esq = insere(a->esq, c, ordem);
      else
        a->dir = insere(a->dir, c, ordem);
      break;
    case MARCA:
      if (strcmp(c->marca, a->carro->marca) < 0)
        a->esq = insere(a->esq, c, ordem);
      else
        a->dir = insere(a->dir, c, ordem);
      break;
      break;
    case ANO:
      if (c->ano < a->carro->ano)
        a->esq = insere(a->esq, c, ordem);
      else /* v >= a->info */
        a->dir = insere(a->dir, c, ordem);
      break;
    }
  }
  return a;
}

Arv *retira(Arv *r, Carro *c)
{
  if (r == NULL)
    return NULL;
  else if (strcmp(r->carro->placa, c->placa) > 0)
    r->esq = retira(r->esq, c);
  else if (strcmp(r->carro->placa, c->placa) < 0)
    r->dir = retira(r->dir, c);
  else
  { /* achou o nó a remover */
    /* nó sem filhos */
    if (r->esq == NULL && r->dir == NULL)
    {
      free(r);
      r = NULL;
    }
    /* nó só tem filho à direita */
    else if (r->esq == NULL)
    {
      Arv *t = r;
      r = r->dir;
      free(t);
    }

    /* só tem filho à esquerda */
    else if (r->dir == NULL)
    {
      Arv *t = r;
      r = r->esq;
      free(t);
    }
    /* nó tem os dois filhos */
    else
    {
      Arv *f = r->esq;
      while (f->dir != NULL)
      {
        f = f->dir;
      }
      /* troca as informações */
      r->carro = f->carro;
      f->carro = c;
      r->esq = retira(r->esq, c);
    }
  }
  return r;
}