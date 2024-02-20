#include<stdio.h>
typedef struct cliente Cliente;

int Contagem_clientes(FILE * arquivo);

void add_clientes(int numero_clientes,Cliente *cliente);

Cliente * preencher_clientes(const char* nome,const char* endereco,int id_cliente);