#include "utils.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "structs.h"
#include "handleMatriz.h"
#include "handleScreen.h"
#include "autoPlay.h"

int main()
{
  GameInfo *gameInfo;
  Matriz **campo;
  time_t start_t, end_t;
  double duracao;
  int resultado, opc;

  srand(time(0));

  gameInfo = (GameInfo *)malloc(sizeof(GameInfo));
  gameInfo->perdeu = false;
  gameInfo->ganhou = false;

  do
  {
    clearScreen();
    printf("Numero de linhas: ");
    scanf("%d", &gameInfo->linhas);
    printf("Numero de colunas: ");
    scanf("%d", &gameInfo->colunas);
  } while (gameInfo->linhas < 0 || gameInfo->colunas < 0);
  gameInfo->totalPosicoes = gameInfo->linhas * gameInfo->colunas;

  printf("Numero de Bombas (1-%d) : ", gameInfo->totalPosicoes);
  gameInfo->numBombas = getInt(1, gameInfo->totalPosicoes, "Digite novamente: ");

  //Aloca e inicializa a matriz
  campo = alocarMatriz(gameInfo);
  //Verifica se deu certo
  if (campo == NULL)
    return 0;
  putBombs(campo, gameInfo);
  locateBombs(gameInfo, campo);

  do
  {
    clearScreen();
    printf(" Quem vai jogar?\n 1- Voce\n 2- Computador\n\n Opcao: ");
    scanf("%d", &opc);
  } while (opc < 0 || opc > 2);

  //Salva o tempo inicial
  time(&start_t);

  //loop principal do game
  if (opc == 1)
    resultado = playGame(campo, gameInfo);
  else
    resultado = autoPlay(campo, gameInfo);

  if (resultado)
    winScreeen();
  else
    loseScreen();

  //Salva o tempo final
  time(&end_t);
  duracao = difftime(end_t, start_t);
  printf(" Duracao da partida = %0.f segundos\n\n", duracao);
  return 0;
}
