#include "caixa_eletronico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100

int main() {
    struct registro contas[MAX_CONTAS];
    int num_contas = 0;

    criarArquivo();
    carregarContasArquivo(contas, &num_contas);

    int opcao;
    do {
        printf("CAIXA ELETRONICO:\n");
        printf("1. Cadastrar conta\n");
        printf("2. Entrar na conta\n");
        printf("3. Redefinir senha\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int conta_idx = cadastrarConta(contas, &num_contas);
                if (conta_idx != -1) {
                    printf("Conta cadastrada com sucesso. Numero da conta: %d\n", contas[conta_idx].numero_conta);
                }
                break;
            }
            case 2: {
                int numeroConta;
                char senha[50];
                printf("Numero da conta: ");
                scanf("%d", &numeroConta);
                printf("Senha: ");
                scanf("%s", senha);

                int indiceConta = entrarConta(contas, num_contas, numeroConta, senha);
                if (indiceConta == -1) {
                    printf("Numero da conta ou senha incorretos.\n");
                    break;
                }

                int opcaoConta;
                do {
                    printf("Conta %d:\n", contas[indiceConta].numero_conta);
                    printf("1. Ver saldo\n");
                    printf("2. Realizar deposito\n");
                    printf("3. Realizar saque\n");
                    printf("4. Realizar transferencia\n");
                    printf("5. Gerar extrato\n");
                    printf("6. Sair\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoConta);

                    switch (opcaoConta) {
                        case 1:
                            mostrarSaldo(contas, indiceConta);
                            break;
                        case 2:
                            realizarDeposito(contas, indiceConta);
                            atualizarSaldoArquivo(contas, num_contas); // Atualiza após o depósito
                            break;
                        case 3:
                            realizarSaque(contas, indiceConta);
                            atualizarSaldoArquivo(contas, num_contas); // Atualiza após o saque
                            break;
                        case 4:
                            realizarTransferencia(contas, num_contas, indiceConta);
                            atualizarSaldoArquivo(contas, num_contas); // Atualiza após a transferência
                            break;
                        case 5:
                            gerarExtrato(contas, indiceConta);
                            break;
                        case 6:
                            printf("Saindo da conta...\n");
                            break;
                        default:
                            printf("Opcao invalida.\n");
                            break;
                    }
                } while (opcaoConta != 6);
                break;
            }
            case 3:
                redefinirSenha(contas, num_contas);
                atualizarSaldoArquivo(contas, num_contas); // Atualiza após redefinir a senha
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}
