/*TAD: Cliente*/
#include "cliente.h"
struct cliente{
    char nome[81];
    char endereco[81];
    int id_cliente;
};

Cliente *preencher_clientes(char *nome, char *endereco, int id_cliente){
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente)); //Alocação dinâmica das linhas da matriz cliente
    if (temp == NULL) { //Verificação da alocação dinâmica
        printf("Erro na alocacao, memoria insuficiente!");
        exit(1);
    }

    int index;
    //Tranformação de todas as letras da váriavel em maiúsculas
    for(index = 0;index < 81;index++) { 
        nome[index]=toupper(nome[index]);
    }

    //função usada para copiar os valores entre duas strings
    strcpy(temp->nome, nome);
    strcpy(temp->endereco, endereco);
    temp->id_cliente = id_cliente;
    return temp;
}

int Contagem_clientes(FILE *arquivo){
    int numero_clientes = 0;
    char linha[100];

    //Navega cada linha do arquivo
    while (fgets(linha, 100, arquivo) != NULL) { 
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes, Cliente **cliente){
    char nome[81],endereco[81];
    int index;

    printf("Informe nome do novo cliente\n");
    scanf(" %[^\n]", nome);

    printf("Informe endeco do novo cliente\n");
    scanf(" %[^\n]", endereco);

    //Tranformação de todas as letras da váriavel em maiúsculas
    for(index = 0;index < 81;index++) { 
        nome[index] = toupper(nome[index]);
        endereco[index] = toupper(endereco[index]);
    }

    //função usada para copiar os valores entre duas strings
    strcpy(cliente[numero_clientes]->nome, nome); 
    strcpy(cliente[numero_clientes]->endereco, endereco);
    
    printf("Informe o codigo do novo cliente\n");
    scanf("%d", &cliente[numero_clientes]->id_cliente);

    FILE *arquivo = fopen("listaclientes.txt", "a");
    //Cadastra as informações do novo cliente no arquivo
    fprintf(arquivo, "\n%s\t%s\t%d", cliente[numero_clientes]->nome, cliente[numero_clientes]->endereco, cliente[numero_clientes]->id_cliente);
    fclose(arquivo);
}

int verificar_id(Cliente ** cliente, int id_cliente, int numero_clientes){
    int count;
    for(count = 0;count < numero_clientes;count++){
        if(cliente[count]->id_cliente != id_cliente){
            return 1;
        }
    }
    return 0;
}

void OrganizarID(Cliente **cliente, int numero_clientes){
    int count1, count2;
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente));
    temp = cliente[0];
    
    // Algoritmo de ordenação Bubble Sort
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++) {
            // Verifica se o ID do cliente atual é maior que o ID do próximo cliente na lista
            if (cliente[count2]->id_cliente > cliente[count2 + 1]->id_cliente){
                // Troca os ponteiros para os clientes, organizando em ordem crescente de ID
                temp = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = temp;
            }
        }
    }
    free(temp);
}

void OrganizarNome(Cliente **cliente, int numero_clientes){ 
    int count1, count2;
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente));
    temp = cliente[0];
    
    // Algoritmo de ordenação Bubble Sort
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++) { 
            // Compara os nomes dos clientes e verifica se o nome atual vem depois no alfabeto
            if (strcmp(cliente[count2]->nome, cliente[count2 + 1]->nome) > 0){
                // Troca os ponteiros para os clientes, organizando em ordem alfabética do nome
                temp = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = temp;
            }
        }
    }
    free(temp);
}

int BuscaExponencialID(Cliente **cliente, int id_busca, int numero_clientes){
    //Verifica se o id do cliente buscado está localizado na posição 0 do vetor cliente
    if (id_busca == cliente[0]->id_cliente){
        return 0;
    }
    int index = 1;
    //Verifica se o id do cliente desejado é menor que o do cliente na posição index
    while (index < numero_clientes && cliente[index]->id_cliente <= id_busca){
        index *= 2;
    }
    return BuscaBinariaId(cliente, index/2, fmin(index,numero_clientes-1), id_busca);
}

