#include "autoPlay.h"

bool autoPlay(Matriz **campo, GameInfo *gameInfo)
{
  int resultado, linha, coluna, opc;
  while (!gameInfo->perdeu && !gameInfo->ganhou)
  {
    clearScreen();
    showMatriz(gameInfo, campo);
    if (!tryPlay(campo, gameInfo))
    {
      linha = getRandomNumber(gameInfo->linhas);
      coluna = getRandomNumber(gameInfo->colunas);
      if (campo[linha][coluna].flag == false)
      {
        if (campo[linha][coluna].bomba)
        {
          gameInfo->perdeu = true;
        }
        else
        {
          if (!campo[linha][coluna].aberto)
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
            printf("\nJogada linha: %d, coluna: %d\n", linha, coluna);
            sleep(1);
          }
        }
      }
    }
    else
    {
      sleep(1);
    }
  }
  openAll(gameInfo, campo);
  clearScreen();
  showMatriz(gameInfo, campo);
  return false;
}

bool tryPlay(Matriz **campo, GameInfo *gameInfo)
{
  bool worked = false;
  for (size_t i = 0; i < gameInfo->linhas; i++)
  {
    for (size_t j = 0; j < gameInfo->colunas; j++)
    {
      if (campo[i][j].aberto && campo[i][j].bombasProximas > 0)
      {
        if (findBombs(campo, gameInfo, i, j))
        {
          clearScreen();
          showMatriz(gameInfo, campo);
          if (findSafeSquares(campo, gameInfo, i, j))
          {
            worked = true;
          }
        }
      }
    }
  }
  if (verifyVictory(campo, gameInfo))
  {
    clearScreen();
    gameInfo->ganhou = true;
    showMatriz(gameInfo, campo);
    return true;
  }
  return worked;
}

bool findBombs(Matriz **campo, GameInfo *gameInfo, int linha, int coluna)
{
  bool worked = false;
  int total = 0;
  if (linha > 0 && !campo[linha - 1][coluna].aberto)
    total++;
  if (linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna].aberto)
    total++;
  if (coluna > 0 && !campo[linha][coluna - 1].aberto)
    total++;
  if (coluna < gameInfo->colunas - 1 && !campo[linha][coluna + 1].aberto)
    total++;
  if (coluna > 0 && linha > 0 && !campo[linha - 1][coluna - 1].aberto)
    total++;
  if (linha > 0 && coluna < gameInfo->colunas - 1 && !campo[linha - 1][coluna + 1].aberto)
    total++;
  if (coluna > 0 && linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna - 1].aberto)
    total++;
  if (linha < gameInfo->linhas - 1 && coluna < gameInfo->colunas - 1 && !campo[linha + 1][coluna + 1].aberto)
    total++;
  if (campo[linha][coluna].bombasProximas != 0 && campo[linha][coluna].bombasProximas == total)
  {
    if (linha > 0 && !campo[linha - 1][coluna].aberto && !campo[linha - 1][coluna].flag)
    {
      campo[linha - 1][coluna].flag = true;
      worked = true;
    }
    if (linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna].aberto && !campo[linha + 1][coluna].flag)
    {
      campo[linha + 1][coluna].flag = true;
      worked = true;
    }
    if (coluna > 0 && !campo[linha][coluna - 1].aberto && !campo[linha][coluna - 1].flag)
    {
      campo[linha][coluna - 1].flag = true;
      worked = true;
    }
    if (coluna < gameInfo->colunas - 1 && !campo[linha][coluna + 1].aberto && !campo[linha][coluna + 1].flag)
    {
      campo[linha][coluna + 1].flag = true;
      worked = true;
    }
    if (coluna > 0 && linha > 0 && !campo[linha - 1][coluna - 1].aberto && !campo[linha - 1][coluna - 1].flag)
    {
      campo[linha - 1][coluna - 1].flag = true;
      worked = true;
    }
    if (linha > 0 && coluna < gameInfo->colunas - 1 && !campo[linha - 1][coluna + 1].aberto && !campo[linha - 1][coluna + 1].flag)
    {
      campo[linha - 1][coluna + 1].flag = true;
      worked = true;
    }
    if (coluna > 0 && linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna - 1].aberto && !campo[linha + 1][coluna - 1].flag)
    {
      campo[linha + 1][coluna - 1].flag = true;
      worked = true;
    }
    if (linha < gameInfo->linhas - 1 && coluna < gameInfo->colunas - 1 && !campo[linha + 1][coluna + 1].aberto && !campo[linha + 1][coluna + 1].flag)
    {
      campo[linha + 1][coluna + 1].flag = true;
      worked = true;
    }
  }
  return worked;
}

