#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct
{
    int codigo;
    char designacao[50];
    float preco;
} Produto;

void adicionar_produto(Produto **items, int *records);
void remover_produto(Produto items[], int *records);
void editar_produto(Produto *items, int *records);
void procurar_produto(Produto *items, int records);

#endif