int BuscaExponencialNome(Cliente **cliente, char *nome_busca, char numero_clientes){
    int index;
    // Transforma todas as letras do nome buscado em maiúsculas
    for(index = 0; index < 81; index++) {
        nome_busca[index] = toupper(nome_busca[index]);
    }
    // Verifica se o nome do cliente buscado está localizado na posição 0 do vetor cliente
    if ((strcmp(cliente[0]->nome, nome_busca)) == 0){
        return 0;
    }
    int i = 1;
    // Verifica se o código ASCII do nome do cliente desejado é menor que o código ASCII do cliente na posição n
    while(i < numero_clientes && (strcmp(cliente[i]->nome, nome_busca)) <= 0){
        i *= 2;
    }
    return BuscaBinariaNome(cliente, i/2, fmin(i, numero_clientes-1), nome_busca);
}

int BuscaBinariaNome(Cliente **clientes, int begin, int end, char *nome_busca){
    if (end >= begin){
        //Inicializando 'mid' como a posição central entre 'begin' e 'end'
        int mid = begin + ((end - begin) / 2);
        //Verifica se o nome do cliente buscado está localizado na posição 'mid' do vetor cliente
        if (strcmp(clientes[mid]->nome, nome_busca) == 0){
            return mid;
        }
        // Verifica se o nome do cliente buscado está localizado em uma posição menor do que 'mid' no vetor cliente
        if (strcmp(clientes[mid]->nome, nome_busca) > 0){
            //Chamada da função com os novos intervalos obtidos apartir da verificação
            return BuscaBinariaNome(clientes, begin,mid-1, nome_busca);
        }
        return BuscaBinariaNome(clientes, mid + 1, end, nome_busca); 
    }
    return -1;
}

int BuscaBinariaId(Cliente **clientes, int begin, int end, int id_busca){
    if (end >= begin){
        //Inicializando 'mid' como a posição central entre 'begin' e 'end'
        int mid = begin + (end-begin)/2;

        //Verifica se o id do cliente buscado está localizado na posição 'mid' do vetor cliente
        if (clientes[mid]->id_cliente == id_busca){
            return mid;
        }
        //Verifica se o id do cliente buscado está localizado em uma posição menor do que 'mid' no vetor cliente
        if (clientes[mid]->id_cliente > id_busca){
            return BuscaBinariaId(clientes, begin, mid-1, id_busca);
        }
        return BuscaBinariaId(clientes, mid + 1, end, id_busca); 
    }
    return -1;
}

void capitalizeNames(char *str){
    int capitalizeNext = 1; //Primeiro caractere começa maiúscula
    for (int index = 0; str[index] != '\0'; index++) { //Navega sobre cada caractere na string
        if (isalpha(str[index])){ //Verifica se o caractere atual é uma letra      
            if (capitalizeNext){ //Transforma a letra em maiúscula se necessário
                str[index] = toupper(str[index]);
                capitalizeNext = 0; //Desativa a transformação para o próximo caractere
            } else{ //Caso não trasforme em maiúscula, trasforma em minúscula
                str[index] = tolower(str[index]);
            }
        } else{ //Se o caractere não for uma letra, ativa a transformação para o próximo
            capitalizeNext = 1;
        }
    }
}

void Exibir_listacliente(FILE *arquivo){
    char linha[100], nome[81], endereco[81];
    int id_cliente;

    rewind(arquivo); //Reposiciona o ponteiro do arquivo para o início

    while (fgets(linha, 100, arquivo) != NULL){ //Navega por todas as linhas do arquivo
        sscanf(linha, "%[^\t]\t%[^\t]\t%d\n", nome, endereco, &id_cliente); //Lê cada linha do arquivo
        printf("%s\t", nome);
        printf("%s\t", endereco);
        printf("%d\n", id_cliente);
    }
}

void menu(){
    printf("========= Bem-vindo =========\n\n");
    printf("1- Cadastrar novo cliente\n");
    printf("2- Buscar cliente por nome\n");
    printf("3- Buscar cliente por Id\n");
    printf("4- Mostrar lista de clientes\n");
    printf("5- Sair\n");
    printf("-----------------------------\n");
}