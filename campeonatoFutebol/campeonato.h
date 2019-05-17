#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "treinador.h"
#include "menu.h"
#include "rodada.h"
#include "partida.h"

void iniciarCampeonato(Lista *jogadores, Lista *times, Lista *rodadas);
void textoMenuCampeonato();
void menuCampeonato(Lista *jogadores, Lista *times, Lista *rodadas);
void classificacaoGeralTimes(Lista *times);
void relatorioArtilharia(Lista *jogadores);
void relatorioTimes(Lista *times);
void relatorioJogadores(Lista *jogadores);
Lista *iniciarNarracao(Lista *rodadas, Lista *times);
void narrarPartida(Partida *partida, Rodada *rodada);
void escalarJogadores(Partida *partida);
bool verificaEscalacao(Escalacao *esc, int id);

#endif