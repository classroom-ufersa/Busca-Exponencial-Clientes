/*TAD: Cliente*/
#include "cliente.h"
struct cliente{
    char nome[81];
    char endereco[81];
    int id_cliente;
};

Cliente *preencher_clientes(char *nome, char *endereco, int id_cliente){//Função para preencher cada linha da matriz cliente
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente));//Alocação dinâmica das linhas da matriz cliente
    if (temp == NULL){//Verificação da alocação dinâmica
        printf("Erro na alocacao, memoria insuficiente!");
        exit(1);
    }
    int index;
    for(index = 0;index < 81;index++){//Tranformação de todas as letras da váriavel em maiúsculas
        nome[index]=toupper(nome[index]);
    }
    strcpy(temp->nome, nome);//Variável 'temp->nome' recebendo 'nome'
    strcpy(temp->endereco, endereco);//Variável 'temp->endereco' recebendo 'endereco'
    temp->id_cliente = id_cliente;
    return temp;
}

int Contagem_clientes(FILE *arquivo){//Função que realiza a contagem de clientes cadastrados no arquivo
    int numero_clientes = 0;
    char linha[100];
    while (fgets(linha, 100, arquivo) != NULL){//Navega cada linha do arquivo
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes, Cliente **cliente){//Função para cadastrar novo cliente 
    char nome[81],endereco[81];
    int index;
    printf("Informe nome do novo cliente\n");
    scanf(" %[^\n]", nome);
    printf("Informe endeço do novo cliente\n");
    scanf(" %[^\n]", endereco);
    for(index = 0;index < 81;index++){//Tranformação de todas as letras da váriavel em maiúsculas
        nome[index] = toupper(nome[index]);
        endereco[index] = toupper(endereco[index]);
    }
    strcpy(cliente[numero_clientes]->nome, nome);//Variável 'cliente[numero_clientes]->nome' recebendo 'nome'
    strcpy(cliente[numero_clientes]->endereco, endereco);//Variável 'cliente[numero_clientes]->endereco' recebendo 'endereco'
    printf("Informe o codigo do novo cliente\n");
    scanf("%d", &cliente[numero_clientes]->id_cliente);
    FILE *arquivo = fopen("listaclientes.txt", "a");
    fprintf(arquivo, "\n%s\t%s\t%d", cliente[numero_clientes]->nome, cliente[numero_clientes]->endereco, cliente[numero_clientes]->id_cliente);//Cadastra as informações do novo cliente no arquivo
    fclose(arquivo);
}

int verificar_id(Cliente ** cliente, int id_cliente, int numero_clientes){//Verifica se existe algum cliente já cadastrado com o id informado
    int count;
    for(count = 0;count < numero_clientes;count++){
        if(cliente[count]->id_cliente != id_cliente){
            return 1;
        }
    }
    return 0;
}

void OrganizarID(Cliente **cliente, int numero_clientes){//Organiza a matriz cliente de acordo com o id dos clientes em ordem crescente
    int count1, count2;
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente));
    temp = cliente[0];
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++){//Verificação n²-n vezes, que seria o numero nescessario para o pior caso
            if (cliente[count2]->id_cliente > cliente[count2 + 1]->id_cliente){//Caso o id do cliente n seja maior que o n+1, ambos trocam de lugar
                temp = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = temp;
            }
        }
    }
    free(temp);
}

void OrganizarNome(Cliente **cliente, int numero_clientes){//Organiza a matriz cliente de acordo com o código ASCII dos nomes 
    int count1, count2;
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente));
    temp = cliente[0];
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++){//Verificação n²-n vezes, que seria o numero nescessario para o pior caso
            if (strcmp(cliente[count2]->nome, cliente[count2 + 1]->nome) > 0){//compara as duas strings e devolve um valor inteiro que lhe diz qual das strings vem antes no código ASCII
                temp = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = temp;
            }
        }
    }
    free(temp);
}

int BuscaExponencialID(Cliente **cliente, int id_busca, int numero_clientes){//Realiza uma busca exponencial que localiza o intervalo das posições dos clientes, em que o id do cliente desejado esta localizado
    if (id_busca == cliente[0]->id_cliente){//Verifica se o id do cliente buscado está localizado na posição 0 do vetor cliente
        return 0;
    }
    int i = 1;
    while (i < numero_clientes && cliente[i]->id_cliente <= id_busca){//Verifica se o id do cliente desejado é menor que o do cliente na posição n, caso contrário multiplica n por 2 e realiza a mesma verificação
        i *= 2;
    }
    return BuscaBinariaId(cliente, i/2, fmin(i,numero_clientes-1), id_busca);//Chamada da função para realizar a busca binária no intervalo descoberto pela função da busca exponencial
}

