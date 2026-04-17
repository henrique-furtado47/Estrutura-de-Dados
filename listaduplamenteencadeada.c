#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char nome[50];
    struct Node *proximo;
    struct Node *anterior;
} Node;

Node *criarElemento(const char *nome)
{
    Node *novo = malloc(sizeof(Node));
    if (!novo) {
        printf("Erro de memoria!\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->proximo = NULL;
    novo->anterior = NULL;
    return novo;
}

Node *inserirElemento(Node *inicio)
{
    char nome[50];
    printf("Digite o nome: ");
    scanf("%49s", nome);

    Node *novo = criarElemento(nome);
    if (!novo)
        return inicio;

    if (inicio == NULL || strcmp(nome, inicio->nome) < 0)
    {
        novo->proximo = inicio;
        if (inicio != NULL)
            inicio->anterior = novo;
        inicio = novo;
        return inicio;
    }

    Node *atual = inicio;

    while (atual->proximo != NULL && strcmp(nome, atual->proximo->nome) > 0)
    {
        atual = atual->proximo;
    }

    if (atual->proximo != NULL)
    {
        novo->proximo = atual->proximo;
        atual->proximo->anterior = novo;
    }
    novo->anterior = atual;
    atual->proximo = novo;
    return inicio;    
}
Node *removerElemento(Node *inicio)
{
    char nome[50];
    printf("Digite o nome a ser removido: ");
    scanf("%49s", nome);

    if (strcmp(inicio->nome, nome) == 0)
    {
        Node *temp = inicio;
        inicio = inicio->proximo;
        if (inicio != NULL)
            inicio->anterior = NULL;
        free(temp);
    }
    else
    {
        Node *atual = inicio->proximo;
        while (atual != NULL && strcmp(atual->nome, nome) != 0)
        {
            atual = atual->proximo;
        }
        if (atual != NULL)
        {
            atual->anterior->proximo = atual->proximo;
            if (atual->proximo != NULL)
                atual->proximo->anterior = atual->anterior;
            free(atual);
        }
    }

    // teste de lista vazia
    if (inicio == NULL)
        printf("Lista vazia!\n");

    return inicio;
}

/* Exibe todos os elementos da lista. */
void listar(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("---- Lista ----\n");
    Node *atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s\n", i++, atual->nome);
        atual = atual->proximo;
    }
    printf("---------------\n");
}

void listarReverso(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Node *atual = inicio;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    int i = 1;
    printf("---- Lista Reversa ----\n");
    while (atual != NULL) {
        printf("%d. %s\n", i++, atual->nome);
        atual = atual->anterior;
    }
    printf("----------------------\n");
}

void navegar(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Node *cursor = inicio;
    int opcao_cursor;
    do
    {
        printf("Cursor: %s\n", cursor->nome);
        printf("0 SAI\n<- 1 Esquerda ||  2 Direita ->\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_cursor);
        system("clear");
        switch (opcao_cursor)
        {
            case 1:
            if (cursor->anterior != NULL)
                cursor = cursor->anterior;
            else
                printf("Não há elemento anterior.\n");
            break;
            case 2:
            if (cursor->proximo != NULL)
                cursor = cursor->proximo;
            else
                printf("Não há elemento seguinte.\n");
            break;
        }
    } while (opcao_cursor != 0);

    return;
}
int main(void)
{
    Node *lista = NULL;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Listar\n");
        printf("4 - Listar Reverso\n");
        printf("5 - Navegar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
            continue;
        }
        system("clear");
        switch (opcao) {
            case 1:  lista = inserirElemento(lista);   break;
            case 2:  lista = removerElemento(lista);   break;
            case 3:  listar(lista);            break;
            case 4:  listarReverso(lista);    break;
            case 5:  navegar(lista);          break;
            case 0:  printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
