#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elemento {
    char nome[50];
    struct Elemento *proximo;
} Elemento;

/* Cria um novo elemento com o nome informado. Retorna NULL se falhar. */
Elemento* criarElemento(const char *nome)
{
    Elemento *novo = malloc(sizeof(Elemento));
    if (!novo) {
        printf("Erro de memoria!\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->proximo = NULL;
    return novo;
}

/* Insere um novo nome na lista mantendo a ordem alfabetica. */
Elemento* inserir(Elemento *inicio)
{
    char nome[50];
    printf("Digite o nome: ");
    scanf("%49s", nome);

    Elemento *novo = criarElemento(nome);
    if (!novo)
        return inicio;

    /* Caso 1: lista vazia ou o novo nome vem antes do primeiro */
    if (inicio == NULL || strcmp(nome, inicio->nome) < 0) {
        novo->proximo = inicio;
        return novo;
    }

    /* Caso 2: percorre ate achar a posicao correta */
    Elemento *atual = inicio;
    while (atual->proximo != NULL && strcmp(atual->proximo->nome, nome) < 0) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    return inicio;
}

/* Remove a primeira ocorrencia do nome informado. */
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

/* Exibe todos os elementos da lista. */
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
        atual = atual->proximo;
    }
    printf("---------------\n");
}

/* Libera toda a memoria ocupada pela lista. */
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
