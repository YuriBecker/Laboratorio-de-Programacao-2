#include "Carro.h"

Carro *novoCarro(char *placa, char *marca, int ano)
{
  Carro *c = (Carro *)malloc(sizeof(Carro));
  c->placa = (char *)malloc(7);
  c->marca = (char *)malloc(15);
  strcpy(c->placa, placa);
  strcpy(c->marca, marca);
  c->ano = ano;
}

bool carrosIguais(Carro *c1, Carro *c2)
{
  return strcmp(c1->placa, c2->placa) == 0;
}

Lista *criar()
{
  return NULL;
}

bool vazia(Lista *lista)
{
  return (lista == NULL);
}

Lista *ultimo(Lista *lista)
{
  if (vazia(lista))
    return lista;
  Lista *ultimo = lista;
  while (ultimo->prox != NULL)
    ultimo = ultimo->prox;
  return ultimo;
}

Lista *inserirOrdenado(Lista *lista, Carro *c)
{
  Lista *novoNo = (Lista *)malloc(sizeof(Lista));
  novoNo->c = c;
  if (vazia(lista))
  {
    novoNo->prox = lista;
    return novoNo;
  }
  else
  {
    Lista *aux = lista;
    Lista *anterior;
    while (aux != NULL)
    {
      if (strcmp(novoNo->c->placa, aux->c->placa) > 0)
        break;
      anterior = aux;
      aux = aux->prox;
    }
    if (aux != NULL)
    {
      novoNo->prox = aux->prox;
      aux->prox = novoNo;
      return lista;
    }
    else
    {
      novoNo->prox = lista;
      return novoNo;
    }
  }
}

Lista *inserirOrdemDesc(Lista *lista, Carro *c)
{
  Lista *novoNo = (Lista *)malloc(sizeof(Lista));
  novoNo->c = c;
  if (vazia(lista))
  {
    novoNo->prox = lista;
    return novoNo;
  }
  else
  {
    Lista *aux = lista;
    Lista *anterior;
    while (aux != NULL)
    {
      if (strcmp(aux->c->placa, novoNo->c->placa) < 0)
        break;
      anterior = aux;
      aux = aux->prox;
    }
    if (aux != NULL)
    {
      anterior->prox = novoNo;
      novoNo->prox = aux;
      return lista;
    }
    else
    {
      ultimo(lista)->prox = novoNo;
      novoNo->prox = NULL;
      return lista;
    }
  }
}

void imprimir(Lista *lista)
{
  if (!vazia(lista))
  {
    Lista *temp = lista;
    while (!vazia(temp))
    {
      printf("%s %s %d \n", temp->c->placa, temp->c->marca, temp->c->ano);
      temp = temp->prox;
    }
  }
  else
  {
    printf("\nLista vazia!");
  }
}

Carro *buscar(Lista *lista, char *placa)
{
  Lista *temp = lista;
  Carro *aux = (Carro *)malloc(sizeof(Carro));
  strcpy(aux->placa, placa);
  while (temp != NULL)
  {
    if (carrosIguais(temp->c, aux))
    {
      free(aux);
      return temp->c;
    }
    temp = temp->prox;
  }
  return NULL;
}

Lista *retirar(Lista *lista, char *placa)
{
  Lista *anterior = NULL;
  Lista *temp = lista;
  while (!vazia(temp))
  {
    if (strcmp(temp->c->placa, placa) == 0)
    {
      //primeiro da lista sera removido
      if (vazia(anterior))
      {
        lista = lista->prox;
        break;
      }
      else
      {
        anterior->prox = temp->prox;
        break;
      }
    }
    anterior = temp;
    temp = temp->prox;
  }
  printf("Carro com a placa -> %s, encontrado e removido!\n", temp->c->placa);
  free(temp);
  return lista;
}

Lista *liberar(Lista *lista)
{
  while (!vazia(lista))
  {
    Lista *temp = lista->prox;
    free(lista);
    lista = temp;
  }
  return NULL;
}
