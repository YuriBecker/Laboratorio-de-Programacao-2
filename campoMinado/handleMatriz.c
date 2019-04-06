#include "handleMatriz.h"

Matriz **alocarMatriz(GameInfo *gameInfo)
{
  Matriz **m = (Matriz **)malloc(gameInfo->linhas * sizeof(Matriz *));

  for (int i = 0; i < gameInfo->linhas; i++)
  {
    m[i] = (Matriz *)malloc(gameInfo->colunas * sizeof(Matriz));
  }

  if (m == NULL)
  {
    printf("Memoria insuficiente.\n");
    return m;
  }
  initializeMatriz(gameInfo, m);
  return m;
}

void openAround(Matriz **campo, int linha, int coluna, GameInfo *gameInfo)
{
  if (linha < 0 || coluna < 0 || coluna >= gameInfo->colunas || linha >= gameInfo->linhas)
    return;
  if (campo[linha][coluna].bomba == true || campo[linha][coluna].checked == true || campo[linha][coluna].flag)
    return;
  campo[linha][coluna].aberto = campo[linha][coluna].checked = true;
  campo[linha][coluna].flag = false;
  if (campo[linha][coluna].bombasProximas == 0)
  {
    openAround(campo, linha + 1, coluna, gameInfo);
    openAround(campo, linha, coluna + 1, gameInfo);
    openAround(campo, linha - 1, coluna, gameInfo);
    openAround(campo, linha, coluna - 1, gameInfo);
    openAround(campo, linha + 1, coluna - 1, gameInfo);
    openAround(campo, linha - 1, coluna + 1, gameInfo);
    openAround(campo, linha + 1, coluna + 1, gameInfo);
    openAround(campo, linha - 1, coluna - 1, gameInfo);
  }
}

void putFlag(Matriz **campo, GameInfo *gameInfo, int linha, int coluna)
{
  if (linha >= 0 && linha < gameInfo->linhas && coluna >= 0 && coluna < gameInfo->colunas)
    if (campo[linha][coluna].aberto == false)
    {
      if (campo[linha][coluna].flag == true)
        campo[linha][coluna].flag = false;
      else
        campo[linha][coluna].flag = true;
    }
}

bool verifyVictory(Matriz **campo, GameInfo *gameInfo)
{
  int count = 0;
  int total = gameInfo->linhas * gameInfo->colunas - gameInfo->numBombas;
  for (size_t l = 0; l < gameInfo->linhas; l++)
  {
    for (size_t c = 0; c < gameInfo->colunas; c++)
    {
      if (campo[l][c].aberto && !campo[l][c].flag)
      {
        count++;
      }
    }
  }
  if (count == total)
    return true;
  else
    return false;
}

void locateBombs(GameInfo *gameInfo, Matriz **campo)
{
  for (size_t linha = 0; linha < gameInfo->linhas; linha++)
  {
    for (size_t coluna = 0; coluna < gameInfo->colunas; coluna++)
    {
      if (!campo[linha][coluna].bomba)
      {
        int total = 0;
        if (linha > 0 && campo[linha - 1][coluna].bomba)
          total++;
        if (linha < gameInfo->linhas - 1 && campo[linha + 1][coluna].bomba)
          total++;
        if (coluna > 0 && campo[linha][coluna - 1].bomba)
          total++;
        if (coluna < gameInfo->colunas - 1 && campo[linha][coluna + 1].bomba)
          total++;
        if (coluna > 0 && linha > 0 && campo[linha - 1][coluna - 1].bomba)
          total++;
        if (linha > 0 && coluna < gameInfo->colunas - 1 && campo[linha - 1][coluna + 1].bomba)
          total++;
        if (coluna > 0 && linha < gameInfo->linhas - 1 && campo[linha + 1][coluna - 1].bomba)
          total++;
        if (linha < gameInfo->linhas - 1 && coluna < gameInfo->colunas - 1 && campo[linha + 1][coluna + 1].bomba)
          total++;
        campo[linha][coluna].bombasProximas = total;
      }
      else
        campo[linha][coluna].bombasProximas = -1;
    }
  }
}

void openAll(GameInfo *gameInfo, Matriz **campo)
{
  for (size_t i = 0; i < gameInfo->linhas; i++)
  {
    for (size_t j = 0; j < gameInfo->colunas; j++)
    {
      campo[i][j].aberto = true;
    }
  }
}

void initializeMatriz(GameInfo *gameInfo, Matriz **campo)
{
  for (size_t i = 0; i < gameInfo->linhas; i++)
  {
    for (size_t j = 0; j < gameInfo->colunas; j++)
    {
      campo[i][j].aberto = false;
      campo[i][j].bomba = false;
      campo[i][j].bombasProximas = 0;
      campo[i][j].flag = false;
      campo[i][j].checked = false;
    }
  }
}

void putBombs(Matriz **campo, GameInfo *gameInfo)
{
  int total = 0;
  do
  {
    int linha = getRandomNumber(gameInfo->linhas);
    int coluna = getRandomNumber(gameInfo->colunas);
    if (!campo[linha][coluna].bomba)
    {
      campo[linha][coluna].bomba = true;
      total++;
    }
  } while (total < gameInfo->numBombas);
}

bool playGame(Matriz **campo, GameInfo *gameInfo)
{
  int resultado, linha, coluna, opc;

  while (!gameInfo->perdeu)
  {
    do
    {
      clearScreen();
      showMatriz(gameInfo, campo);
      printf("\nDigite a linha e coluna: ");
      scanf("%d %d", &linha, &coluna);
      printf("\nEscolha (1 - Abrir  2 - Colocar/Remover Bandeira) : ");
      scanf("%d", &opc);
    } while (linha < 0 || linha >= gameInfo->linhas || coluna < 0 || coluna >= gameInfo->colunas || opc < 1 || opc > 2);
    if (opc == 1)
    {
      if (campo[linha][coluna].bomba)
      {
        gameInfo->perdeu = true;
      }
      else
      {
        if (campo[linha][coluna].flag == false)
        {
          campo[linha][coluna].aberto = true;
          if (campo[linha][coluna].bombasProximas == 0)
            openAround(campo, linha, coluna, gameInfo);
          if (verifyVictory(campo, gameInfo))
          {
            clearScreen();
            showMatriz(gameInfo, campo);
            return true;
          }
        }
      }
    }
    else
    {
      putFlag(campo, gameInfo, linha, coluna);
    }
  }
  clearScreen();
  openAll(gameInfo, campo);
  showMatriz(gameInfo, campo);
  return false;
}