bool findSafeSquares(Matriz **campo, GameInfo *gameInfo, int linha, int coluna)
{
  bool worked = false;
  int total = 0;
  if (linha > 0 && campo[linha - 1][coluna].flag)
    total++;
  if (linha < gameInfo->linhas - 1 && campo[linha + 1][coluna].flag)
    total++;
  if (coluna > 0 && campo[linha][coluna - 1].flag)
    total++;
  if (coluna < gameInfo->colunas - 1 && campo[linha][coluna + 1].flag)
    total++;
  if (coluna > 0 && linha > 0 && campo[linha - 1][coluna - 1].flag)
    total++;
  if (linha > 0 && coluna < gameInfo->colunas - 1 && campo[linha - 1][coluna + 1].flag)
    total++;
  if (coluna > 0 && linha < gameInfo->linhas - 1 && campo[linha + 1][coluna - 1].flag)
    total++;
  if (linha < gameInfo->linhas - 1 && coluna < gameInfo->colunas - 1 && campo[linha + 1][coluna + 1].flag)
    total++;
  if (campo[linha][coluna].bombasProximas == total)
  {
    if (linha > 0 && !campo[linha - 1][coluna].aberto && !campo[linha - 1][coluna].flag)
    {
      campo[linha - 1][coluna].aberto = true;
      openAround(campo, linha - 1, coluna, gameInfo);
      worked = true;
    }
    if (linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna].aberto && !campo[linha + 1][coluna].flag)
    {
      campo[linha + 1][coluna].aberto = true;
      openAround(campo, linha + 1, coluna, gameInfo);
      worked = true;
    }
    if (coluna > 0 && !campo[linha][coluna - 1].aberto && !campo[linha][coluna - 1].flag)
    {
      campo[linha][coluna - 1].aberto = true;
      openAround(campo, linha, coluna - 1, gameInfo);
      worked = true;
    }
    if (coluna < gameInfo->colunas - 1 && !campo[linha][coluna + 1].aberto && !campo[linha][coluna + 1].flag)
    {
      campo[linha][coluna + 1].aberto = true;
      openAround(campo, linha, coluna + 1, gameInfo);
      worked = true;
    }
    if (coluna > 0 && linha > 0 && !campo[linha - 1][coluna - 1].aberto && campo[linha - 1][coluna - 1].flag)
    {
      campo[linha - 1][coluna - 1].aberto = true;
      openAround(campo, linha - 1, coluna - 1, gameInfo);
      worked = true;
    }
    if (linha > 0 && coluna < gameInfo->colunas - 1 && !campo[linha - 1][coluna + 1].aberto && !campo[linha - 1][coluna + 1].flag)
    {
      campo[linha - 1][coluna + 1].aberto = true;
      openAround(campo, linha - 1, coluna + 1, gameInfo);
      worked = true;
    }
    if (coluna > 0 && linha < gameInfo->linhas - 1 && !campo[linha + 1][coluna - 1].aberto && !campo[linha + 1][coluna - 1].flag)
    {
      campo[linha + 1][coluna - 1].aberto = true;
      openAround(campo, linha + 1, coluna - 1, gameInfo);
      worked = true;
    }
    if (linha < gameInfo->linhas - 1 && coluna < gameInfo->colunas - 1 && !campo[linha + 1][coluna + 1].aberto && !campo[linha + 1][coluna + 1].flag)
    {
      campo[linha + 1][coluna + 1].aberto = true;
      openAround(campo, linha + 1, coluna + 1, gameInfo);
      worked = true;
    }
  }
  return worked;
}