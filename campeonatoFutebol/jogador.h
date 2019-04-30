#ifndef JOGADOR_H
#define JOGADOR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

#define GOLEIRO 0
#define ATACANTE 1
#define ZAGUEIRO 2

typedef struct Jogador
{
  int id;
  char *nome;
  int posicao;
  int idade;
  int numCamisa;
  int idTime;
  int gols;
  int cartaoVermelho;
  int cartaoAmarelo;
  int faltas;
} Jogador;

Jogador *criarJogador(const char *nome);
Jogador *buscarJogador(Lista *jogadores, int id);
Lista *retirarJogador(Lista *jogadores, int id);
Lista *retirarJogadorP(Lista *jogadores, Jogador *jogador);
void imprimirJogadores(Lista *jogadores);

#endif