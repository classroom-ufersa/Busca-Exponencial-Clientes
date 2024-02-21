#include"cliente.c"



int main(void){
    int index=0,id_cliente,numero_clientes;
    char nome[80],endereco[80],linha[100],opcao,opcao2;

    FILE * aLista=fopen("Lista clientes.txt","r");
    numero_clientes=Contagem_clientes(aLista);
    Cliente ** cliente=(Cliente**)malloc(numero_clientes*sizeof(Cliente*));
    while(fgets(linha,100,aLista) != NULL){
        sscanf(linha,"%[^\t]%[^\t]%d\n",nome,endereco,id_cliente);
        cliente[index] = preencher_clientes(nome,endereco,id_cliente);
        index++;
    }
    do{
        printf("MENU\n");
        printf("1-Cadastrar novo cliente\n2-Buscar por nome\n3-Buscar por código\n4-Mostrar lista de clientes\n5-Sair");
        scanf("%c",&opcao);
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
            /* code */
            break;
        case '3':
            

            
            break;
        case '4':
            /* code */
            break;
        case '5':
            /* code */
            break;
        default:
            printf("Opção inválida");
            break;
        }
    } while (opcao!=5);
    
}