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

typedef struct tempo
{
  int dia;
  int mes;
  int ano;
  int hora;
  int min;
  int seg;
} Tempo;

Matriz **alocarMatriz(GameInfo *gameInfo);
int getRandomNumber(int max);
void showMatriz(GameInfo *gameInfo, Matriz **campo);
int getInt(int min, int max, char str[]);
void clearScreen();
Tempo *getTime();
void putBombs(Matriz **campo, GameInfo *gameInfo);
void initializeMatriz(GameInfo *gameInfo, Matriz **campo);
bool playGame(Matriz **campo, GameInfo *gameInfo);
bool verifyVictory(Matriz **campo, GameInfo *gameInfo);

int main()
{

  GameInfo *gameInfo;
  Matriz **campo;
  Tempo *tempoInicial;
  int resultado;

  srand(time(0));

  gameInfo = (GameInfo *)malloc(sizeof(GameInfo));

  printf("Numero de linhas: ");
  scanf("%d", &gameInfo->linhas);
  printf("Numero de colunas: ");
  scanf("%d", &gameInfo->colunas);

  gameInfo->totalPosicoes = gameInfo->linhas * gameInfo->colunas;

  printf("Numero de Bombas (1-%d) : ", gameInfo->totalPosicoes);
  gameInfo->numBombas = getInt(1, gameInfo->totalPosicoes, "Digite novamente: ");

  //Aloca e inicializa a matriz
  campo = alocarMatriz(gameInfo);
  //Verifica se deu certo
  if (campo == NULL)
    return 0;

  putBombs(campo, gameInfo);
  tempoInicial = getTime();
  // 1 == ganhou
  // 0 == perdeu
  resultado = playGame(campo, gameInfo);
  //printf("Dia: %d Mes: %d Ano: %d Hora: %d Min: %d Seg: %d\n", tempoInicial->dia, tempoInicial->mes, tempoInicial->ano, tempoInicial->hora, tempoInicial->min, tempoInicial->seg);
  clearScreen();
  printf("%d\n", resultado);
  return 0;
}

bool playGame(Matriz **campo, GameInfo *gameInfo)
{
  int resultado, linha, coluna;
  bool perdeu = false;

  while (!perdeu)
  {
    do
    {
      clearScreen();
      showMatriz(gameInfo, campo);
      printf("\nDigite a linha e coluna: ");
      scanf("%d %d", &linha, &coluna);
    } while (linha < 0 || linha > gameInfo->linhas || coluna < 0 || coluna > gameInfo->colunas);
    if (campo[linha][coluna].bomba)
    {
      perdeu = true;
    }
    else
    {
      campo[linha][coluna].aberto = true;
      if (verifyVictory(campo, gameInfo))
      {
        return true;
      }
    }
  }
  // 0 == perdeu
  return false;
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

void initializeMatriz(GameInfo *gameInfo, Matriz **campo)
{
  for (size_t i = 0; i < gameInfo->linhas; i++)
  {
    for (size_t j = 0; j < gameInfo->colunas; j++)
    {
      campo[i][j].aberto = false;
      campo[i][j].bomba = false;
      campo[i][j].bombasProximas = 0;
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

Tempo *getTime()
{
  time_t timer;
  struct tm *horarioLocal;
  Tempo *t = (Tempo *)malloc(sizeof(Tempo));

  time(&timer);                     // Obtem informações de data e hora
  horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

  t->dia = horarioLocal->tm_mday;
  t->mes = horarioLocal->tm_mon + 1;
  t->ano = horarioLocal->tm_year + 1900;
  t->hora = horarioLocal->tm_hour;
  t->min = horarioLocal->tm_min;
  t->seg = horarioLocal->tm_sec;

  return t;
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

  printf("     ");
  for (int j = 0; j < gameInfo->colunas; j++)
  {
    printf(" %d    ", j);
  }
  printf("\n\n");
  for (int i = 0; i < gameInfo->linhas; i++)
  {
    printf(" %d   ", i);
    for (int j = 0; j < gameInfo->colunas; j++)
    {
      printf("[%d]   ", campo[i][j].bomba);
    }
    printf("\n\n");
  }
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

  int randomNumber;

  randomNumber = rand() % max;

  return randomNumber;
}
