#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*Definição de novo tipo: Cliente*/
typedef struct cliente Cliente;


/**
 * @brief Esta função conta o número de clientes presentes em um arquivo.
 * 
 * A função percorre cada linha do arquivo apontado por 'arquivo' e conta
 * quantas linhas existem, assumindo que cada linha representa um cliente.
 * 
 * @param arquivo Um ponteiro para um arquivo do tipo FILE que contém as informações dos clientes.
 *                O arquivo deve estar aberto para leitura antes de ser passado para a função.
 * 
 * @return O número total de clientes no arquivo.
 *         Retorna 0 se o arquivo estiver vazio ou se ocorrer um erro de leitura.
 */
int Contagem_clientes(FILE * arquivo);


/**
 * @brief Adiciona um novo cliente à lista de clientes e registra suas informações em um arquivo.
 * 
 * Esta função solicita ao usuário o nome, endereço e código do novo cliente,
 * armazena essas informações na lista de clientes e também as registra em um arquivo.
 * 
 * @param numero_clientes O número atual de clientes na lista.
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes.
 *                A função assume que o array já tem espaço suficiente para armazenar o novo cliente.
 */
void add_clientes(Cliente ***cliente, int *numero_clientes);
//void add_clientes(int numero_clientes,Cliente **cliente);


void escrever_arquivo(Cliente **cliente, int numero_clientes);


/**
 * @brief Verifica se o código do cliente já existe na lista de clientes.
 * 
 * Esta função verifica se o código do cliente fornecido já existe na lista de clientes.
 * 
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes.
 * @param id_cliente O código do cliente a ser verificado.
 * @param numero_clientes O número total de clientes na lista.
 * @return Retorna 1 se o código do cliente NÃO existir na lista, caso contrário retorna 0.
 */
int verificar_id(Cliente ** cliente, int id_cliente, int numero_clientes);


/**
 * @brief Preenche uma estrutura Cliente com as informações fornecidas e retorna um ponteiro para ela.
 * 
 * Esta função aloca dinamicamente memória para uma estrutura Cliente, preenche seus campos com as
 * informações fornecidas (nome, endereço e ID do cliente) e retorna um ponteiro para a estrutura alocada.
 * 
 * @param nome Uma string representando o nome do cliente.
 * @param endereco Uma string representando o endereço do cliente.
 * @param id_cliente Um número inteiro representando o ID do cliente.
 * 
 * @return Um ponteiro para uma estrutura Cliente preenchida com as informações fornecidas.
 *         Retorna NULL em caso de falha na alocação dinâmica de memória.
 */
Cliente * preencher_clientes(char *nome,char *endereco,int id_cliente);


/**
 * @brief Organiza a lista de clientes com base no ID do cliente em ordem crescente.
 * 
 * Esta função recebe um array de ponteiros para estruturas Cliente e o número total de clientes na lista.
 * Ela organiza a lista de clientes em ordem crescente com base no ID do cliente, utilizando o algoritmo
 * Bubble Sort.
 * 
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes.
 * @param numero_clientes O número total de clientes na lista.
 * 
 * @note Esta função modifica a lista de clientes diretamente.
 */
void OrganizarID(Cliente ** cliente,int numero_clientes);


/**
 * @brief Organiza a lista de clientes em ordem alfabética do nome.
 * 
 * Esta função recebe um array de ponteiros para estruturas Cliente e o número total de clientes na lista.
 * Ela organiza a lista de clientes em ordem alfabética do nome, utilizando o algoritmo de ordenação Bubble Sort.
 * 
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes.
 * @param numero_clientes O número total de clientes na lista.
 * 
 * @note Esta função modifica a lista de clientes diretamente.
 */
void OrganizarNome(Cliente ** cliente,int numero_clientes);


/**
 * @brief Realiza uma busca exponencial pelo ID do cliente em um vetor ordenado de clientes.
 * 
 * Esta função busca o ID do cliente em um vetor de clientes ordenado pelo ID, utilizando
 * o algoritmo de busca exponencial. Ela recebe um array de ponteiros para estruturas Cliente,
 * o ID do cliente a ser buscado, e o número total de clientes na lista.
 * 
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes ordenada pelo ID.
 * @param id_busca O ID do cliente a ser buscado.
 * @param numero_clientes O número total de clientes na lista.
 * @return O índice do cliente na lista se encontrado, caso contrário, retorna -1.
 */

