#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "time.h"
#include "jogador.h"
#include "treinador.h"
#include "campeonato.h"

void limpaTela();
void menuPrincipal(Lista **times, Lista **jogadores, Lista **treinadores, Lista **rodadas, bool *sair);
void textoMenuPrincipal();
Lista *menuJogadores(Lista *jogadores, Lista *times);
void textoMenuJogadores();
Lista *menuTimes(Lista *jogadores, Lista *times);
void textoMenuTimes();
void aguardarTecla();
void textoMenuTreinadores();
Lista *menuTreinadores(Lista *treinadores, Lista *times);
void textoAvisoCampeonato();

Lista *criaJogadoresAutomaticamente(Lista *jogadores, Lista *times);
Lista *criaTimesAutomaticamente(Lista *times);
#endif