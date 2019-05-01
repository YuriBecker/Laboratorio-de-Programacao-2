
#include "time.h"

/*
   Funcoes obrigatorias.
   
   As funcoes a seguir sao necessarias para parametrizar as funcoes genericas
   da lista de void. 

*/

// Mostra na tela os dados de um time.
void imprimirTime(void *time)
{
  Time *t = (Time *)time;
  printf("--------------------------------\n");
  printf(" ID Time: %d \n %s \n Estadio: %s \n Cidade: %s\n", t->id, t->nome, t->estadio, t->cidade);
  if (t->jogadores != NULL)
  {
    imprimirJogadores(t->jogadores);
    printf("--------------------------------\n");
  }
}

// Compara a igualdade entre times.
bool timesIguais(void *time1, void *time2)
{
  return ((Time *)time1)->id == ((Time *)time2)->id;
}

/*
  Funcoes opcionais.
  
  As funcoes a seguir sao auxiliares. Elas foram criadas para facilitar a escrita 
  do id cliente e para melhorar sua legibilidade.
  
  Neste exemplo, todo o id cliente esta no arquivo main.
*/

unsigned int gerarIdTime()
{
  static int ID = 1;
  return ID++;
}

// Cria um time com o id preenchido
Time *criarTimePK()
{
  Time *t = (Time *)malloc(sizeof(Time));
  t->nome = (char *)malloc(sizeof(char) * 50);
  t->cidade = (char *)malloc(sizeof(char) * 50);
  t->estadio = (char *)malloc(sizeof(char) * 50);
  t->dataFundacao = (char *)malloc(sizeof(char) * 50);
  t->id = gerarIdTime();
  t->jogadores = criar();
  t->idTreinador = -1;
  t->golsFeitos = 0;
  t->golsSofridos = 0;
  return t;
}

// Cria um time com o id e o nome preenchidos
Time *criarTime(const char *nome, const char *estadio, const char *cidade, const char *dataFundacao)
{
  Time *t = criarTimePK();
  strcpy(t->nome, nome);
  strcpy(t->estadio, estadio);
  strcpy(t->cidade, cidade);
  strcpy(t->dataFundacao, dataFundacao);
  return t;
}

/* Em C++ as funcoes criarJogador e criarJogadorPK poderiam ser 
   sobrecarregadas (terem o mesmo nome) */

// Busca um time pelo código.
Time *buscarTime(Lista *times, int id)
{
  Time *t = (Time *)malloc(sizeof(Time));
  t->id = id;
  return (Time *)buscar(times, t, &timesIguais);
}

// Adiciona um jogador a um time.
void inscrever(Time *time, Jogador *jogador)
{
  jogador->idTime = time->id;
  time->jogadores = inserirFim(time->jogadores, jogador);
}

// Retira um jogador de um time.
void desinscrever(Time *time, int id)
{
  Jogador *jogador = buscarJogador(time->jogadores, id);
  jogador->idTime = -1;
  time->jogadores = retirarJogadorP(time->jogadores, buscarJogador(time->jogadores, id));
}

/* Em C++ as funcoes retirarTime e retirarTimeP poderiam ser 
   sobrecarregadas (terem o mesmo nome) */

// Retira um time através de um ponteiro para este time.
Lista *retirarTimeP(Lista *times, Time *time)
{
  return retirar(times, time, &timesIguais);
}

// Retira um time através do código do time
Lista *retirarTime(Lista *times, int id)
{
  return retirarTimeP(times, buscarTime(times, id));
}

/* Em C++ as funcoes retirarJogador e retirarJogadorP poderiam ser 
   sobrecarregadas (terem o mesmo nome) */

// Imprime a lista de times usando a funcao auxiliar imprimirTime
void imprimirTimes(Lista *times)
{
  imprimir(times, &imprimirTime);
}
