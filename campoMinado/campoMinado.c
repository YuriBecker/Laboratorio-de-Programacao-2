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
int geraValorAleatorio(int max);
void visualizarMatriz(int linhas, int colunas, Matriz** campo);
int getInt(int min, int max, char str[]);
void limpaTela();
Tempo* getTempo();
void plataBombas(Matriz** campo, int numBombas);

int main(){

  int linhas, colunas, numBombas, totalPosicoes;
  Matriz** campo; 
  Tempo* tempoInicial;

  tempoInicial = getTempo();

  printf("Numero de linhas: ");
  scanf("%d", &linhas);
  printf("Numero de colunas: ");
  scanf("%d", &colunas);

  totalPosicoes = linhas*colunas;

  printf("Numero de Bombas (1-%d) : ", totalPosicoes);
  numBombas = getInt(1, totalPosicoes, "Digite novamente: ");
  
  campo = alocarMatriz(linhas, colunas);

  limpaTela();

  visualizarMatriz(linhas, colunas, campo); 

  //printf("Dia: %d Mes: %d Ano: %d Hora: %d Min: %d Seg: %d\n", tempoInicial->dia, tempoInicial->mes, tempoInicial->ano, tempoInicial->hora, tempoInicial->min, tempoInicial->seg);

 
  return 0;
}

void plataBombas(Matriz** campo, int numBombas){

}

Tempo* getTempo(){
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

void limpaTela(){
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

void visualizarMatriz(int linhas, int colunas, Matriz** campo){

  for(int i = 0; i < linhas; i++)
  {
    printf(" %d \t", i);
    for(int j = 0; j < colunas; j++){ 
      printf("[%d] \t", campo[i][j].aberto);
    }
    printf("\n");
  }

}

Matriz** alocarMatriz(int Linhas,int Colunas){ 
 
  Matriz **m = (Matriz**)malloc(Linhas * sizeof(Matriz*)); 
 
  for (int i = 0; i < Linhas; i++){ 
       m[i] = (Matriz*) malloc(Colunas * sizeof(Matriz)); 
  }

  return m; 
}

int geraValorAleatorio(int max){
  
  int randomNumber;
  
  srand (time(NULL));
  randomNumber = rand() % max;

  return randomNumber;
}
