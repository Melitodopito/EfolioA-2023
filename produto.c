#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "venda.h"
#include "produto.h"
#include "UI.h"

void adicionar_produto(Produto **items, int *registo)
{
  int codigo;
  char designacao[50];
  float preco;

  printf("Novo produto\n");

  int valid_input = 0;
  do
  {
    printf("Código: ");
    if (scanf("%d", &codigo) != 1)
    {
      printf("Código inválido. Por favor insira um numero inteiro.\n");

      while (getchar() != '\n')
        ;
    }
    else
    {
      valid_input = 1;
    }
  } while (!valid_input);

  // Verificar existencia de produto
  for (int i = 0; i < *registo; i++)
  {
    if ((*items)[i].codigo == codigo)
    {
      printf("Já existe um produto com este código.\n");
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
  }

  // designacao
  printf("designacao: ");
  scanf(" %[^\n]", designacao);

  // preco
  valid_input = 0;
  do
  {
    printf("preco: ");
    if (scanf("%f", &preco) != 1)
    {
      printf("preco inválido. Por favor insira um número.\n");

      while (getchar() != '\n')
        ;
    }
    else
    {
      valid_input = 1;
    }
  } while (!valid_input);

  // Addicionar
  Produto *new_items = (Produto *)realloc(*items, (*registo + 1) * sizeof(Produto));
  if (new_items == NULL)
  {
    printf("Erro ao alocar memória\n");
    return;
  }
  *items = new_items;

  (*items)[*registo].codigo = codigo;
  strcpy((*items)[*registo].designacao, designacao);
  (*items)[*registo].preco = preco;

  FILE *fp = fopen("produtos.csv", "a");
  if (fp == NULL)
  {
    printf("Erro ao abrir o ficheiro.\n");
    return;
  }
  fprintf(fp, "%d,%s,%.2f\n", codigo, designacao, preco);
  fclose(fp);

  (*registo)++;

  printf("Produto adicionado com sucesso.\n");
}

void remover_produto(Produto items[], int *registo)
{
  int index = -1;
  int codigo;
  char designacao[50];
  float preco;

  printf("Remover produto\n");

  printf("Código: ");
  scanf("%d", &codigo);
  // Procurar Registo
  for (int i = 0; i < *registo; i++)
  {
    if (items[i].codigo == codigo)
    {
      index = i;
      break;
    }
  }

  if (index == -1)
  {
    printf("Produto não encontrado.\n");
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

  // Remover Produto
  for (int i = index; i < *registo - 1; i++)
  {
    items[i] = items[i + 1];
  }
  (*registo)--;

  FILE *fp = fopen("produtos.csv", "r");
  FILE *tmp_fp = fopen("produtos.tmp", "w");
  if (fp == NULL || tmp_fp == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char line[100];
  while (fgets(line, sizeof(line), fp))
  {
    sscanf(line, "%d,%[^,],%f", &codigo, designacao, &preco);
    if (codigo != items[index].codigo)
    {
      fprintf(tmp_fp, "%d,%s,%.2f\n", codigo, designacao, preco);
    }
  }

  fclose(fp);
  fclose(tmp_fp);

  if (remove("produtos.csv") != 0)
  {
    printf("Erro ao remover o arquivo.\n");
    return;
  }

  if (rename("produtos.tmp", "produtos.csv") != 0)
  {
    printf("Erro ao renomear o arquivo.\n");
    return;
  }

  printf("Produto removido com sucesso.\n");
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

void editar_produto(Produto *items, int *registo)
{
  int codigo;
  int index = -1;
  printf("\nMENU----------------------------\n");
  printf("Editar produto------------------\n");
  printf("---------------------------------\n");
  printf("Código: ");
  scanf("%d", &codigo);

  // Procurar por Codigo
  for (int i = 0; i < *registo; i++)
  {
    if (items[i].codigo == codigo)
    {
      index = i;
      break;
    }
  }

  if (index == -1)
  {
    printf("Produto não encontrado.\n\n");
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

  int choice;
  printf("\nEscolha o que deseja editar:\n");
  printf("1. Código\n");
  printf("2. designacao\n");
  printf("3. preco\n");
  printf("4. Todos os campos\n");
  scanf("%d", &choice);

  // Atualizar
  switch (choice)
  {
  case 1:
    printf("Código atual: %d\n", items[index].codigo);
    printf("Novo código: ");
    scanf("%d", &items[index].codigo);
    break;
  case 2:
    printf("designacao atual: %s\n", items[index].designacao);
    printf("Nova designacao: ");
    scanf(" %[^\n]", items[index].designacao);
    break;
  case 3:
    printf("preço atual: %.2f\n", items[index].preco);
    printf("Novo preco: ");
    scanf("%f", &items[index].preco);
    break;
  case 4:
    printf("Código atual: %d\n", items[index].codigo);
    printf("Novo código: ");
    scanf("%d", &items[index].codigo);

    printf("designacao atual: %s\n", items[index].designacao);
    printf("Nova designacao: ");
    scanf(" %[^\n]", items[index].designacao);

    printf("preco atual: %.2f\n", items[index].preco);
    printf("Novo preco: ");
    scanf("%f", &items[index].preco);
    break;
  default:
    printf("Escolha inválida.\n");
    return;
  }

  // Atualizar csv
  FILE *fp = fopen("produtos.csv", "w");
  if (fp == NULL)
  {
    printf("Erro ao abrir o ficheiro.\n");
    return;
  }

  for (int i = 0; i < *registo; i++)
  {
    fprintf(fp, "%d,%s,%.2f\n", items[i].codigo, items[i].designacao, items[i].preco);
  }

  fclose(fp);

  printf("Produto editado com sucesso.\n");
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

void procurar_produto(Produto *items, int registo)
{
  printf("Procurar produto\n");
  printf("Escolha uma opção:\n");
  printf("1. Procurar por código\n");
  printf("2. Procurar por nome\n");
  printf("Opção Desejada: ");

  int opcao;
  scanf("%d", &opcao);
  printf("\n");

  if (opcao == 1)
  {
    int codigo;
    printf("Código: ");
    scanf("%d", &codigo);

    for (int i = 0; i < registo; i++)
    {
      if (items[i].codigo == codigo)
      {
        limpar_ecra();
        printf("Produto encontrado:\n");
        printf("Código: %d\n", items[i].codigo);
        printf("designacao: %s\n", items[i].designacao);
        printf("preco: %.2f\n", items[i].preco);

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
    }
    limpar_ecra();
    printf("Produto não encontrado.\n");
  }
  else if (opcao == 2)
  {
    char nome[50];
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < registo; i++)
    {
      if (strcmp(items[i].designacao, nome) == 0)
      {
        printf("Produto encontrado:\n\n");
        printf("Código: %d\n", items[i].codigo);
        printf("designacao: %s\n", items[i].designacao);
        printf("preco: %.2f\n", items[i].preco);
        return;
      }
    }
    limpar_ecra();
    printf("Produto não encontrado.\n");
  }
  else
  {
    printf("Opção inválida.\n");
  }
}