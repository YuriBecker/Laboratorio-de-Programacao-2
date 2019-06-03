#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Carro.h"
#include "Menu.h"

int main()
{
  Lista *carros = criar();
  bool desejaSair = false;
  while (!desejaSair)
  {
    menuPrincipal(&carros, &desejaSair);
  }
}