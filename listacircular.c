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
    novo->proximo = novo;
    novo->anterior = novo;
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

    if (inicio == NULL)
    {
        return novo;
    }
    if (strcmp(nome, inicio->nome) < 0)
    {
        novo->proximo = inicio;
        novo->anterior = inicio->anterior;
        inicio->anterior->proximo = novo;
        inicio->anterior = novo;
        inicio = novo;
        return inicio;
    }

    Node *atual = inicio;

    while (atual->proximo != inicio && strcmp(nome, atual->proximo->nome) > 0)
    {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;          // novo aponta pra frente
    atual->proximo->anterior = novo;         // o da frente aponta pra trás pro novo
    novo->anterior = atual;                  // novo aponta pra trás
    atual->proximo = novo;                   // o de trás aponta pra frente pro novo


    return inicio;    
}
Node *removerElemento(Node *inicio)
{
    char nome[50];
    printf("Digite o nome a ser removido: ");
    scanf("%49s", nome);

    if (strcmp(inicio->nome, nome) == 0)
    {
        /* Se é o unico nó, libera e retorna NULL */
        if (inicio->proximo == inicio) {
            free(inicio);
            return NULL;
        }
        /* Religa o ultimo com o segundo */
        Node *temp = inicio;
        inicio->anterior->proximo = inicio->proximo;  // ultimo->frente = segundo
        inicio->proximo->anterior = inicio->anterior;  // segundo->tras = ultimo
        inicio = inicio->proximo;                       // segundo vira o novo inicio
        free(temp);
    }
    else
    {
        Node *atual = inicio->proximo;
        while (atual != inicio && strcmp(atual->nome, nome) != 0)
        {
            atual = atual->proximo;
        }
        if (atual != inicio)
        {
            /* Sempre religa os dois lados */
            atual->anterior->proximo = atual->proximo;
            atual->proximo->anterior = atual->anterior;
            free(atual);
        }
        else
        {
            printf("\"%s\" nao encontrado.\n", nome);
        }
    }
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
    do {
        printf("%d. %s\n", i++, atual->nome);
        atual = atual->proximo;
    } while (atual != inicio);
    printf("---------------\n");
}

void listarReverso(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    Node *atual = inicio->anterior;  /* comeca no ultimo */
    int i = 1;
    printf("---- Lista Reversa ----\n");
    do {
        printf("%d. %s\n", i++, atual->nome);
        atual = atual->anterior;
    } while (atual != inicio->anterior);  /* para quando voltar ao ultimo */
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
            case 1: cursor = cursor->anterior; break;
            case 2: cursor = cursor->proximo;  break;
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
