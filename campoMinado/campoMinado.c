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

typedef struct matriz {
  bool bomba;
  bool aberto;
  int bombasProximas; 
} Matriz;

typedef struct tempo {
  int dia;
  int mes;
  int ano;
  int hora;
  int min;
  int seg;
} Tempo;

Matriz** alocarMatriz(int Linhas,int Colunas);
int getRandomNumber(int max);
void showMatriz(int linhas, int colunas, Matriz** campo);
int getInt(int min, int max, char str[]);
void clearScreen();
Tempo* getTime();
void putBombs(Matriz** campo, int linhas, int colunas, int numBombas);
void initializeMatriz(int linhas, int colunas, Matriz** campo);

int main(){

  int linhas, colunas, numBombas, totalPosicoes;
  Matriz** campo; 
  Tempo* tempoInicial;

  tempoInicial = getTime();

  printf("Numero de linhas: ");
  scanf("%d", &linhas);
  printf("Numero de colunas: ");
  scanf("%d", &colunas);

  totalPosicoes = linhas*colunas;

  printf("Numero de Bombas (1-%d) : ", totalPosicoes);
  numBombas = getInt(1, totalPosicoes, "Digite novamente: ");
  
  //Aloca e inicializa a matriz
  campo = alocarMatriz(linhas, colunas);

  if(campo == NULL) return 0;
  
  clearScreen();

  putBombs(campo, linhas, colunas, numBombas);

  showMatriz(linhas, colunas, campo); 
    
  //printf("Dia: %d Mes: %d Ano: %d Hora: %d Min: %d Seg: %d\n", tempoInicial->dia, tempoInicial->mes, tempoInicial->ano, tempoInicial->hora, tempoInicial->min, tempoInicial->seg);
  
 
  return 0;
}

void initializeMatriz(int linhas, int colunas, Matriz** campo){
  for(size_t i = 0; i < linhas; i++)
  {
    for(size_t j = 0; j < colunas; j++)
    {
      campo[i][j].aberto = false;
      campo[i][j].bomba= false;
      campo[i][j].bombasProximas = 0;
    }
    
  }
  
}

void putBombs(Matriz** campo, int linhas, int colunas, int numBombas){
  int total = 0;
  do{
    int linha = getRandomNumber(linhas);
    int coluna = getRandomNumber(colunas);
    if(!campo[linha][coluna].bomba){
      campo[linha][coluna].bomba = true;
      total++;
    }
  }while(total!=numBombas);
}

Tempo* getTime(){
  time_t timer;
  struct tm *horarioLocal;
  Tempo* t = (Tempo*)malloc(sizeof(Tempo)); 

  time(&timer); // Obtem informações de data e hora
  horarioLocal = localtime(&timer); // Converte a hora atual para a hora local


  t->dia = horarioLocal->tm_mday;
  t->mes = horarioLocal->tm_mon + 1;
  t->ano = horarioLocal->tm_year + 1900;
  t->hora = horarioLocal->tm_hour;
  t->min  = horarioLocal->tm_min;
  t->seg  = horarioLocal->tm_sec;
  
  return t;
}

void clearScreen(){
  system("@cls||clear");
}

int getInt(int min, int max, char str[]){
  int aux = 0;
  bool errou = false;
  while(aux > max|| aux < min){
    if(errou) printf("%s", str);
    scanf("%d", &aux);
    errou = true;
  }
  return aux;
}

void showMatriz(int linhas, int colunas, Matriz** campo){

  printf("     ");
  for(int j = 0; j < colunas; j++){ 
    printf(" %d    ", j);
  }
  printf("\n\n");
  for(int i = 0; i < linhas; i++)
  {
    printf(" %d   ", i);
    for(int j = 0; j < colunas; j++){ 
      printf("[%d]   ", campo[i][j].bomba);
    }
    printf("\n\n");
  }

}

Matriz** alocarMatriz(int linhas,int colunas){ 
 
  Matriz **m = (Matriz**)malloc(linhas * sizeof(Matriz*)); 
 
  for (int i = 0; i < linhas; i++){ 
       m[i] = (Matriz*) malloc(colunas * sizeof(Matriz)); 
  }

  if (m==NULL) {
    printf("Memoria insuficiente.\n");
    return m;
  }

  initializeMatriz(linhas, colunas, m);

  return m; 
}

int getRandomNumber(int max){
  
  int randomNumber;
  
  srand (time(NULL));
  randomNumber = rand() % max;

  return randomNumber;
}
