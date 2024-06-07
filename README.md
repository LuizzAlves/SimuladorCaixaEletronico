## Simulador de Caixa Eletrônico

###

Este é um programa em C que simula operações comuns de um caixa eletrônico. Ele foi desenvolvido com o objetivo de permitir a prática de conceitos de programação em C, como manipulação de arquivos, funções e estruturas de dados.

## Funcionalidades

- Criação de contas
- Acesso a contas existentes
- Transferencia de valores entre contas
- Saque
- Deposito
- Persistência de Dados em Arquivo de Texto

## Requisitos

[Liste os requisitos necessários para rodar seu programa. Por exemplo:]

- GCC (GNU Compiler Collection)
- Sistema Operacional: Linux, macOS ou Windows

### Como Clonar o Projeto:

bash
git clone git@github.com:LuizzAlves/SimuladorCaixaEletronico.git


### Como Compilar e Executar (Linux and macOS):

bash
gcc -c main.c -o main.o
gcc -c caixa_eletronico.c -o caixa_eletronico.o
gcc main.o caixa_eletronico.o -o caixa_eletronico


### How to run Linux and macOS:

bash
./caixa_eletronico


### Como Compilar e Executar (Windows):

bash
gcc -c main.c -o main.o
gcc -c caixa_eletronico.c -o caixa_eletronico.o
gcc main.o caixa_eletronico.o -o caixa_eletronico.exe


### How to run Windows:


caixa_eletronico.exe


## Estrutura do Projeto

- main.c: Contém a função principal e a lógica de controle do programa.
- caixa_eletronico.c: Implementa as funções específicas do caixa eletrônico, como saque, depósito e consulta de saldo.
- caixa_eletronico.h: Define as funções e estruturas de dados usadas no caixa_eletronico.c.

## Contribuição

Se você quiser contribuir para este projeto, siga os passos abaixo:

1. Faça um fork do projeto
2. Crie uma branch para sua feature (git checkout -b feature/nova-feature)
3. Commit suas mudanças (git commit -m 'Adiciona nova feature')
4. Faça um push para a branch (git push origin feature/nova-feature)
5. Abra um Pull Request

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## Contato

Para mais informações, sinta-se à vontade para entrar em contato:

- Nome: Luiz Alves
- Email: luiz.alves1003@outlook.com
- GitHub: [LuizzAlves](https://github.com/LuizzAlves)
