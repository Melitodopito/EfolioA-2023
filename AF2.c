#include "venda.h"
#include "produto.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int main()
{
  setlocale(LC_ALL, "pt_PT.utf8");
  Produto *items = NULL;
  int registo = 0;
  int op = 0;
  int num_vendas = 0;
  Venda *vendas = NULL;

  ler_ficheiro_csv((void **)&items, &registo, "produtos.csv", 1);
  ler_ficheiro_csv((void **)&vendas, &num_vendas, "vendas.csv", 0);

  while (1)
  {
    printf("\nMENU------------------------------\n");
    printf("----------------------------------\n");
    printf("----------------------------------\n\n");
    printf("-Selecione o que deseja fazer:    \n");
    printf("-1-Adicionar Produto              \n");
    printf("-2-Remover Produto                \n");
    printf("-3-Editar Produto                 \n");
    printf("-4-Encontrar um Produto           \n");
    printf("-5-Relatorio de Vendas            \n");
    printf("-6-Sair do programa               \n");
    printf("----------------------------------\n");
    printf("----------------------------------\n\n");
    printf("-Opção Desejada: ");
    scanf("%d", &op);
    printf("\n");

    if (op == 1)
    {
      adicionar_produto(&items, &registo);
    }
    else if (op == 2)
    {
      remover_produto(items, &registo);
    }
    else if (op == 3)
    {
      editar_produto(items, &registo);
    }
    else if (op == 4)
    {
      procurar_produto(items, registo);
    }
    else if (op == 5)
    {
      gerar_relatorio_vendas(items, registo, vendas, num_vendas);
    }
    else if (op == 6)
    {
      break;
    }
    else
    {
      limpar_ecra();
      printf(" \nAcção não válida\nPor favor Insira uma Opção válida\n ");
      continue;
    }
  }

  free(items);
  free(vendas);

  return 0;
}