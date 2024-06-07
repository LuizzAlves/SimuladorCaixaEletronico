#include "caixa_eletronico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Atualiza o arquivo de contas com os dados mais recentes
void atualizarSaldoArquivo(struct registro *contas, int num_contas) {
    FILE *arquivo = fopen("contas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    for (int i = 0; i < num_contas; ++i) {
        fprintf(arquivo, "Nome: %s\nNumero da conta: %d\nSaldo: %.2f\nSenha: %s\n----------------------\n",
                contas[i].nome, contas[i].numero_conta, contas[i].saldo, contas[i].senha);
    }
    fclose(arquivo);
}

// Carrega as contas do arquivo para o array de contas
void carregarContasArquivo(struct registro *contas, int *num_contas) {
    FILE *arquivo = fopen("contas.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo de contas nao encontrado ou vazio.\n");
        return;
    }
    char buffer[255];
    while (fgets(buffer, 255, arquivo)) {
        if (strstr(buffer, "Nome: ")) {
            sscanf(buffer, "Nome: %s\nNumero da conta: %d\nSaldo: %f\nSenha: %s",
                   contas[*num_contas].nome, &contas[*num_contas].numero_conta, &contas[*num_contas].saldo, contas[*num_contas].senha);
            contas[*num_contas].num_transacoes = 0; // Inicializa o número de transações
            (*num_contas)++;
            if (*num_contas >= MAX_CONTAS) {
                printf("Limite maximo de contas atingido.\n");
                break;
            }
        }
    }
    fclose(arquivo);
}

// Cria o arquivo de contas se ele não existir
void criarArquivo() {
    FILE *arquivo = fopen("contas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao acessar o arquivo de contas.\n");
        exit(1);
    }
    fclose(arquivo);
}

// Cadastra uma nova conta
int cadastrarConta(struct registro *contas, int *num_contas) {
    if (*num_contas >= MAX_CONTAS) {
        printf("Numero maximo de contas atingido.\n");
        return -1;
    }
    printf("Nome: ");
    scanf("%s", contas[*num_contas].nome);

    do {
        printf("Digite o valor inicial da conta: ");
        scanf("%f", &contas[*num_contas].saldo);
        if (contas[*num_contas].saldo <= 0) {
            printf("O valor inicial da conta deve ser maior que zero.\n");
        }
    } while (contas[*num_contas].saldo <= 0);

    printf("Digite a senha: ");
    scanf("%s", contas[*num_contas].senha);

    srand(time(NULL));
    contas[*num_contas].numero_conta = rand() % 9000 + 1000;
    contas[*num_contas].num_transacoes = 0; // Inicializa o número de transações
    (*num_contas)++;
    atualizarSaldoArquivo(contas, *num_contas); // Atualiza o arquivo após cadastrar a conta
    return *num_contas - 1;
}

// Encontra o índice de uma conta pelo número da conta
int encontrarConta(struct registro *contas, int num_contas, int numeroConta) {
    for (int i = 0; i < num_contas; ++i) {
        if (contas[i].numero_conta == numeroConta) {
            return i;
        }
    }
    return -1;
}

