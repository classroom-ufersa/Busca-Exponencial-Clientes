/*TAD: Cliente*/
#include "cliente.h"
struct cliente
{
    char nome[81];
    char endereco[81];
    int id_cliente;
};

Cliente *preencher_clientes(char *nome, char *endereco, int id_cliente){
    Cliente *temp = (Cliente *)malloc(sizeof(Cliente)); 
    if (temp == NULL) { 
        printf("Erro na alocacao, memoria insuficiente!");
        exit(1);
    }

    int nomet = (int)strlen(nome);
    nome[nomet] = '\0';

    int index;
    for(index = 0;index <= nomet;index++) { 
        nome[index]=toupper(nome[index]);
    }

    strcpy(temp->nome, nome);
    strcpy(temp->endereco, endereco);
    temp->id_cliente = id_cliente;
    return temp;
}

int Contagem_clientes(FILE *arquivo){
    int numero_clientes = 0;
    char linha[100];

    while (fgets(linha, 100, arquivo) != NULL) { 
        numero_clientes++;
    }
    return numero_clientes;
}

void add_clientes(int numero_clientes, Cliente **cliente){
    char *nome =  (char*) malloc(81 * sizeof(char));
    char *endereco =  (char*) malloc(81 * sizeof(char));
    if (nome == NULL || endereco == NULL){
        printf("Erro de alocacao, memoria insuficiente");
        exit(1);
    }
    int index;
    printf("Informe nome do novo cliente: ");
    scanf(" %[^\n]", nome);
    limpa_tela();

    int nomet= (int)strlen(nome);
    nome[nomet] = '\0';
    
    verificar_nome(nome);

    while(verificar_nome(nome)==1){
        printf("Nome invalido\n\n");
        printf("Informe nome do novo cliente: ");
        scanf(" %[^\n]", nome);
        verificar_nome(nome);
        limpa_tela();
    }
    
    printf("Informe endereco do novo cliente: ");
    scanf(" %[^\n]", endereco);

    int enderecot = (int)strlen(endereco);
    endereco[enderecot] = '\0';

    for(index=0;index<nomet;index++){
        nome[index]=toupper(nome[index]);
    }


    cliente[numero_clientes] = preencher_clientes(nome,endereco,numero_clientes+101);

    capitalizeNames(nome);
    capitalizeNames(endereco);

    FILE *arquivo = fopen("listaclientes.txt", "a");
    fprintf(arquivo, "\n%s\t%s\t%d", nome, endereco, numero_clientes+101);

    fclose(arquivo);
}

int verificar_nome(char * nome){
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i]!=' '){
            return 1;
        }
    }
    return 0;
}

void OrganizarID(Cliente **cliente, int numero_clientes){
    int count1, count2;
    Cliente *a = (Cliente *)malloc(sizeof(Cliente));
    if (a == NULL){
        printf("Erro de alocacao, memoria insuficiente");
        exit(1);
    }
    a = cliente[0];
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++){
            if (cliente[count2]->id_cliente > cliente[count2 + 1]->id_cliente){
                a = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = a;
            }
        }
    }
}

void OrganizarNome(Cliente **cliente, int numero_clientes){
    int count1, count2;
    Cliente *a = (Cliente *)malloc(sizeof(Cliente));
    if (a == NULL){
        printf("Erro de alocacao, memoria insuficiente");
    }

    a = cliente[0];
    for (count1 = 0; count1 < numero_clientes; count1++){
        for (count2 = 0; count2 < numero_clientes - 1; count2++){
            if (strcmp(cliente[count2]->nome, cliente[count2 + 1]->nome) > 0){
                a = cliente[count2];
                cliente[count2] = cliente[count2 + 1];
                cliente[count2 + 1] = a;
            }
        }
    }
}

int BuscaExponencialID(Cliente **cliente, int id_busca, int numero_clientes){
    if (id_busca == cliente[0]->id_cliente){
        return 0;
    }
    int end = 1;
    while (end < numero_clientes && cliente[end]->id_cliente <= id_busca){
        end *= 2;
    }
    return BuscaBinariaId(cliente,end/2,fmin(end,numero_clientes-1),id_busca);
}

int BuscaExponencialNome(Cliente **cliente, char nome_busca[80], char numero_clientes){
    int index; //1 vez: c1
    for(index=0;index<81;index++){
        nome_busca[index]=toupper(nome_busca[index]); //n - 1 vezes: (n - 1) * c2
    }
    if ((strcmp(cliente[0]->nome, nome_busca)) == 0){
        return 0; // 1 vez: c3
    }
    int end=1; // 1 vez: c4
    while(end<numero_clientes && (strcmp(cliente[end]->nome,nome_busca))<=0){
        end*=2; //n/2 vezes = (n/2) * c5
    }
    return BuscaBinariaNome(cliente,end/2,fmin(end,numero_clientes-1),nome_busca); //log n vezes = log n * c6
}

int BuscaBinariaNome(Cliente **clientes, int begin, int end, char nome_busca[81]){
    if (end >= begin){
        int mid = begin + ((end - begin) / 2);
        if (strcmp(clientes[mid]->nome, nome_busca) == 0){
            return mid;
        }
        if (strcmp(clientes[mid]->nome, nome_busca) > 0){
            return BuscaBinariaNome(clientes,begin,mid-1,nome_busca);
        }
        return BuscaBinariaNome(clientes,mid+1,end,nome_busca); 
    }
    return -1;
}

int BuscaBinariaId(Cliente **clientes, int begin, int end, int id_busca){
    if (end >= begin){
        int mid = begin + (end-begin)/2;
        if (clientes[mid]->id_cliente == id_busca){
            return mid;
        }
        if (clientes[mid]->id_cliente > id_busca){
            return BuscaBinariaId(clientes,begin,mid-1,id_busca);
        }
        return BuscaBinariaId(clientes,mid+1,end,id_busca); 
    }
    return -1;
}

void capitalizeNames(char *str) {
    int capitalizeNext = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            if (capitalizeNext) {
                str[i] = toupper(str[i]);
                capitalizeNext = 0; 
            } else {
                str[i] = tolower(str[i]);
            }
        } else {
            capitalizeNext = 1;
        }
    }
}

void Exibir_listacliente(FILE *arquivo){
    char linha[100], nome[81], endereco[81];
    int id_cliente;
    rewind(arquivo);
    while (fgets(linha, 100, arquivo) != NULL){
        sscanf(linha, "%[^\t]\t%[^\t]\t%d\n", nome, endereco, &id_cliente);
        printf("%s\t", nome);
        printf("%s\t", endereco);
        printf("%d\n", id_cliente);
    }
}

void menu(){
    printf("========= Bem-Vindo =========\n\n");
    printf("1- Cadastrar novo cliente\n");
    printf("2- Buscar cliente por nome\n");
    printf("3- Buscar cliente por Id\n");
    printf("4- Mostrar lista de clientes\n");
    printf("5- Sair\n");
    printf("-----------------------------\n");
}

void pressiona_enter(){
    printf("\nPressione ENTER para continuar.");
    while (getchar() != '\n');
    getchar();
}

void limpa_tela(){
    system("cls");
}