int BuscaExponencialNome(Cliente **cliente, char *nome_busca, char numero_clientes){//Realiza uma busca exponencial que localiza o intervalo das posições dos clientes, em que o código ASCII do nome do cliente desejado esta localizado
    int index;
    for(index = 0; index < 81; index++){//Tranformação de todas as letras da váriavel em maiúsculas
        nome_busca[index] = toupper(nome_busca[index]);
    }
    if ((strcmp(cliente[0]->nome, nome_busca)) == 0){//Verifica se o nome do cliente buscado está localizado na posição 0 do vetor cliente
        return 0;
    }
    int i = 1;
    while(i < numero_clientes && (strcmp(cliente[i]->nome, nome_busca)) <= 0){//Verifica se o código ASCII do nome do cliente desejado é menor que o código ASCII do cliente na posição n, caso contrário multiplica n por 2 e realiza a mesma verificação
        i *= 2;
    }
    return BuscaBinariaNome(cliente, i/2, fmin(i, numero_clientes-1), nome_busca);//Chamada da função para realizar a busca binária no intervalo descoberto pela função da busca exponencial
}

int BuscaBinariaNome(Cliente **clientes, int begin, int end, char *nome_busca){//Realiza uma busca binária no intervalo entre as variáveis 'begin' e 'end'
    if (end >= begin){
        int mid = begin + ((end - begin) / 2);//Inicializando 'mid' como a posição central entre 'begin' e 'end'
        if (strcmp(clientes[mid]->nome, nome_busca) == 0){//Verifica se o nome do cliente buscado está localizado na posição 'mid' do vetor cliente
            return mid;
        }
        if (strcmp(clientes[mid]->nome, nome_busca) > 0){//Verifica se o nome do cliente buscado está localizado em uma posição menor do que 'mid' no vetor cliente
            return BuscaBinariaNome(clientes, begin,mid-1, nome_busca);//Chamada da função com os novos intervalos obtidos apartir da verificação
        }
        return BuscaBinariaNome(clientes, mid + 1, end, nome_busca); 
    }
    return -1;
}

int BuscaBinariaId(Cliente **clientes, int begin, int end, int id_busca){//Realiza uma busca binária no intervalo entre as variáveis 'begin' e 'end'
    if (end >= begin){
        int mid = begin + (end-begin)/2;//Inicializando 'mid' como a posição central entre 'begin' e 'end'
        if (clientes[mid]->id_cliente == id_busca){//Verifica se o id do cliente buscado está localizado na posição 'mid' do vetor cliente
            return mid;
        }
        if (clientes[mid]->id_cliente > id_busca){//Verifica se o id do cliente buscado está localizado em uma posição menor do que 'mid' no vetor cliente
            return BuscaBinariaId(clientes, begin, mid-1, id_busca);//Chamada da função com os novos intervalos obtidos apartir da verificação
        }
        return BuscaBinariaId(clientes, mid + 1, end, id_busca); 
    }
    return -1;
}

void capitalizeNames(char *str){//Indica se a próxima letra deve ser transformada em maiúscula  
    int capitalizeNext = 1;//Primeiro caractere começa maiúscula
    for (int index = 0; str[index] != '\0'; index++) {//Navega sobre cada caractere na string
        if (isalpha(str[index])){//Verifica se o caractere atual é uma letra      
            if (capitalizeNext){//Transforma a letra em maiúscula se necessário
                str[index] = toupper(str[index]);
                capitalizeNext = 0; //Desativa a transformação para o próximo caractere
            } else{//Caso não trasforme em maiúscula, trasforma em minúscula
                str[index] = tolower(str[index]);
            }
        } else{//Se o caractere não for uma letra, ativa a transformação para o próximo
            capitalizeNext = 1;
        }
    }
}

void Exibir_listacliente(FILE *arquivo){//Exibe todos os clientes cadastrados no arquivo
    char linha[100], nome[81], endereco[81];
    int id_cliente;
    rewind(arquivo);
    while (fgets(linha, 100, arquivo) != NULL){//Navega por todas as linhas do arquivo
        sscanf(linha, "%[^\t]\t%[^\t]\t%d\n", nome, endereco, &id_cliente);//Lê cada linha do arquivo
        printf("%s\t", nome);
        printf("%s\t", endereco);
        printf("%d\n", id_cliente);
    }
}

void menu(){//Tela do menu principal
    printf("*************************\n");
    printf("******* BEM-VINDO *******\n");
    printf("*************************\n\n");

    printf("1- Cadastrar novo cliente\n");
    printf("2- Buscar cliente por nome\n");
    printf("3- Buscar cliente por Id\n");
    printf("4- Mostrar lista de clientes\n");
    printf("5- Sair\n");
}