int BuscaExponencialID(Cliente ** cliente,int id_busca,int numero_clientes);


/**
 * @brief Realiza uma busca exponencial pelo nome do cliente em um vetor ordenado de clientes.
 * 
 * Esta função busca o nome do cliente em um vetor de clientes ordenado alfabeticamente pelo nome,
 * utilizando o algoritmo de busca exponencial. Ela recebe um array de ponteiros para estruturas Cliente,
 * o nome do cliente a ser buscado, e o número total de clientes na lista.
 * 
 * @param cliente Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes ordenada pelo nome.
 * @param nome_busca O nome do cliente a ser buscado.
 * @param numero_clientes O número total de clientes na lista.
 * @return O índice do cliente na lista se encontrado, caso contrário, retorna -1.
 */
int BuscaExponencialNome(Cliente ** cliente,char *nome_busca,char numero_clientes);


/**
 * @brief Realiza uma busca binária pelo ID do cliente em um vetor ordenado de clientes.
 * 
 * Esta função busca o ID do cliente em um vetor de clientes ordenado numericamente pelo ID,
 * utilizando o algoritmo de busca binária. Ela recebe um array de ponteiros para estruturas Cliente,
 * o índice inicial e final do intervalo de busca, e o ID do cliente a ser buscado.
 * 
 * @param clientes Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes ordenada pelo ID.
 * @param begin O índice inicial do intervalo de busca.
 * @param end O índice final do intervalo de busca.
 * @param id_busca O ID do cliente a ser buscado.
 * @return O índice do cliente na lista se encontrado, caso contrário, retorna -1.
 */
int BuscaBinariaId(Cliente **clientes, int begin, int end, int id);


/**
 * @brief Realiza uma busca binária pelo nome do cliente em um vetor ordenado de clientes.
 * 
 * Esta função busca o nome do cliente em um vetor de clientes ordenado alfabeticamente pelo nome,
 * utilizando o algoritmo de busca binária. Ela recebe um array de ponteiros para estruturas Cliente,
 * o índice inicial e final do intervalo de busca, e o nome do cliente a ser buscado.
 * 
 * @param clientes Um ponteiro para um array de ponteiros para estruturas Cliente, representando a lista de clientes ordenada pelo nome.
 * @param begin O índice inicial do intervalo de busca.
 * @param end O índice final do intervalo de busca.
 * @param nome_busca O nome do cliente a ser buscado.
 * @return O índice do cliente na lista se encontrado, caso contrário, retorna -1.
 */
int BuscaBinariaNome(Cliente **clientes, int begin, int end, char *nome);


/**
 * @brief Capitaliza os nomes contidos em uma string.
 * 
 * Esta função percorre uma string e capitaliza os nomes contidos nela, ou seja, transforma
 * a primeira letra de cada palavra em maiúscula e as demais letras em minúscula. Para isso,
 * ela recebe uma string como entrada e modifica diretamente essa string.
 * 
 * @param str A string contendo os nomes a serem capitalizados.
 */
void capitalizeNames(char *str);


/**
 * @brief Exibe o conteúdo de um arquivo contendo informações de clientes.
 * 
 * Esta função lê o conteúdo de um arquivo contendo informações de clientes,
 * cada linha do arquivo deve conter o nome, endereço e ID do cliente separados por tabulação (\t).
 * Em seguida, exibe essas informações no terminal.
 * 
 * @param arquivo Um ponteiro para o arquivo contendo as informações dos clientes.
 */
void Exibir_listacliente(FILE * arquivo);


/**
 * @brief Exibe um menu de opções para interação com o sistema de gerenciamento de clientes.
 * 
 * Esta função imprime um menu na saída padrão, apresentando as opções disponíveis
 * para interação com o sistema de gerenciamento de clientes.
 * 
 * As opções incluem:
 * 1. Cadastrar novo cliente
 * 2. Buscar cliente por nome
 * 3. Buscar cliente por ID
 * 4. Mostrar lista de clientes
 * 5. Sair
 * 
 * @note Esta função não recebe parâmetros nem retorna valores.
 */
void menu();