#include "venda.h"
#include "produto.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

int menu_ou_sair()
{
  int opcao;
  do
  {
    printf("\nDeseja voltar ao menu principal ou sair do programa?\n");
    printf("1. Voltar ao menu principal\n");
    printf("2. Sair do programa\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);

    if (opcao < 1 || opcao > 2)
    {

      printf("\nOpção inválida. Por favor, digite 1 ou 2.\n");
    }
  } while (opcao < 1 || opcao > 2);

  return opcao;
}

void limpar_ecra()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int ler_ficheiro_csv(void **items_ptr, int *registo, const char *file_name, int is_produto)
{
  // Abrir ficheiro
  FILE *file;

  file = fopen(file_name, "r+");

  if (file == NULL)
  {
    printf("Erro ao abrir %s\n", file_name);
    exit(1);
  }

  int read = 0;
  *registo = 0;
  // Alocar memoria
  do
  {
    if (is_produto)
    {

      *items_ptr = (Produto *)realloc(*items_ptr, (*registo + 1) * sizeof(Produto));

      read = fscanf(file, "%i,%49[^,],%f\n",
                    &((Produto *)(*items_ptr))[*registo].codigo,
                    ((Produto *)(*items_ptr))[*registo].designacao,
                    &((Produto *)(*items_ptr))[*registo].preco);
    }
    else
    {
      if (*registo == 0)
      {
        *items_ptr = (Venda *)malloc(10 * sizeof(Venda));
      }
      else if (*registo % 10 == 0)
      {
        *items_ptr = (Venda *)realloc(*items_ptr, (*registo + 10) * sizeof(Venda));
      }

      read = fscanf(file, "%i,%49[^,],%i\n",
                    &((Venda *)(*items_ptr))[*registo].codigo,
                    ((Venda *)(*items_ptr))[*registo].data,
                    &((Venda *)(*items_ptr))[*registo].quantidade_vendida);
    }

    if (read == 3)
      (*registo)++;

    if (read != 3 && !feof(file))
    {
      printf("%s com formato Incorreto, por favor verifique linha nº%d \n", is_produto ? "Produto" : "Venda", *registo + 1);
      exit(2);
    }

    if (ferror(file))
    {
      printf("Error Reading file.\n");
      exit(3);
    }
  } while (!feof(file));

  fclose(file);

  return *registo;
}