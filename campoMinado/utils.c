// #include <stdio.h>
// #include <stdlib.h>
#include <stdbool.h>
// #include <unistd.h>
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

int getRandomNumber(int max)
{
  int retorno = rand() % max;
  return retorno;
}