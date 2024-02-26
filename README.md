# Busca-Exponencial-Clientes
Este é um simples sistema de cadastro de clientes em linguagem C. Ele permite a adição, busca e exibição de clientes, além de salvar os dados em um arquivo texto.

# COMPONENTES:
- Pedro Henrique Andrade da Conceição;
- Pedro Lucas de Souza Ferreira;
- Nattan Ferreira Lopes;
- Samuel de Almeida Saturno.

## Funcionalidades

1. **Cadastrar novo cliente:** Solicita ao usuário o nome, endereço e código do novo cliente, armazena essas informações na lista de clientes e também as registra no arquivo.

2. **Buscar cliente por nome:** Realiza uma busca por nome de cliente, exibindo suas informações caso encontrado.

3. **Buscar cliente por Id:** Realiza uma busca por código de cliente (ID), exibindo suas informações caso encontrado.

4. **Mostrar lista de clientes:** Exibe a lista completa de clientes cadastrados.

## Funcionamento

- O código implementa a busca exponencial para encontrar clientes com base no nome ou código. A busca exponencial é uma técnica de busca em que o elemento desejado é comparado com elementos em posições que crescem exponencialmente até encontrar o elemento ou ultrapassar o limite.

- As opções do menu permitem ao usuário interagir com o sistema, realizando operações como cadastrar novos clientes, buscar por nome ou código, e exibir a lista de clientes.

- O programa utiliza um arquivo de texto chamado "listaclientes.txt" para armazenar os dados dos clientes.
