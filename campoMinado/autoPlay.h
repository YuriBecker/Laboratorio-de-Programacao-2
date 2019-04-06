#ifndef AUTO_PLAY
#define AUTO_PLAY

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "structs.h"
#include "handleScreen.h"
#include "handleMatriz.h"
#include "utils.h"

bool autoPlay(Matriz **campo, GameInfo *gameInfo);
bool tryPlay(Matriz **campo, GameInfo *gameInfo);
bool findBombs(Matriz **campo, GameInfo *gameInfo, int linha, int coluna);
bool findSafeSquares(Matriz **campo, GameInfo *gameInfo, int linha, int coluna);
#endif