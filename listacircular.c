// Henrique Furtado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>



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
    novo->proximo = novo;
    novo->anterior = novo;
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
        printf("   Idade: %d\n", atual->idade);
        printf("   Renda: R$%.2f\n", atual->renda);
        printf("   Prioritário: %s\n---------------\n", atual->prioritario ? "Sim" : "Não");
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
        printf("   Idade: %d\n", atual->idade);
        printf("   Renda: R$%.2f\n", atual->renda);
        printf("   Prioritário: %s\n---------------\n", atual->prioritario ? "Sim" : "Não");
        atual = atual->anterior;
    } while (atual != inicio->anterior);  /* para quando voltar ao ultimo */
    printf("----------------------\n");
}

static struct termios old_tio;

void setup_terminal_leitura_direta(void) {
    struct termios new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_terminal_original(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

int getch(void) {
    int ch;
    setup_terminal_leitura_direta();
    ch = getchar();
    restore_terminal_original();
    return ch;
}

void navegar(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Node *cursor = inicio;
    int ch;

    while (1)
    {   
        system("clear");
        printf("---------------\n");
        printf("   Anterior: %s\n", cursor->anterior->nome);
        printf("   Idade: %d\n", cursor->anterior->idade);
        printf("   Renda: R$%.2f\n", cursor->anterior->renda);
        printf("   Prioritário: %s\n", cursor->anterior->prioritario ? "Sim" : "Não");
        printf("---------------\n");
        printf(">>  Cursor: %s <<\n", cursor->nome);
        printf("    Idade: %d\n", cursor->idade);
        printf("    Renda: R$%.2f\n", cursor->renda);
        printf("    Prioritário: %s\n", cursor->prioritario ? "Sim" : "Não");
        printf("---------------\n");
        printf("   Próximo: %s\n", cursor->proximo->nome);
        printf("   Idade: %d\n", cursor->proximo->idade);
        printf("   Renda: R$%.2f\n", cursor->proximo->renda);
        printf("   Prioritário: %s\n", cursor->proximo->prioritario ? "Sim" : "Não");
        printf("---------------\n\n");

        printf("Use as SETAS para navegar | Pressione ESC para sair\n");
        
        ch = getch();

        if (ch == 27) {
            int next_ch1 = getch();
            if (next_ch1 == '[') {
                int next_ch2 = getch();
                switch (next_ch2) {
                    case 'A':
                        cursor = cursor->anterior;
                        break;
                    case 'B':
                        cursor = cursor->proximo;
                        break;
                }
            } else {
                ungetc(next_ch1, stdin);
                break; 
            }
        }
    }

    system("clear");
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
