/*TAD: Cliente*/
#include"cliente.h"
struct cliente{
    char nome[81];
    char endereco[81];
    int id_cliente;
};
//Cliente * preencher_clientes(char nome[81],char endereco[81],int id_cliente){
Cliente * preencher_clientes(char *nome,char *endereco,int id_cliente){
    Cliente * a=(Cliente*)malloc(sizeof(Cliente));
    if(a == NULL) {
        printf("erro!");
    }
    strcpy(a->nome,nome);
    strcpy(a->endereco,endereco);
    a->id_cliente=id_cliente;
    return a;
}

int Contagem_clientes(FILE * arquivo){
    int numero_clientes=0;
    char linha[100];
    while(fgets(linha,100,arquivo) != NULL){
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes, Cliente **cliente){
    printf("Informe nome do novo cliente\n");
    scanf(" %[^\n]",cliente[(numero_clientes)]->nome);

    printf("Informe endeço do novo cliente\n");
    scanf(" %[^\n]",cliente[(numero_clientes)]->endereco);

    printf("Informe o codigo do novo cliente\n");
    scanf("%d",&cliente[(numero_clientes)]->id_cliente);

    FILE * arquivo=fopen("listaclientes.txt","a");
    fprintf(arquivo,"\n%s\t%s\t%d",cliente[(numero_clientes)]->nome,cliente[(numero_clientes)]->endereco,cliente[(numero_clientes)]->id_cliente);
    
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
    int end=1;
    while(end<numero_clientes && id_busca<cliente[end]->id_cliente){
        end*=2;
    }
    return end;
}


int BuscaExponencialNome(Cliente ** cliente,char nome_busca[80],char numero_clientes){
    if((strcmp(cliente[0]->nome,nome_busca))==0){
        return 0;
    }
    int end=1;
    while(end<numero_clientes && (strcmp(cliente[end]->nome,nome_busca))<0){
        end*=2;
    }
    return end;
}

int BuscaBinariaNome(Cliente **clientes, int begin, int end, char nome_busca[81]){
    if (end>=begin)
    {
        int mid = begin + (end-begin)/2;
        if (strcmp(clientes[mid]->nome, nome_busca) == 0)
        {
            return mid;
        }
        if (strcmp(clientes[mid]->nome, nome_busca) > 0)
        {
            return BuscaBinariaNome(clientes, mid+1, end, nome_busca);
        }
        return BuscaBinariaNome(clientes, begin, mid-1, nome_busca); 
    }
    return -1;
}

int BuscaBinariaId(Cliente **clientes, int begin, int end, int id_busca){
    if (end>=begin)
    {
        int mid = begin + (end-begin)/2;
        if (clientes[mid]->id_cliente == id_busca)
        {
            return mid;
        }
        if (clientes[mid]->id_cliente > id_busca)
        {
            return BuscaBinariaId(clientes, mid+1, end, id_busca);
        }
        return BuscaBinariaId(clientes, begin, mid-1, id_busca); 
    }
    return -1;
}

void Exibir_cliente(FILE * arquivo){
    char linha[100],nome[81],endereco[81];
    int id_cliente;
    rewind(arquivo);
    while(fgets(linha,100,arquivo) != NULL){
        sscanf(linha,"%[^\t]\t%[^\t]\t%d\n",nome,endereco,&id_cliente);
        printf("%s\t",nome);
        printf("%s\t",endereco);
        printf("%d\n",id_cliente);
    }
}
