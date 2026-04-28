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

Node *removerPorNome(Node *inicio, const char *nome)
{
    if (inicio == NULL) {
        return NULL;
    }

    Node *atual = inicio;

    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual->proximo == atual) {
                free(atual);
                return NULL;
            }

            atual->anterior->proximo = atual->proximo;
            atual->proximo->anterior = atual->anterior;

            if (atual == inicio) {
                inicio = atual->proximo;
            }

            free(atual);
            return inicio;
        }

        atual = atual->proximo;
    } while (atual != inicio);

    printf("\"%s\" nao encontrado.\n", nome);
    return inicio;
}

Node *removerAtual(Node *inicio, Node *alvo)
{
    if (inicio == NULL || alvo == NULL) {
        return inicio;
    }

    if (alvo->proximo == alvo) {
        free(alvo);
        return NULL;
    }

    alvo->anterior->proximo = alvo->proximo;
    alvo->proximo->anterior = alvo->anterior;

    if (alvo == inicio) {
        inicio = alvo->proximo;
    }

    free(alvo);
    return inicio;
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

enum Tecla {
    TECLA_SETA_CIMA = 1001,
    TECLA_SETA_BAIXO = 1002,
    TECLA_INSERT = 1003,
    TECLA_DELETE = 1004
};

int ler_tecla(void)
{
    int ch = getch();

    if (ch != 27) {
        return ch;
    }

    int ch2 = getch();
    if (ch2 != '[') {
        return 27;
    }

    int ch3 = getch();

    switch (ch3) {
        case 'A':
            return TECLA_SETA_CIMA;
        case 'B':
            return TECLA_SETA_BAIXO;
        case '2':
            getch();
            return TECLA_INSERT;
        case '3':
            getch();
            return TECLA_DELETE;
        default:
            return ch3;
    }
}

Node *navegar(Node *inicio)
{
    if (inicio == NULL) {
        printf("Lista vazia.\n");
        printf("Pressione qualquer tecla para inserir o primeiro elemento.\n");
        getch();
        inicio = inserirElemento(inicio);
    }

    Node *cursor = inicio;

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

        printf("Use as SETAS para navegar | INSERT para inserir | DELETE para remover | Pressione ESC para sair\n");

        int tecla = ler_tecla();

        if (tecla == TECLA_SETA_CIMA) {
            cursor = cursor->anterior;
        } else if (tecla == TECLA_SETA_BAIXO) {
            cursor = cursor->proximo;
        } else if (tecla == TECLA_INSERT) {
            inicio = inserirElemento(inicio);
            if (inicio != NULL) {
                cursor = inicio;
            }
        } else if (tecla == TECLA_DELETE) {
            Node *proximo = cursor->proximo;
            printf("Você deseja remover %s? (s/n): ", cursor->nome);
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S') {
                inicio = removerAtual(inicio, cursor);
                if (inicio == NULL) {
                    break;
                }
                cursor = proximo == cursor ? inicio : proximo;
            }
        } else if (tecla == 27) {
            break;
        }
    }

    system("clear");
    return inicio;
}
int main(void)
{
    Node *lista = NULL;
    lista = navegar(lista);
    printf("Encerrando...\n");
    return 0;
}
