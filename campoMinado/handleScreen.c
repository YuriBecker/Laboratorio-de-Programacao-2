#include "handleScreen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void header()
{
  printf("\n CAMPO MINADO - YURI BECKER\n\n\n");
}

void winScreeen()
{
  printf("\n :) GANHOU!!\n\n");
}

void loseScreen()
{
  printf("\n :( PERDEU!!\n\n");
}

void clearScreen()
{
  system("clear");
}

void showMatriz(GameInfo *gameInfo, Matriz **campo)
{
  header();
  printf("     ");
  for (int j = 0; j < gameInfo->colunas; j++)
  {
    printf(" %d  ", j);
  }
  printf("\n    ");
  for (int j = 0; j < gameInfo->colunas; j++)
  {
    printf("____");
  }
  printf("__");
  printf("\n\n");
  for (int i = 0; i < gameInfo->linhas; i++)
  {
    if (i < 10)
      printf(" %d | ", i);
    else
      printf(" %d| ", i);

    for (int j = 0; j < gameInfo->colunas; j++)
    {
      if (campo[i][j].flag && !campo[i][j].aberto)
        printf(" P  ");
      else if (campo[i][j].aberto)
        if (campo[i][j].bomba)
          printf(" B  ");
        else if (campo[i][j].bombasProximas > 0)
          printf(" %d  ", campo[i][j].bombasProximas);
        else
          printf("    ");
      else
        printf(" -  ");
    }
    printf(" |");
    printf("\n");
  }
  printf("    ");
  for (int j = 0; j < gameInfo->colunas; j++)
  {
    printf("____");
  }
  printf("__\n\n");
}
