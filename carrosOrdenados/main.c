#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Carro.h"
#include "Menu.h"
#include "ArvBinBusca.h"

int main()
{
  Lista *carros = criar();
  Arv *arvPlaca = cria();
  Arv *arvMarca = cria();
  Arv *arvAno = cria();
  bool desejaSair = false;
  while (!desejaSair)
  {
    menuPrincipal(&carros, &arvPlaca, &arvMarca, &arvAno, &desejaSair);
  }
}