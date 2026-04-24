// Henrique Furtado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elemento {
    char nome[50];
    int idade;
    float renda;
    int prioritario;
    struct Elemento *proximo;
} Elemento;

Elemento* criarElemento(const char *nome, int idade, float renda, int prioritario)
{
    Elemento *novo = malloc(sizeof(Elemento));
    if (!novo) {
        printf("Erro de memoria!\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->renda = renda;
    novo->prioritario = prioritario;
    novo->proximo = NULL;
    return novo;
}

Elemento* inserir(Elemento *inicio)
{
    char nome[50];
    printf("Digite o nome: ");
    scanf("%49s", nome);
    printf("Digite a idade: ");
    scanf("%d", &idade);
    printf("Digite a renda: ");
    scanf("%f", &renda);
    printf("Digite o status de prioridade (0 ou 1): ");
    scanf("%d", &prioritario);

    Elemento *novo = criarElemento(nome, idade, renda, prioritario);
    if (!novo)
        return inicio;

    if (inicio == NULL || strcmp(nome, inicio->nome) < 0) {
        novo->proximo = inicio;
        return novo;
    }

    Elemento *atual = inicio;
    while (atual->proximo != NULL && strcmp(atual->proximo->nome, nome) < 0) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    return inicio;
}

Elemento* remover(Elemento *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return NULL;
    }

    char nome[50];
    printf("Digite o nome a remover: ");
    scanf("%49s", nome);

    if (strcmp(inicio->nome, nome) == 0) {
        Elemento *removido = inicio;
        inicio = inicio->proximo;
        free(removido);
        printf("\"%s\" removido com sucesso.\n", nome);
        return inicio;
    }

    Elemento *atual = inicio;
    while (atual->proximo != NULL && strcmp(atual->proximo->nome, nome) != 0) {
        atual = atual->proximo;
    }

    if (atual->proximo == NULL) {
        printf("\"%s\" nao encontrado na lista.\n", nome);
    } else {
        Elemento *removido = atual->proximo;
        atual->proximo = removido->proximo;
        free(removido);
        printf("\"%s\" removido com sucesso.\n", nome);
    }
    return inicio;
}

void listar(Elemento *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("---- Lista ----\n");
    Elemento *atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s\n", i++, atual->nome);
        printf("   Idade: %d\n", atual->idade);
        printf("   Renda: %.2f\n", atual->renda);
        printf("   Prioritário: %s\n---------------\n", atual->prioritario ? "Sim" : "Não");
        atual = atual->proximo;
    }
    printf("---------------\n");
}

void liberar(Elemento *inicio)
{
    while (inicio != NULL) {
        Elemento *tmp = inicio;
        inicio = inicio->proximo;
        free(tmp);
    }
}

int main(void)
{
    Elemento *lista = NULL;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
            continue;
        }
        switch (opcao) {
            case 1:  lista = inserir(lista);   break;
            case 2:  lista = remover(lista);   break;
            case 3:  listar(lista);            break;
            case 0:  printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberar(lista);
    return 0;
}
