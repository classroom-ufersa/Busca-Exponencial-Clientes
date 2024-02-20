#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include"cliente.c"


int main(void){
    int index,cod_cliente,busca_cod_cliente,numero_clientes;
    char nome[80],busca_nome,endereco[80];

    FILE * aLista=fopen("Lista clientes.txt","rt");
    numero_clientes=Contagem_clientes(aLista);
    Cliente * cliente=(Cliente*)malloc(numero_clientes*sizeof(Cliente*));
    preencher_clientes(aLista,cliente);

    char opcao, opcao2;
    do{
        printf("MENU\n");
        printf("1-Cadastrar novo cliente\n2-Buscar por nome\n3-Buscar por código\n4-Mostrar lista de clientes\n5-Sair");
        scanf("%c",&opcao);
        switch (opcao){
        case '1':
            do{
            add_clientes(numero_clientes,cliente);
            numero_clientes+1;
            printf("Adicionar novo cliente?\n(S) ou (N)\n");
            scanf("%c",&opcao2);
            opcao2 = toupper(opcao2); //transforma o caracter em maiúsculo
            } while (opcao2=='S');
            break;
        case '2':
            /* code */
            break;
        case '3':
            /* code */
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