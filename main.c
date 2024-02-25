#include "cliente.c"

int main(void){
    int index=0, id_cliente, numero_clientes, id_busca, posicao;
    char nome[81], endereco[81], linha[100], opcao, opcao2, nome_busca[81];
    FILE * aLista = fopen("listaclientes.txt","r"); // Abre arquivo e escreve
    numero_clientes = Contagem_clientes(aLista); // Conta o número de clientes
    Cliente ** cliente = (Cliente**)malloc(numero_clientes*sizeof(Cliente*)); // Realoca a memória dinamicamente
    if(cliente == NULL){ // Se o valor de cliente for Nulo mostra erro na memória
        printf("Erro de memoria\n");
        exit(1);
    }
    rewind(aLista); // Volta a leitura pro começo do .txt
    if(cliente == NULL){
        printf("erro!\n");
    }
    while(fgets(linha, 100, aLista) != NULL){ // Lê o conteúdo do txt e armazena os dados coletados para preencer a lisa
        sscanf(linha, "%[^\t]\t%[^\t]\t%d\n", nome, endereco, &id_cliente);
        cliente[index] = preencher_clientes(nome, endereco, id_cliente);
        index++;
    }

    do{
        menu();
        scanf("%s", &opcao);
        switch (opcao){
        case '1': // Adiciona novo cliente
            numero_clientes = Contagem_clientes(aLista);
            do{
            cliente = realloc(cliente,(numero_clientes+1)*sizeof(Cliente*));
            add_clientes(numero_clientes,cliente);
            numero_clientes++;
            printf("Deseja adicionar mais um novo cliente?\n(S) ou (N)\n");
            scanf(" %[^\n]", &opcao2);
            opcao2 = toupper(opcao2); //transforma o caracter em maiúsculo
            while(opcao2 != 'S' && opcao2 != 'N') {
                printf("opcao invalida\nDigite (S) ou (N)\n");
                scanf(" %[^\n]", &opcao2);
                opcao2 = toupper(opcao2);
            }
            } while (opcao2=='S');
            break;
        case '2': // Busca por nome
            OrganizarNome(cliente,numero_clientes);
            printf("Informe o nome: \n");
            scanf(" %[^\n]", nome_busca);
            posicao = BuscaExponencialNome(cliente, nome_busca, numero_clientes);
            if(posicao < 0){
                printf("Cliente inexistente\n");
            }
            else{
                strcpy(nome, cliente[numero_clientes]->nome);
                strcpy(endereco, cliente[numero_clientes]->endereco);
                id_cliente = cliente[posicao]->id_cliente;
                capitalizeNames(nome);
                capitalizeNames(endereco);
                printf("Nome: %s\n", nome);
                printf("Endereco: %s\n", endereco);
                printf("Id: %d\n", id_cliente);
            }
            break;
        case '3': // Busca por ID
            OrganizarID(cliente, numero_clientes);
            printf("Informe o id: \n");
            scanf("%d", &id_busca);
            posicao=BuscaExponencialID(cliente, id_busca, numero_clientes);
            if(posicao < 0){ // Se não existe mostra que o cliente é inexistente
                printf("Cliente inexistente\n");
            }
            else{ // Se o cliente existe mostra as informações
                strcpy(nome, cliente[numero_clientes]->nome);
                strcpy(endereco, cliente[numero_clientes]->endereco);
                id_cliente = cliente[posicao]->id_cliente;
                capitalizeNames(nome);
                capitalizeNames(endereco);
                printf("Nome: %s\n", nome);
                printf("Endereco: %s\n", endereco);
                printf("Id: %d\n", id_cliente);
            }
            break;
        case '4': // Mostra a lista completa
            Exibir_listacliente(aLista);
            break;
        case '5': // Encerra a execução
            printf("Obrigado pela preferencia");
            break;
        default:
            printf("Opcao invalida\n\n");
            break;
        }
    } while (opcao!='5');
    
    fclose(aLista); // Fecha o .txt
    for(index = 0;index < numero_clientes; index++){
        free(cliente[index]);
    }
    free(cliente);
}