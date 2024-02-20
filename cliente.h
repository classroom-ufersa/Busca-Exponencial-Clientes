#include<stdio.h>
typedef struct cliente Cliente;

int Contagem_clientes(FILE * arquivo);

void add_clientes(int numero_clientes,Cliente *cliente);

void preencher_clientes(FILE * arquivo,Cliente * cliente);