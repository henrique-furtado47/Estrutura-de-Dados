/*
 * Árvore Binária de Busca (BST)
 * --------------------------------
 * Cada nó armazena uma letra (índice) e um inteiro correspondente.
 * Carrega o alfabeto (a=1, b=2, ..., z=26) e permite buscar uma
 * letra retornando o inteiro associado.
 *
 * Observação: para evitar que a árvore vire uma "lista" (degenerada),
 * inserimos as letras pelo meio (inserção balanceada recursiva).
 *
 * Compilar: gcc -g arvore1.c -o arvore1
 * Executar: ./arvore1
 */

 // Henrique Furtado
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct No {
    char  letra;     
    int   valor;   
    struct No *esq;
    struct No *dir;
} No;

/* ---------- Funções da árvore ---------- */

/* Cria um novo nó na memória dinâmica */
No* criarNo(char letra, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha de alocacao de memoria.\n");
        exit(1);
    }
    novo->letra = letra;
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/* Insere um nó na BST ordenando pela letra (índice) */
No* inserir(No *raiz, char letra, int valor) {
    if (raiz == NULL)
        return criarNo(letra, valor);

    if (letra < raiz->letra)
        raiz->esq = inserir(raiz->esq, letra, valor);
    else if (letra > raiz->letra)
        raiz->dir = inserir(raiz->dir, letra, valor);

    return raiz;
}

/* Busca uma letra na árvore. Retorna o inteiro ou -1 se nao achar */
int buscar(No *raiz, char letra) {
    if (raiz == NULL)
        return -1;
    if (letra == raiz->letra)
        return raiz->valor;
    if (letra < raiz->letra)
        return buscar(raiz->esq, letra);
    return buscar(raiz->dir, letra);
}

void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("  %c = %d\n", raiz->letra, raiz->valor);
    emOrdem(raiz->dir);
}

/* Libera toda a memoria da arvore */
void liberar(No *raiz) {
    if (raiz == NULL) return;
    liberar(raiz->esq);
    liberar(raiz->dir);
    free(raiz);
}


void carregarAlfabeto(No **raiz, int ini, int fim) {
    if (ini > fim) return;
    int meio = (ini + fim) / 2;
    char letra = 'a' + meio;
    int  valor = meio + 1;          
    *raiz = inserir(*raiz, letra, valor);
    carregarAlfabeto(raiz, ini, meio - 1);
    carregarAlfabeto(raiz, meio + 1, fim);
}

/* ---------- Programa principal ---------- */
int main(void) {
    No *raiz = NULL;

    carregarAlfabeto(&raiz, 0, 25);

    printf("Alfabeto carregado na arvore (em ordem):\n");
    emOrdem(raiz);

    char entrada;
    printf("\nDigite uma letra para buscar (ou '.' para sair): ");
    while (scanf(" %c", &entrada) == 1 && entrada != '.') {
        entrada = (char) tolower((unsigned char) entrada);

        if (entrada < 'a' || entrada > 'z') {
            printf("  '%c' nao eh uma letra do alfabeto (a-z).\n", entrada);
        } else {
            int valor = buscar(raiz, entrada);
            if (valor == -1)
                printf("  Letra '%c' nao encontrada.\n", entrada);
            else
                printf("  '%c' = %d\n", entrada, valor);
        }
        printf("\nDigite outra letra (ou '.' para sair): ");
    }

    liberar(raiz);
    printf("Encerrado.\n");
    return 0;
}
