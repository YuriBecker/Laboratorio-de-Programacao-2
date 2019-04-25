#include "lista.h"

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

Lista *inserirInicio(Lista *lista, void *elemento)
{
   Lista *novoNo = (Lista *)malloc(sizeof(Lista));
   novoNo->info = elemento;
   novoNo->prox = lista;
   return novoNo;
}

Lista *inserirFim(Lista *lista, void *elemento)
{
   if (vazia(lista))
      return inserirInicio(lista, elemento);
   ultimo(lista)->prox = inserirInicio(NULL, elemento);
   return lista;
}

void imprimir(Lista *lista, void imprimirElemento(void *))
{
   if (!vazia(lista))
   {
      Lista *temp = lista;
      while (!vazia(temp))
      {
         imprimirElemento(temp->info); 
         temp = temp->prox;
      }
   }
}

void *buscar(Lista *lista, void *elemento, bool iguais(void *, void *))
{
   Lista *temp = lista;
   while (temp != NULL)
   {
      if (iguais(temp->info, elemento)) 
      {
         free(elemento);
         return temp->info;
      }
      temp = temp->prox;
   }
   return NULL;
}

Lista *retirar(Lista *lista, void *elemento, bool iguais(void *, void *))
{
   Lista *anterior = NULL;
   Lista *temp = lista;
   while (!vazia(temp) && !iguais(temp->info, elemento))
   {
      anterior = temp;
      temp = temp->prox;
   }
   if (vazia(temp))
      return lista;
   if (anterior == NULL)
      lista = temp->prox;
   else
      anterior->prox = temp->prox;
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
