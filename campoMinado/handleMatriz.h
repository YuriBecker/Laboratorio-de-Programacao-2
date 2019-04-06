#ifndef HANDLE_MATRIZ
#define HANDLE_MATRIZ

#include "structs.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Matriz **alocarMatriz(GameInfo *gameInfo);
void putBombs(Matriz **campo, GameInfo *gameInfo);
void locateBombs(GameInfo *gameInfo, Matriz **campo);
void initializeMatriz(GameInfo *gameInfo, Matriz **campo);
void openAll(GameInfo *gameInfo, Matriz **campo);
bool playGame(Matriz **campo, GameInfo *gameInfo);
bool verifyVictory(Matriz **campo, GameInfo *gameInfo);
void putFlag(Matriz **campo, GameInfo *gameInfo, int linha, int coluna);
void openAround(Matriz **campo, int linha, int coluna, GameInfo *gameInfo);

#endif