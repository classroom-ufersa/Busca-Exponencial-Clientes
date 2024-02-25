#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
typedef struct cliente Cliente;

int Contagem_clientes(FILE * arquivo);

//void add_clientes(int numero_clientes, Cliente **cliente);

void add_clientes(Cliente ***cliente, int *numero_clientes);

void escrever_arquivo(Cliente **cliente, int numero_clientes);

int verificar_id(Cliente ** cliente, int id_cliente, int numero_clientes);

Cliente * preencher_clientes(char *nome,char *endereco,int id_cliente);

void OrganizarID(Cliente ** cliente,int numero_clientes);

void OrganizarNome(Cliente ** cliente,int numero_clientes);

int BuscaExponencialID(Cliente ** cliente,int id_busca,int numero_clientes);

int BuscaExponencialNome(Cliente ** cliente,char *nome_busca,char numero_clientes);

int BuscaBinariaId(Cliente **clientes, int begin, int end, int id);

int BuscaBinariaNome(Cliente **clientes, int begin, int end, char *nome);

void capitalizeNames(char *str);

void Exibir_listacliente(FILE * arquivo);

void menu();
