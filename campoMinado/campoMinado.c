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

Matriz** alocarMatriz(int Linhas,int Colunas);
int geraValorAleatorio(int max);
void visualizarMatriz(int linhas, int colunas, Matriz** campo);
int getInt(int min, int max, char str[]);
void limpaTela();

int main(){

  int linhas, colunas, numBombas, totalPosicoes;
  
  Matriz** campo; 

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
  
  return 0;
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

  for(size_t i = 0; i < linhas; i++)
  {
    for(size_t j = 0; j < colunas; j++){
      printf("%d \t", campo[i][j].aberto);
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

  /* initialize random seed: */
  srand (time(NULL));

  randomNumber = rand() % max;

  return randomNumber;
}
