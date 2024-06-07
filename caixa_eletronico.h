#ifndef CAIXA_ELETRONICO_H
#define CAIXA_ELETRONICO_H

#define MAX_CONTAS 100

// Estrutura para armazenar informações da conta
struct registro {
    char nome[50];
    int numero_conta;
    float saldo;
    char senha[50]; // Tamanho maior para armazenar hash da senha
    char transacoes[10][150]; // Histórico das últimas 10 transações com espaço para timestamp
    int num_transacoes; // Número de transações registradas
};

// Declaração das funções
void atualizarSaldoArquivo(struct registro *contas, int num_contas);
void carregarContasArquivo(struct registro *contas, int *num_contas);
void criarArquivo();
int cadastrarConta(struct registro *contas, int *num_contas);
int entrarConta(struct registro *contas, int num_contas, int numeroConta, const char *senha);
void menuOperacoes(struct registro *contas, int num_contas, int indiceConta);
int encontrarConta(struct registro *contas, int num_contas, int numeroConta);
void registrarTransacao(struct registro *contas, int indiceConta, const char *descricao);
void gerarExtrato(struct registro *contas, int indiceConta);
void redefinirSenha(struct registro *contas, int num_contas);
void registrarLog(const char *mensagem);
void* salarioThread(void* arg);
void realizarDeposito(struct registro *contas, int indiceConta);
void realizarSaque(struct registro *contas, int indiceConta);
void mostrarSaldo(struct registro *contas, int indiceConta);
void realizarTransferencia(struct registro *contas, int num_contas, int indiceConta);

#endif
