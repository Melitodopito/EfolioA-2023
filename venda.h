#ifndef VENDA_H
#define VENDA_H
#include "venda.h"
#include "produto.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
  int codigo;
  char data[11];
  int quantidade_vendida;
} Venda;

void gerar_relatorio_vendas(Produto items[], int num_produtos, Venda vendas[], int num_vendas);

#endif