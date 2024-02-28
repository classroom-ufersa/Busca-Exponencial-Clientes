#include"cliente.c"

int main(void){
    int index=0, id_cliente, numero_clientes, id_busca, posicao;
    char nome[81], endereco[81], linha[100], opcao[11], opcao2, nome_busca[81];
    clock_t inicio, fim;
    double tempo_decorrido;

    FILE * aLista=fopen("listaclientes.txt","r");
    if (aLista == NULL){
        printf("Erro de abertura de arquivo");
        exit(1);
    }
    numero_clientes=Contagem_clientes(aLista);
    Cliente ** cliente=(Cliente**)malloc(numero_clientes*sizeof(Cliente*));
    if(cliente == NULL){
        printf("Erro de memoria\n");
        exit(1);
    }
    rewind(aLista);
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
                limpa_tela();
                cliente=realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
                add_clientes(numero_clientes,cliente);
                numero_clientes++;
                limpa_tela();

                printf("Deseja adicionar mais um novo cliente?\n(S) ou (N)\n");
                scanf(" %[^\n]",&opcao2);
                opcao2 = toupper(opcao2);
                limpa_tela();

                while(opcao2 != 'S' && opcao2 != 'N') {
                    printf("Opcao invalida\n\nDigite (S) ou (N)\n");
                    scanf(" %[^\n]", &opcao2);
                    opcao2 = toupper(opcao2);
                    Sleep(1);
                    limpa_tela();
                }
            } while (opcao2=='S');
        }
        else if(strcmp(opcao,"2")==0){
            limpa_tela();
            OrganizarNome(cliente,numero_clientes);
            printf("Informe o nome: ");
            scanf(" %[^\n]",nome_busca);
            verificar_nome(nome_busca);

            limpa_tela(); 

            while(verificar_nome(nome_busca)==1){
                printf("Nome invalido\n\n");
                printf("Informe o nome novamente: ");
                scanf(" %[^\n]", nome_busca);
                verificar_nome(nome_busca);
                limpa_tela();         
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
            
            pressiona_enter();
            limpa_tela();
        }
        else if(strcmp(opcao,"3")==0){
            limpa_tela();
            OrganizarID(cliente,numero_clientes);
            printf("Informe o id: ");
            scanf("%d",&id_busca);
            limpa_tela();

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

            pressiona_enter();
            limpa_tela();
        }
        else if(strcmp(opcao,"4")==0){
            limpa_tela();
            Exibir_listacliente(aLista);

            pressiona_enter();
            limpa_tela();
        }
        else if(strcmp(opcao,"5")==0){
            printf("Saindo...");
        }
        else{
            printf("Opcao invalida\n\n");
            pressiona_enter();
            limpa_tela();
        }
    } while (strcmp(opcao,"5")!=0);
    
    fclose(aLista);
    for(index = 0;index < numero_clientes; index++){
        free(cliente[index]);
    }
    free(cliente);
}
