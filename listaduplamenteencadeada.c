// Henrique Furtado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char nome[50];
    int idade;
    float renda;
    int prioritario;
    struct Node *proximo;
    struct Node *anterior;
} Node;

Node *criarElemento(const char *nome, int idade, float renda, int prioritario)
{
    Node *novo = malloc(sizeof(Node));
    if (!novo) {
        printf("Erro de memoria!\n");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->renda = renda;
    novo->prioritario = prioritario;
    novo->proximo = NULL;
    novo->anterior = NULL;
    return novo;
}

Node *inserirElemento(Node *inicio)
{
    char nome[50];
    printf("Digite o nome: ");
    scanf("%49s", nome);
    int idade;
    printf("Digite a idade: ");
    scanf("%d", &idade);
    float renda;
    printf("Digite a renda: ");
    scanf("%f", &renda);
    int prioritario;
    printf("Digite o status de prioridade (0 ou 1): ");
    scanf("%d", &prioritario);

    Node *novo = criarElemento(nome, idade, renda, prioritario);
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

    if (inicio == NULL)
        printf("Lista vazia!\n");

    return inicio;
}

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
        printf("   Idade: %d\n", atual->idade);
        printf("   Renda: %.2f\n", atual->renda);
        printf("   Prioritário: %s\n---------------\n", atual->prioritario ? "Sim" : "Não");
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
        printf("   Idade: %d\n", atual->idade);
        printf("   Renda: %.2f\n", atual->renda);
        printf("   Prioritário: %s\n---------------\n", atual->prioritario ? "Sim" : "Não");
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
        system("clear");
        if (cursor->anterior != NULL) 
        {
            printf("---------------\n");
            printf("   Anterior: %s\n", cursor->anterior->nome);
            printf("    Idade: %d\n", cursor->anterior->idade);
            printf("   Renda: %.2f\n", cursor->anterior->renda);
            printf("   Prioritário: %s\n", cursor->anterior->prioritario ? "Sim" : "Não");
        }
        else
        {
            printf("---------------\n");
            printf("   Anterior: [sem elemento anterior]\n");
        }
        printf("---------------\n");
        printf(">>  Cursor: %s <<\n", cursor->nome);
        printf("    Idade: %d\n", cursor->idade);
        printf("    Renda: %.2f\n", cursor->renda);
        printf("    Prioritário: %s\n", cursor->prioritario ? "Sim" : "Não");
        if (cursor->proximo != NULL)
        {
            printf("---------------\n");
            printf("   Próximo: %s\n", cursor->proximo->nome);
            printf("    Idade: %d\n", cursor->proximo->idade);
            printf("   Renda: %.2f\n", cursor->proximo->renda);
            printf("   Prioritário: %s\n", cursor->proximo->prioritario ? "Sim" : "Não");
        }
        else
        {
            printf("---------------\n");
            printf("   Próximo: [sem elemento próximo]\n");
        }
        printf("---------------\n\n");

        printf("1: Cima (Anterior) | 2: Baixo (Próximo) | 0: Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao_cursor) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao_cursor = -1; 
        }

        switch (opcao_cursor)
        {
            case 1: 
            if (cursor->anterior != NULL)
                cursor = cursor->anterior;
            else
                printf("Não há elemento anterior!\n");
            break;
            case 2: 
            if (cursor->proximo != NULL)
                cursor = cursor->proximo;
            else
                printf("Não há elemento próximo!\n");
            break;
            case 0: system("clear"); break; 
            default: 
            printf("Opção inválida!\n");
            printf("Pressione Enter para continuar...");
            while (getchar() != '\n'); 
            getchar(); 
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