// Verifica se a senha está correta para entrar na conta
int entrarConta(struct registro *contas, int num_contas, int numeroConta, const char *senha) {
    for (int i = 0; i < num_contas; ++i) {
        if (contas[i].numero_conta == numeroConta && strcmp(contas[i].senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

// Registra uma transação no histórico da conta e no arquivo de log
void registrarTransacao(struct registro *contas, int indiceConta, const char *descricao) {
    char timestamp[20];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, sizeof(timestamp)-1, "%Y-%m-%d %H:%M:%S", t);

    if (contas[indiceConta].num_transacoes < 10) {
        snprintf(contas[indiceConta].transacoes[contas[indiceConta].num_transacoes], 150, "%s - %s", timestamp, descricao);
    } else {
        for (int i = 1; i < 10; ++i) {
            strcpy(contas[indiceConta].transacoes[i - 1], contas[indiceConta].transacoes[i]);
        }
        snprintf(contas[indiceConta].transacoes[9], 150, "%s - %s", timestamp, descricao);
    }
    contas[indiceConta].num_transacoes++;

    // Registrar no arquivo de log
    char mensagem[200];
    snprintf(mensagem, sizeof(mensagem), "Conta %d: %s - %s", contas[indiceConta].numero_conta, descricao, timestamp);
    registrarLog(mensagem);
}

// Gera o extrato das transações da conta
void gerarExtrato(struct registro *contas, int indiceConta) {
    printf("Extrato da conta %d:\n", contas[indiceConta].numero_conta);
    for (int i = 0; i < contas[indiceConta].num_transacoes; ++i) {
        printf("%s\n", contas[indiceConta].transacoes[i]);
    }
}

// Redefine a senha de uma conta
void redefinirSenha(struct registro *contas, int num_contas) {
    int numeroConta;
    char novaSenha[50];
    printf("Numero da conta: ");
    scanf("%d", &numeroConta);

    int indiceConta = encontrarConta(contas, num_contas, numeroConta);
    if (indiceConta == -1) {
        printf("Conta nao encontrada.\n");
        return;
    }

    printf("Digite a nova senha: ");
    scanf("%s", novaSenha);

    strcpy(contas[indiceConta].senha, novaSenha);
    printf("Senha alterada com sucesso.\n");
    registrarTransacao(contas, indiceConta, "Senha alterada");
    atualizarSaldoArquivo(contas, num_contas); // Atualiza o arquivo após redefinir a senha
}

// Realiza um depósito em uma conta
void realizarDeposito(struct registro *contas, int indiceConta) {
    float valor;
    printf("Digite o valor para deposito: ");
    scanf("%f", &valor);
    if (valor <= 0) {
        printf("Valor invalido para deposito.\n");
        return;
    }
    contas[indiceConta].saldo += valor;
    printf("Deposito realizado com sucesso. Novo saldo: %.2f\n", contas[indiceConta].saldo);
    char descricao[50];
    snprintf(descricao, sizeof(descricao), "Deposito de %.2f", valor);
    registrarTransacao(contas, indiceConta, descricao);
    atualizarSaldoArquivo(contas, indiceConta); // Atualiza o arquivo após o depósito
}

// Realiza um saque de uma conta
void realizarSaque(struct registro *contas, int indiceConta) {
    float valor;
    printf("Digite o valor para saque: ");
    scanf("%f", &valor);
    if (valor <= 0 || valor > contas[indiceConta].saldo) {
        printf("Valor invalido para saque.\n");
        return;
    }
    contas[indiceConta].saldo -= valor;
    printf("Saque realizado com sucesso. Novo saldo: %.2f\n", contas[indiceConta].saldo);
    char descricao[50];
    snprintf(descricao, sizeof(descricao), "Saque de %.2f", valor);
    registrarTransacao(contas, indiceConta, descricao);
    atualizarSaldoArquivo(contas, indiceConta); // Atualiza o arquivo após o saque
}

// Realiza uma transferência entre duas contas
void realizarTransferencia(struct registro *contas, int num_contas, int indiceContaOrigem) {
    int numeroContaDestino;
    float valor;
    printf("Digite o numero da conta destino: ");
    scanf("%d", &numeroContaDestino);
    int indiceContaDestino = encontrarConta(contas, num_contas, numeroContaDestino);
    if (indiceContaDestino == -1) {
        printf("Conta destino nao encontrada.\n");
        return;
    }
    printf("Digite o valor para transferencia: ");
    scanf("%f", &valor);
    if (valor <= 0 || valor > contas[indiceContaOrigem].saldo) {
        printf("Valor invalido para transferencia.\n");
        return;
    }
    contas[indiceContaOrigem].saldo -= valor;
    contas[indiceContaDestino].saldo += valor;
    printf("Transferencia realizada com sucesso. Novo saldo: %.2f\n", contas[indiceContaOrigem].saldo);
    char descricao[50];
    snprintf(descricao, sizeof(descricao), "Transferencia de %.2f para conta %d", valor, numeroContaDestino);
    registrarTransacao(contas, indiceContaOrigem, descricao);
    registrarTransacao(contas, indiceContaDestino, descricao);
    atualizarSaldoArquivo(contas, num_contas); // Atualiza o arquivo após a transferência
}

// Mostra o saldo de uma conta
void mostrarSaldo(struct registro *contas, int indiceConta) {
    printf("Saldo atual: %.2f\n", contas[indiceConta].saldo);
}

// Registra uma mensagem de log no arquivo de log
void registrarLog(const char *mensagem) {
    FILE *arquivo = fopen("log.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }
    fprintf(arquivo, "%s\n", mensagem);
    fclose(arquivo);
}
