#include "treinador.h"

unsigned int gerarIdTreinador()
{
  static int ID = 1;
  return ID++;
}

// Mostra na tela os dados de um treinador.
void imprimirTreinador(void *treinador)
{
  if (((Treinador *)treinador)->idTime > 0)
  {
    printf("  ID Treinador: %d \n  Nome: %s \n  ID Time: %d\n", ((Treinador *)treinador)->id, ((Treinador *)treinador)->nome, ((Treinador *)treinador)->idTime);
  }
  else
  {
    printf("  ID Treinador: %d \n  Nome: %s \n  Não treina nenhum time\n", ((Treinador *)treinador)->id, ((Treinador *)treinador)->nome);
  }
  printf("---------------------------------------------\n");
}

// Compara a igualdade entre treinadores.
bool treinadoresIguais(void *treinador1, void *treinador2)
{
  return ((Treinador *)treinador1)->id == ((Treinador *)treinador2)->id;
}

// Cria um treinador com a id preenchida
Treinador *criarTreinadorPK()
{
  Treinador *j = (Treinador *)malloc(sizeof(Treinador));
  j->nome = (char *)malloc(sizeof(char) * 50);
  j->id = gerarIdTreinador();
  j->idTime = -1;
  return j;
}

// Cria um jogador com a id e o nome preenchidos
Treinador *criarTreinador(const char *nome)
{
  Treinador *t = criarTreinadorPK();
  strcpy(t->nome, nome);
  return t;
}

// Busca um jogador pela id.
Treinador *buscarTreinador(Lista *treinadores, int id)
{
  Treinador *t = (Treinador *)malloc(sizeof(Treinador));
  t->id = id;
  return (Treinador *)buscar(treinadores, t, &treinadoresIguais);
}

// Retira um treinador da lista  através de um ponteiro para este treinador.
Lista *retirarTreinadorP(Lista *treinadores, Treinador *t)
{
  return retirar(treinadores, t, &treinadoresIguais);
}

// Retira um treinador da lista através do id
Lista *retirarTreinador(Lista *treinadores, int id)
{
  return retirarTreinadorP(treinadores, buscarTreinador(treinadores, id));
}

// Imprime a lista de treinadores usando a funcao auxiliar imprimirTreinador
void imprimirTreinadores(Lista *treinadores)
{
  imprimir(treinadores, &imprimirTreinador);
}
