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

  Lista *aux = lista;
  Lista *anterior = criar();

  while (aux != NULL)
  {
    if (strcmp(novoNo->c->placa, aux->c->placa) < 0)
      break;
    anterior = aux;
    aux = aux->prox;
  }

  if (anterior == NULL)
  {
    lista = novoNo;
    novoNo->prox = aux;
    return lista;
  }
  else
  {
    anterior->prox = novoNo;
    novoNo->prox = aux;
    return lista;
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
  free(temp);
  return lista;
}

bool placaJaExiste(Lista *carros, char *placa)
{
  Lista *aux = carros;
  while (!vazia(aux))
  {
    if (!strcmp(aux->c->placa, placa))
      return true;
    aux = aux->prox;
  }
  return false;
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
