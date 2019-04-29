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

void limpaTela();
void menuPrincipal(Lista **times, Lista **jogadores, Lista **treinadores, bool *sair);
void textoMenuPrincipal();
Lista *menuJogadores(Lista *jogadores, Lista *times);
void textoMenuJogadores();
Lista *menuTimes(Lista *jogadores, Lista *times);
void textoMenuTimes();
void aguardarTecla();
void textoMenuTreinadores();
Lista *menuTreinadores(Lista *treinadores, Lista *times);

Lista *criaJogadoresAutomaticamente(Lista *jogadores);
Lista *criaTimesAutomaticamente(Lista *times);
#endif