//Implemente o jogo Campo Minado. Veja uma poss´ıvel descri¸c˜ao do jogo em
//http://pt.wikipedia.org/wiki/Campo_minado. Observa¸c˜oes:
//• Deve ser usada aloca¸c˜ao dinˆamica para a(s) matriz(es).
//• O programa deve ser organizado em diferentes arquivos e fun¸c˜oes, se necess´ario.
//• O usu´ario escolhe a dimens˜ao da matriz e o n´umero de bombas.
//• Deve ser contado o tempo decorrido desde o in´ıcio do jogo.
//• Deve haver uma op¸c˜ao na qual o computador tenta resolver o jogo (de
//maneira inteligente, n˜ao simplesmente aleat´oria).

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct matriz
{
  bool bomba;
  bool aberto;
  bool checked;
  bool flag;
  int bombasProximas;
} Matriz;

typedef struct gameInfo
{
  int linhas;
  int colunas;
  int numBombas;
  int totalPosicoes;
  bool perdeu;
} GameInfo;

Matriz **alocarMatriz(GameInfo *gameInfo);
int getRandomNumber(int max);
void showMatriz(GameInfo *gameInfo, Matriz **campo);
int getInt(int min, int max, char str[]);
void clearScreen();
void putBombs(Matriz **campo, GameInfo *gameInfo);
void locateBombs(GameInfo *gameInfo, Matriz **campo);
void initializeMatriz(GameInfo *gameInfo, Matriz **campo);
void openAll(GameInfo *gameInfo, Matriz **campo);
bool playGame(Matriz **campo, GameInfo *gameInfo);
bool verifyVictory(Matriz **campo, GameInfo *gameInfo);
void putFlag(Matriz **campo, GameInfo *gameInfo, int linha, int coluna);
void openAround(Matriz **campo, int linha, int coluna, GameInfo *gameInfo);
void header();
void winScreeen();
void loseScreen();

int main()
{
  GameInfo *gameInfo;
  Matriz **campo;
  time_t start_t, end_t;
  double duracao;
  int resultado;

  srand(time(0));

  gameInfo = (GameInfo *)malloc(sizeof(GameInfo));
  gameInfo->perdeu = false;

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
  //Salva o tempo inicial
  time(&start_t);
  //loop principal do game
  resultado = playGame(campo, gameInfo);
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
        campo[linha][coluna].aberto = true;
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
  openAll(gameInfo, campo);
  clearScreen();
  showMatriz(gameInfo, campo);
  return false;
}

void header()
{
  printf("\n CAMPO MINADO - YURI BECKER\n\n\n");
}

void winScreeen()
{
  printf("\n VOCE GANHOU!!\n\n");
}

void loseScreen()
{
  printf("\n VOCE PERDEU!!\n\n");
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
      if (campo[linha][coluna].flag == true)
        campo[linha][coluna].flag = false;
      else
        campo[linha][coluna].flag = true;
}

bool verifyVictory(Matriz **campo, GameInfo *gameInfo)
{
  int count = 0;
  int total = gameInfo->linhas * gameInfo->colunas - gameInfo->numBombas;
  for (size_t l = 0; l < gameInfo->linhas; l++)
  {
    for (size_t c = 0; c < gameInfo->colunas; c++)
    {
      if (campo[l][c].aberto)
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

void clearScreen()
{
  system("@cls||clear");
}

int getInt(int min, int max, char str[])
{
  int aux = 0;
  bool errou = false;
  while (aux > max || aux < min)
  {
    if (errou)
      printf("%s", str);
    scanf("%d", &aux);
    errou = true;
  }
  return aux;
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
      if (campo[i][j].flag)
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

int getRandomNumber(int max)
{
  return rand() % max;
}