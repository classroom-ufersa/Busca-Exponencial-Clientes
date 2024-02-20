#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct cliente Cliente;

int Contagem_clientes(FILE * arquivo);

void add_clientes(int numero_clientes,Cliente **cliente);

Cliente * preencher_clientes(char nome[80],char endereco[80],int id_cliente);
