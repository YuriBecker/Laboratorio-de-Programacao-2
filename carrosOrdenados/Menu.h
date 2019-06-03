#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Carro.h"
#include "ArvBinBusca.h"

void menuPrincipal(Lista **carros, bool *sair);
void textoMenuPrincipal();
void limpaTela();
void aguardarTecla();

#endif