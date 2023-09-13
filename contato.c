#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir a estrutura de um contato
typedef struct {
    char nome[50];
    char email[50];
    char telefone[20];
} Contato;

// Variáveis globais
Contato listaContatos[100]; // Lista de contatos
int totalContatos = 0; // Total de contatos na lista

// Protótipos das funções
void adicionarContato();
void listarContatos();
void buscarContato();
void exportarContatos();
void excluirContato();
int validarTelefone(const char *);
int validarEmail(const char *);

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Buscar contato\n");
        printf("4. Exportar contatos\n");
        printf("5. Excluir contato\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}

void adicionarContato() {
    Contato novoContato;

    printf("\nAdicionar Contato\n");
    printf("Nome: ");
    scanf("%s", novoContato.nome);

    printf("Email: ");
    scanf("%s", novoContato.email);
    while (!validarEmail(novoContato.email)) {
        printf("Email inválido! Insira novamente: ");
        scanf("%s", novoContato.email);
    }

    printf("Telefone: ");
    scanf("%s", novoContato.telefone);
    while (!validarTelefone(novoContato.telefone)) {
        printf("Telefone inválido! Insira novamente: ");
        scanf("%s", novoContato.telefone);
    }

    listaContatos[totalContatos] = novoContato;
    totalContatos++;

    printf("Contato adicionado com sucesso!\n");
}

void listarContatos() {
    printf("\nLista de Contatos:\n");
    int i;
    for (i = 0; i < totalContatos; i++) {
        printf("Nome: %s\n", listaContatos[i].nome);
        printf("Email: %s\n", listaContatos[i].email);
        printf("Telefone: %s\n\n", listaContatos[i].telefone);
    }
}

void buscarContato() {
    char nomeBusca[50];
    int encontrado = 0;

    printf("\nBuscar Contato\n");
    printf("Digite o nome do contato: ");
    scanf("%s", nomeBusca);
int i;
    for (i = 0; i < totalContatos; i++) {
        if (strcmp(nomeBusca, listaContatos[i].nome) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", listaContatos[i].nome);
            printf("Email: %s\n", listaContatos[i].email);
            printf("Telefone: %s\n", listaContatos[i].telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado!\n");
    }
}

void exportarContatos() {
    FILE *arquivo;
    char nomeArquivo[50];

    printf("\nExportar Contatos\n");
    printf("Digite o nome do arquivo de exportação: ");
    scanf("%s", nomeArquivo);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de exportação!\n");
        return;
    }
     int i;
    for ( i = 0; i < totalContatos; i++) {
        fprintf(arquivo, "Nome: %s\n", listaContatos[i].nome);
        fprintf(arquivo, "Email: %s\n", listaContatos[i].email);
        fprintf(arquivo, "Telefone: %s\n\n", listaContatos[i].telefone);
    }

    fclose(arquivo);

    printf("Contatos exportados com sucesso!\n");
}

void excluirContato() {
    char nomeExcluir[50];
    int encontrado = 0;

    printf("\nExcluir Contato\n");
    printf("Digite o nome do contato a ser excluído: ");
    scanf("%s", nomeExcluir);
    int i;
    int j;
    for ( i = 0; i < totalContatos; i++) {
        if (strcmp(nomeExcluir, listaContatos[i].nome) == 0) {
            for (j = i; j < totalContatos - 1; j++) {
                listaContatos[j] = listaContatos[j + 1];
            }
            totalContatos--;
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        printf("Contato excluído com sucesso!\n");
    } else {
        printf("Contato não encontrado!\n");
    }
}

int validarTelefone(const char *telefone) {
    // Verificar se o telefone tem o formato XXXX-XXXX
    int i;
    for (i = 0; i < 4; i++) {
        if (!isdigit(telefone[i])) {
            return 0;
        }
    }
    if (telefone[i++] != '-') {
        return 0;
    }
    for (; i < 8; i++) {
        if (!isdigit(telefone[i])) {
            return 0;
        }
    }
    return 1;
}

int validarEmail(const char *email) {
    // Verificar se o email tem um formato básico de endereço de email
    int i = 0;
    int at_found = 0;
    while (email[i] != '\0') {
        if (email[i] == '@') {
            at_found = 1;
        }
        i++;
    }
    return at_found;
}

