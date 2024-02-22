#include"cliente.c"



int main(void){
    int index=0,id_cliente,numero_clientes,index_busca,id_busca;
    char nome[81],endereco[81],linha[100],opcao,opcao2,nome_busca[81];

    FILE * aLista=fopen("listaclientes.txt","r");
    numero_clientes=Contagem_clientes(aLista);
    Cliente ** cliente=(Cliente**)malloc(numero_clientes*sizeof(Cliente*));
    rewind(aLista);
    if(cliente == NULL){
        printf("erro!");
    }
    while(fgets(linha,100,aLista) != NULL){
        sscanf(linha,"%[^\t]\t%[^\t]\t%d\n",nome,endereco,&id_cliente);
        cliente[index] = preencher_clientes(nome,endereco,id_cliente);
        index++;
    }//da pra colocar esse while em uma função
    printf("%s", cliente[1]->nome);
    do{
        printf("MENU\n");
        printf("1-Cadastrar novo cliente\n2-Buscar por nome\n3-Buscar por código\n4-Mostrar lista de clientes\n5-Sair\n");
        scanf("%s",&opcao);
        switch (opcao){
        case '1':
            do{
            cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
            add_clientes(numero_clientes,cliente);
            numero_clientes++;
            printf("Adicionar novo cliente?\n(S) ou (N)\n");
            scanf("%c",&opcao2);
            opcao2 = toupper(opcao2); //transforma o caracter em maiúsculo
            } while (opcao2=='S');
            break;
        case '2':
            OrganizarNome(cliente,numero_clientes);
            printf("Informe o nome");
            scanf("%[^\n]",nome_busca);
            index_busca=BuscaExponencialNome(cliente,nome_busca,numero_clientes);
            index_busca=BuscaBinariaNome(cliente,index_busca/2,index_busca,nome_busca);
            if(index_busca<0){
                printf("Erro");
            }
            else{
                printf("%s",cliente[index_busca]->nome);
            }
            break;
        case '3':
            OrganizarID(cliente,numero_clientes);
            printf("Informe o id");
            scanf("%d",&id_busca);
            index_busca=BuscaExponencialID(cliente,id_busca,numero_clientes);
            index_busca=BuscaBinariaId(cliente,index_busca/2,index_busca,id_busca);
            if(index_busca<0){
                printf("Erro");
            }
            else{
                printf("%d",cliente[index_busca]->id_cliente);
            }
            break;
        case '4':
            Exibir_cliente(aLista);
            break;
        case '5':
            printf("Ralwu mofi raleu");
            break;
        default:
            printf("Opção inválida");
            break;
        }
    } while (opcao!='5');
    fclose(aLista);
    for(index=0;index<numero_clientes;index++){
        free(cliente[index]);
    }
    free(cliente);
}
