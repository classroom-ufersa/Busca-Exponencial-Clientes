#include"cliente.c"

int main(void){
    int index=0, id_cliente, numero_clientes, id_busca, posicao;
    char nome[81], endereco[81], linha[100], opcao, opcao2, nome_busca[81];

    FILE * aLista=fopen("listaclientes.txt","r");
    numero_clientes=Contagem_clientes(aLista);
    Cliente ** cliente=(Cliente**)malloc(numero_clientes*sizeof(Cliente*));
    if(cliente == NULL){
        printf("Erro de memoria\n");
        exit(1);
    }
    rewind(aLista);
    if(cliente == NULL){
        printf("erro!\n");
    }
    while(fgets(linha, 100, aLista) != NULL){
        sscanf(linha,"%[^\t]\t%[^\t]\t%d\n",nome,endereco,&id_cliente);
        cliente[index] = preencher_clientes(nome,endereco,id_cliente);
        index++;
    }//da pra colocar esse while em uma função
    do{
        menu();
        scanf("%s",&opcao);
        switch (opcao){
        case '1':
            do{
            numero_clientes = Contagem_clientes(aLista);
            cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
            add_clientes(numero_clientes,cliente);
            numero_clientes++;
            printf("Deseja adicionar mais um novo cliente?\n(S) ou (N)\n");
            scanf(" %[^\n]",&opcao2);
            opcao2 = toupper(opcao2); //transforma o caracter em maiúsculo
            } while (opcao2=='S');
            break;
        case '2':
            OrganizarNome(cliente,numero_clientes);
            printf("Informe o nome: ");
            scanf(" %[^\n]",nome_busca);
            posicao=BuscaExponencialNome(cliente,nome_busca,numero_clientes);
            if(posicao<0){
                printf("Cliente inexistente\n");
            }
            else{
                capitalizeNames(cliente[posicao]->nome);
                printf("Nome: %s\n",cliente[posicao]->nome);
                printf("Endereco: %s\n",cliente[posicao]->endereco);
                printf("Id: %d\n\n",cliente[posicao]->id_cliente);
            }
            break;
        case '3':
            OrganizarID(cliente,numero_clientes);
            printf("Informe o id: ");
            scanf("%d",&id_busca);
            posicao=BuscaExponencialID(cliente,id_busca,numero_clientes);
            if(posicao < 0){
                printf("Cliente inexistente\n");
            }
            else{
                printf("Nome: %s\n",cliente[posicao]->nome);
                printf("Endereco: %s\n",cliente[posicao]->endereco);
                printf("Id: %d\n\n",cliente[posicao]->id_cliente);
            }
            break;
        case '4':
            Exibir_listacliente(aLista);
            break;
        case '5':
            printf("Obrigado pela preferencia");
            break;
        default:
            printf("Opcao invalida\n\n");
            break;
        }
    } while (opcao!='5');
    
    fclose(aLista);
    for(index = 0;index < numero_clientes; index++){
        free(cliente[index]);
    }
    free(cliente);
}
