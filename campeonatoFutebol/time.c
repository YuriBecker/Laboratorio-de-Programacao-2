
#include "time.h"

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
  t->eliminado = false;
  t->pontos = 0;
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

// Imprime a lista de times usando a funcao auxiliar imprimirTime
void imprimirTimes(Lista *times)
{
  imprimir(times, &imprimirTime);
}

//verifica se eh possivel inicar um campeonato
bool verificarTimes(Lista *times)
{
  int numTimes = 0;
  bool aprovado = true;
  if (!vazia(times))
  {
    Lista *temp = times;
    while (!vazia(temp))
    {
      int numJogadores = 0;
      bool goleiro = false;
      if (((Time *)temp->info)->idTreinador < 1)
      {
        printf("\n %s nao possui treinador!\n", ((Time *)temp->info)->nome);
        aprovado = false;
      }

      Lista *jogador = ((Time *)temp->info)->jogadores;
      while (!vazia(jogador))
      {
        if (((Jogador *)jogador->info)->posicao == GOLEIRO)
          goleiro = true;
        numJogadores++;
        jogador = jogador->prox;
      }
      if (!goleiro)
      {
        printf("\n %s nao possui goleiro!\n", ((Time *)temp->info)->nome);
        aprovado = false;
      }
      if (numJogadores < 7)
      {
        printf("\n %s possui menos de 7 jogadores!\n", ((Time *)temp->info)->nome);
        aprovado = false;
      }
      else
      {
        if (numJogadores > 25)
        {
          printf("\n %s possui mais de 25 jogadores\n", ((Time *)temp->info)->nome);
          aprovado = false;
        }
      }

      temp = temp->prox;
      numTimes++;
      printf("\n");
    }
    if (!potenciaDeDois(numTimes))
    {
      printf("\n O numero de times cadastrados nao eh potencia de dois!\n");
      aprovado = false;
    }
  }
  else
  {
    printf("\n\nNenhum time cadastrado!\n");
    aprovado = false;
  }
  return aprovado;
}

bool potenciaDeDois(int num)
{
  switch (num)
  {
  case 2:
  case 4:
  case 8:
  case 16:
  case 32:
  case 64:
    return true;
  default:
    return false;
    break;
  }
}