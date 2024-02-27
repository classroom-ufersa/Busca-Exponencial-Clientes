#include"cliente.c"

int main(void){
    int index=0, id_cliente, numero_clientes, id_busca, posicao;
    char nome[81], endereco[81], linha[100], opcao[11], opcao2, nome_busca[81];
    clock_t inicio, fim;
    double tempo_decorrido;

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
    }
    do{
        menu();
        scanf(" %[^\n]",opcao);
        
        if(strcmp(opcao,"1")==0){
            do{
                cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
                add_clientes(numero_clientes,cliente);
                numero_clientes++;

                printf("Deseja adicionar mais um novo cliente?\n(S) ou (N)\n");
                scanf(" %[^\n]",&opcao2);
                opcao2 = toupper(opcao2); //transforma o caracter em maiúsculo

                while(opcao2 != 'S' && opcao2 != 'N') {
                    printf("opcao invalida\nDigite (S) ou (N)\n");
                    scanf(" %[^\n]", &opcao2);
                    opcao2 = toupper(opcao2);
                }
            } while (opcao2=='S');
        }
        else if(strcmp(opcao,"2")==0){
            OrganizarNome(cliente,numero_clientes);
            printf("Informe o nome: ");
            scanf(" %[^\n]",nome_busca);

            verificar_nome(nome_busca);

            while(verificar_nome(nome_busca)==1){
                printf("Nome invalido\n\n");
                printf("Informe nome novamente: ");
                scanf(" %[^\n]", nome_busca);
                verificar_nome(nome_busca);
            }
            inicio = clock();
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
            fim = clock();
            tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f segundos\n", tempo_decorrido);
        }
        else if(strcmp(opcao,"3")==0){
            OrganizarID(cliente,numero_clientes);
            printf("Informe o id: ");
            scanf("%d",&id_busca);
            inicio = clock();
            posicao=BuscaExponencialID(cliente,id_busca,numero_clientes);
            if(posicao < 0){
                printf("Cliente inexistente\n");
            }
            else{
                capitalizeNames(cliente[posicao]->nome);
                capitalizeNames(cliente[posicao]->endereco);
                printf("Nome: %s\n",cliente[posicao]->nome);
                printf("Endereco: %s\n",cliente[posicao]->endereco);
                printf("Id: %d\n\n",cliente[posicao]->id_cliente);
            }
            fim = clock();
            tempo_decorrido = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo de execucao: %f segundos\n", tempo_decorrido);
        }
        else if(strcmp(opcao,"4")==0){
            Exibir_listacliente(aLista);
        }
        else if(strcmp(opcao,"5")==0){
            printf("Obrigado pela preferencia");
        }
        else{
            printf("Opcao invalida\n\n");
        }
    } while (strcmp(opcao,"5")!=0);
    
    fclose(aLista);
    for(index = 0;index < numero_clientes; index++){
        free(cliente[index]);
    }
    free(cliente);
}
