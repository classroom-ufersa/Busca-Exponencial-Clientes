#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include"cliente.c"


int main(void){
    int index,id_cliente,busca_cod_cliente,numero_clientes;
    char nome[80],busca_nome,endereco[80],ler[80];

    FILE * aLista=fopen("Lista clientes.txt","rt");
    numero_clientes=Contagem_clientes(aLista);
    Cliente * cliente=(Cliente*)malloc(numero_clientes*sizeof(Cliente*));
    for(index=0;index<numero_clientes;index++){
        fscanf(aLista,"%20[^\t]\t%20[^\t]\t%d",nome,endereco,&id_cliente);
        cliente[index]=preencher_clientes(nome,endereco,id_cliente);
    }

    char opcao,opcao2;
    do{
        printf("MENU\n");
        printf("1-Cadastrar novo cliente\n2-Buscar por nome\n3-Buscar por código\n4-Mostrar lista de clientes\n5-Sair");
        scanf("%c",&opcao);
        switch (opcao){
        case '1':
            do{
            add_clientes(numero_clientes,cliente);
            numero_clientes++;
            printf("Adicionar novo cliente?\n(S) ou (N)\n");
            scanf("%c",&opcao2);
            toupper(opcao2); //transforma o caracter em maiúsculo
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