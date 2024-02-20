/*TAD: Cliente*/
#include"cliente.h"
struct cliente{
    char nome[80];
    char endereco[80];
    int id_cliente;
};

Cliente * preencher_clientes(char nome[80],char endereco[80],int id_cliente){
    Cliente * a=(Cliente*)malloc(sizeof(Cliente));
    strcpy(a->nome,nome);
    strcpy(a->endereco,endereco);
    a->id_cliente=id_cliente;
    return a;
}

int Contagem_clientes(FILE * arquivo){
    int numero_clientes=0;
    while(!(feof(arquivo))){
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes,Cliente **cliente){
    cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
    printf("Informe nome do novo cliente");
    scanf("%[^\n]",cliente[(numero_clientes)]->nome);

    printf("Informe endeço do novo cliente");
    scanf("%[^\n]",cliente[(numero_clientes)]->endereco);

    printf("Informe o codigo do novo cliente");
    scanf("%d",&cliente[(numero_clientes)]->id_cliente);

    FILE * arquivo=fopen("Lista clientes->txt","a");
    fprintf(arquivo,"%s\t%s\t%d",cliente[(numero_clientes)]->nome,cliente[(numero_clientes)]->endereco,cliente[(numero_clientes)]->id_cliente);
    
    fclose(arquivo);
}


