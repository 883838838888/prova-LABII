#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Estrutura de dados para um contato
typedef struct {
    char nome[50];
    char email[50];
    char telefone[15];
} Contato;

// Tamanho máximo da lista de contatos
#define MAX_CONTATOS 100

// Tabela hash para armazenar os contatos
Contato tabela[MAX_CONTATOS];

// Função de hash usando o método da multiplicação
int hash(char* chave) {
    unsigned int h = 0;
    int i;
    for (i = 0; i < strlen(chave); i++) {
        h = h * 31 + chave[i];
    }
    return h % MAX_CONTATOS;
}

// Função para adicionar um novo contato
void adicionarContato() {
    Contato novoContato;
    printf("Digite o nome: ");
    scanf("%s", novoContato.nome);
    printf("Digite o email: ");
    scanf("%s", novoContato.email);
    printf("Digite o telefone: ");
    scanf("%s", novoContato.telefone);
    
    // Calcular o índice de hash para o contato
    int indice = hash(novoContato.nome);
    
    // Verificar se o índice está vazio
    if (strlen(tabela[indice].nome) == 0) {
        tabela[indice] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("O índice já está ocupado. O contato não pode ser adicionado.\n");
    }
}

// Função para listar todos os contatos
void listarContatos() {
    printf("Lista de contatos:\n");
    int i;
    for (i = 0; i < MAX_CONTATOS; i++) {
        if (strlen(tabela[i].nome) > 0) {
            printf("Nome: %s\n", tabela[i].nome);
            printf("Email: %s\n", tabela[i].email);
            printf("Telefone: %s\n", tabela[i].telefone);
            printf("\n");
        }
    }
}

// Função para buscar um contato pelo nome
void buscarContato() {
    char nome[50];
    printf("Digite o nome do contato: ");
    scanf("%s", nome);
    
    // Calcular o índice de hash para o nome
    int indice = hash(nome);
    
    // Verificar se o contato existe
    if (strcmp(tabela[indice].nome, nome) == 0) {
        printf("Contato encontrado:\n");
        printf("Nome: %s\n", tabela[indice].nome);
        printf("Email: %s\n", tabela[indice].email);
        printf("Telefone: %s\n", tabela[indice].telefone);
    } else {
        printf("Contato não encontrado.\n");
    }
}

// Função para exportar os contatos para um arquivo
void exportarContatos() {
    char nomeArquivo[50];
    printf("Digite o nome do arquivo de exportação: ");
    scanf("%s", nomeArquivo);
    
    // Abrir o arquivo para escrita
    FILE* arquivo = fopen(nomeArquivo, "w");
    
    // Verificar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    // Escrever cada contato no arquivo
    int i;
    for (i = 0; i < MAX_CONTATOS; i++) {
        if (strlen(tabela[i].nome) > 0) {
            fprintf(arquivo, "Nome: %s\n", tabela[i].nome);
            fprintf(arquivo, "Email: %s\n", tabela[i].email);
            fprintf(arquivo, "Telefone: %s\n", tabela[i].telefone);
            fprintf(arquivo, "\n");
        }
    }
    
    // Fechar o arquivo
    fclose(arquivo);
    
    printf("Contatos exportados com sucesso!\n");
}

// Função para excluir um contato pelo nome
void excluirContato() {
    char nome[50];
    printf("Digite o nome do contato a ser excluído: ");
    scanf("%s", nome);
    
    // Calcular o índice de hash para o nome
    int indice = hash(nome);
    
    // Verificar se o contato existe
    if (strcmp(tabela[indice].nome, nome) == 0) {
        // Limpar o contato
        memset(&tabela[indice], 0, sizeof(Contato));
        printf("Contato excluído com sucesso!\n");
    } else {
        printf("Contato não encontrado.\n");
    }
}

bool validarTelefone(char* telefone) {
    int i, digitCount = 0, dashCount = 0;

    // Verificar se o telefone possui apenas dígitos e um traço
    for (i = 0; telefone[i] != '\0'; i++) {
        if (isdigit(telefone[i])) {
            digitCount++;
        }
        if (telefone[i] == '-') {
            dashCount++;
        }
    }

    // O telefone deve conter apenas dígitos e opcionalmente um traço
    if (digitCount >= 8 && digitCount <= 12 && dashCount <= 1) {
        return true; // Telefone válido
    } else {
        return false; // Telefone inválido
    }
}


bool validarEmail(char* email) {
    int i, atCount = 0, dotCount = 0;

    // Verificar se o email possui pelo menos um '@' e um '.'
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
        }
        if (email[i] == '.') {
            dotCount++;
        }
    }

    // O email deve ter exatamente um '@' e um '.'
    if (atCount == 1 && dotCount >= 1) {
        return true; // Email válido
    } else {
        return false; // Email inválido
    }
}



// Função principal (menu)
int main() {
    int opcao;
    
    // Loop principal do menu
    while (1) {
    	
    	   printf("Bem vindo deseja entrar na minha lista de contatos?\n");
        printf(" MENU:\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Buscar contato\n");
        printf("4. Exportar contatos\n");
        printf("5. Excluir contato\n");
        printf("6. Sair\n");
        printf("Digite a opcao desejada: \n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                buscarContato();
                break;
            case 4:
                exportarContatos();
                break;
            case 5:
                excluirContato();
                break;
            case 6:
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
        
        printf("\n");
    }
    
    return 0;
}
