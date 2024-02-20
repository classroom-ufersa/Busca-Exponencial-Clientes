/*TAD: Cliente*/
#include"cliente.h"
#include<stdio.h>
#include<stdlib.h>
struct cliente{
    char nome[80];
    char endereco[80];
    int id_cliente;
};

void preencher_clientes(FILE * arquivo,Cliente * cliente){
    char ler[50];
    int index=0;
    while ((fgets(ler, 50, arquivo)) != EOF){
        sscanf(ler,"%20[^\t]\t%20[^\t]\t%d", cliente[index].nome,cliente[index].endereco,&cliente[index].id_cliente);
        index++;
    }
}

int Contagem_clientes(FILE * arquivo){
    int numero_clientes;
    numero_clientes=0;
    while(!(feof(arquivo))){
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes,Cliente *cliente){
    cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
    printf("Informe nome do novo cliente");
    scanf("%[^\n]",cliente[(numero_clientes)].nome);
    printf("Informe endeço do novo cliente");
    scanf("%[^\n]",cliente[(numero_clientes)].endereco);
    printf("Informe o codigo do novo cliente");
    scanf("%d",&cliente[(numero_clientes)].id_cliente);
    FILE * arquivo=fopen("Lista clientes.txt","a");
    fprintf(arquivo,"%s\t%s\t%d",cliente[(numero_clientes)].nome,cliente[(numero_clientes)].endereco,cliente[(numero_clientes)].id_cliente);

    fclose(arquivo);
}



int busca_exponencial(){}