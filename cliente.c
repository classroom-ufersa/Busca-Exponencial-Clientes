/*TAD: Cliente*/
#include"cliente.h"
#include<stdio.h>
#include<stdlib.h>
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

void OrganizarID(Cliente ** cliente,int numero_clientes){
    int count1,count2;
    Cliente * a=(Cliente*)malloc(sizeof(Cliente));
    a=cliente[0];
    for(count1=0;count1<numero_clientes;count1++){
        for(count2=0;count2<numero_clientes-1;count2++){
            if(cliente[count2]->id_cliente>cliente[count2+1]->id_cliente){
                a=cliente[count2];
                cliente[count2]=cliente[count2+1];
                cliente[count2+1]=a;

            }
        }
    }
}

void OrganizarNome(Cliente ** cliente,int numero_clientes){
    int count1,count2;
    Cliente * a=(Cliente*)malloc(sizeof(Cliente));
    a=cliente[0];
    for(count1=0;count1<numero_clientes;count1++){
        for(count2=0;count2<numero_clientes-1;count2++){
            if (strcmp(cliente[count2]->nome, cliente[count2 + 1]->nome) > 0){
                a=cliente[count2];
                cliente[count2]=cliente[count2+1];
                cliente[count2+1]=a;

            }
        }
    }
}

int BuscaExponencialID(Cliente ** cliente,int id_busca,int numero_clientes){
    if(id_busca==cliente[0]->id_cliente){
        return 0;
    }
    int i=1;
    while(i<numero_clientes && id_busca<cliente[i]->id_cliente){
        i*=2;
    }
    return i;
}


int BuscaExponencialNome(Cliente ** cliente,char nome_busca[80],char numero_clientes){
    if((strcmp(cliente[0]->nome,nome_busca))==0){
        return 0;
    }
    int i=1;
    while(i<numero_clientes && (strcmp(cliente[i]->nome,nome_busca))<0){
        i*=2;
    }
    return i;
}

