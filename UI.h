#ifndef UI_H
#define UI_H
#include "venda.h"
#include "produto.h"
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
int menu_ou_sair();

void limpar_ecra();

int ler_ficheiro_csv(void **items_ptr, int *registo, const char *file_name, int is_produto);

#endif