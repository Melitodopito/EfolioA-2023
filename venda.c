#include "venda.h"
#include "produto.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

void gerar_relatorio_vendas(Produto items[], int num_produtos, Venda vendas[], int num_vendas)
{
  // Alocar memória
  Venda *vendas_por_produto = (Venda *)malloc(num_produtos * sizeof(Venda));
  if (vendas_por_produto == NULL)
  {
    printf("Erro ao alocar memória para vendas_por_produto.\n");
    return;
  }

  for (int i = 0; i < num_produtos; i++)
  {
    vendas_por_produto[i].codigo = items[i].codigo;
    vendas_por_produto[i].quantidade_vendida = 0;
  }

  // Calcular a quantidade vendida
  for (int i = 0; i < num_vendas; i++)
  {
    int codigo_produto = vendas[i].codigo;
    int quantidade_vendida = vendas[i].quantidade_vendida;
    for (int j = 0; j < num_produtos; j++)
    {
      if (items[j].codigo == codigo_produto)
      {
        vendas_por_produto[j].quantidade_vendida += quantidade_vendida;
        break;
      }
    }
  }

  // Imprimir relatório
  printf("Relatório de vendas\n");
  printf("-------------------------------------\n");
  printf("%-10s%-20s%-25s%s\n", "Código", "Produto", "Quantidade Vendida", "Receitas");
  float total_arrecadado = 0;
  int total_vendas = 0;
  for (int i = 0; i < num_produtos; i++)
  {
    int codigo_produto = vendas_por_produto[i].codigo;
    int quantidade_vendida = vendas_por_produto[i].quantidade_vendida;
    float preco = 0;
    for (int j = 0; j < num_produtos; j++)
    {
      if (items[j].codigo == codigo_produto)
      {
        preco = items[j].preco;
        printf("%-9d%-20s%-25d", codigo_produto, items[j].designacao, quantidade_vendida);
        break;
      }
    }
    float valor_vendas = preco * quantidade_vendida;
    total_arrecadado += valor_vendas;
    printf("%.2f\n", valor_vendas);
    total_vendas += quantidade_vendida;
  }
  printf("-------------------------------------\n");
  printf("%-35s%d\n", "Total de vendas:", total_vendas);
  printf("%-35s%.2f\n", "Total arrecadado:", total_arrecadado);

  // libertar Memoria
  free(vendas_por_produto);
  int opcao = menu_ou_sair();
  if (opcao == 1)
  {
    return;
  }
  else if (opcao == 2)
  {
    exit(0);
  }
}
