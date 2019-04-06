#ifndef HANDLE_SCREEN
#define HANDLE_SCREEN

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void header();
void clearScreen();
void winScreeen();
void loseScreen();
void showMatriz(GameInfo *gameInfo, Matriz **campo);

#endif