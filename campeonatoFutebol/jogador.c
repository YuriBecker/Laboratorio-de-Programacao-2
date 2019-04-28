
#include "jogador.h"

unsigned int gerarIdJogador()
{
  static int ID = 1;
  return ID++;
}

// Mostra na tela os dados de um jogador.
void imprimirJogador(void *jogador)
{
  printf("   ID jogador: %d - Nome: %s\n", ((Jogador *)jogador)->id, ((Jogador *)jogador)->nome);
}

// Compara a igualdade entre jogadores.
bool jogadoresIguais(void *jogador1, void *jogador2)
{
  return ((Jogador *)jogador1)->id == ((Jogador *)jogador2)->id;
}

// Cria um jogador com a id preenchida
Jogador *criarJogadorPK()
{
  Jogador *j = (Jogador *)malloc(sizeof(Jogador));
  j->nome = (char *)malloc(sizeof(char) * 50);
  j->id = gerarIdJogador();
  j->idTime = -1;
  return j;
}

// Cria um jogador com a id e o nome preenchidos
Jogador *criarJogador(const char *nome)
{
  Jogador *j = criarJogadorPK();
  strcpy(j->nome, nome);
  return j;
}

// Busca um jogador pela id.
Jogador *buscarJogador(Lista *jogadores, int id)
{
  Jogador *aux = (Jogador *)malloc(sizeof(Jogador));
  aux->id = id;
  return (Jogador *)buscar(jogadores, aux, &jogadoresIguais);
}

// Retira um jogador da lista geral de jogadores através de um ponteiro para este jogador.
Lista *retirarJogadorP(Lista *jogadores, Jogador *jogador)
{
  return retirar(jogadores, jogador, &jogadoresIguais);
}

// Retira um jogador da lista geral de jogadores através do id
Lista *retirarJogador(Lista *jogadores, int id)
{
  return retirarJogadorP(jogadores, buscarJogador(jogadores, id));
}

// Imprime a lista de jogadores usando a funcao auxiliar imprimirJogador
void imprimirJogadores(Lista *jogadores)
{
  imprimir(jogadores, &imprimirJogador);
}
