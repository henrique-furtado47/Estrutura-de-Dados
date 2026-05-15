// Henrique Furtado

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 256
#define TOTAL_ITENS 100

typedef struct {
    char nome[50];
    int codigo;
} Item;

void inicializar_arquivo(Item itens[], int *contador)
{
    FILE *arquivo;
    char linha[MAX_LINHA];

    arquivo = fopen("/home/henrique.furtado/Estrutura de Dados/nomes_aleatorios.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    // Ignora cabeçalho
    fgets(linha, MAX_LINHA, arquivo);

    while (fgets(linha, MAX_LINHA, arquivo) != NULL &&
           *contador < TOTAL_ITENS)
    {
        linha[strcspn(linha, "\n")] = 0;

        char *nome = strtok(linha, ",");
        char *codigo = strtok(NULL, ",");

        if (nome != NULL && codigo != NULL) {

            strcpy(itens[*contador].nome, nome);

            itens[*contador].codigo = atoi(codigo);

            (*contador)++;
        }
    }

    fclose(arquivo);
}

void listar(Item itens[], int *contador)
{
    for (int i = 0; i < *contador; i++) {

        printf("%d -> %s | %d\n", i, itens[i].nome, itens[i].codigo);
    }
}

void ordenar_codigo(Item itens[], int *contador)
{      
    int trocas=0;
    Item temp;
    for (int i = 0; i < *contador - 1; i++)
    {
        for (int j = i + 1; j < *contador; j++)
        {
            printf("%d vs %d\n", itens[i].codigo, itens[j].codigo);
            if (itens[i].codigo > itens[j].codigo)
            {
                trocas++;
                printf("%d > %d\n", itens[i].codigo, itens[j].codigo);
                printf("Trocando de posição...\n");
                temp = itens[i];
                itens[i] = itens[j];
                itens[j] = temp;
            }

        }
    }
    printf("\nFoi feito %d trocas\n", trocas);

}

void ordenar_nome(Item itens[], int *contador)
{   
    int trocas=0;
    Item temp;
    for (int i = 0; i < *contador - 1; i++)
    {
        for (int j = 1 + i; j < *contador; j++)
        {
            printf("%s vs %s\n", itens[i].nome, itens[j].nome);
            if (strcmp(itens[i].nome, itens[j].nome)>0)
            {  
                trocas ++;
                printf("%s > %s\n", itens[i].nome, itens[j].nome);
                printf("Trocando de posição...");
                temp = itens[i];
                itens[i] = itens[j];
                itens[j] = temp;
            }
        }
    }
    printf("\nFoi feito %d trocas\n", trocas);
}

void quicksort_codigo(Item itens[], int inicio, int fim, int *trocas)
{
    if (inicio < fim)
    {
        Item pivot = itens[fim];
        Item temp;

        printf("\n=================================\n");
        printf("QuickSort de %d até %d\n", inicio, fim);
        printf("Pivot: %d\n", pivot.codigo);

        int i = inicio - 1;

        for (int j = inicio; j < fim; j++)
        {
            printf("Comparando %d com %d\n", itens[j].codigo, pivot.codigo);

            if (itens[j].codigo < pivot.codigo)
            {
                i++;

                printf("%d < %d\n", itens[j].codigo, pivot.codigo);
                printf("Trocando posição...\n");

                temp = itens[i];
                itens[i] = itens[j];
                itens[j] = temp;

                (*trocas)++;
            }
        }

        printf("Colocando pivot na posição correta...\n");

        temp = itens[i + 1];
        itens[i + 1] = itens[fim];
        itens[fim] = temp;

        (*trocas)++;

        int posicao_pivot = i + 1;

        printf("Pivot %d foi para posição %d\n", pivot.codigo, posicao_pivot);

        quicksort_codigo(itens, inicio, posicao_pivot - 1, trocas);
        quicksort_codigo(itens, posicao_pivot + 1, fim, trocas);
    }
}
int main()
{   

    int opcao;
    Item itens[TOTAL_ITENS];

    int contador = 0;

    inicializar_arquivo(itens, &contador);
    do
    {
        printf("\nEscolha uma opção:\n");
        printf("1 - Listar\n");
        printf("2 - Ordenar por nome\n");
        printf("3 - Ordenar por código\n");
        printf("4 - Reiniciar Lista\n");
        printf("5 - Quick Sort Código\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);
        system("clear");

        switch (opcao)
        {
            case 1:
                listar(itens, &contador);
                break;

            case 2:
                ordenar_nome(itens, &contador);
                break;

            case 3:
                ordenar_codigo(itens, &contador);
                break;
            
            case 4:
                int contador = 0;
                inicializar_arquivo(itens, &contador);
                printf("Lista reincializada\n");
                break;
            
            case 5:
                int trocas = 0;
                quicksort_codigo(itens, 0, contador - 1, &trocas);
                printf("\nFoi feito %d trocas\n", trocas);
                printf("Lista ordenada por código\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida\n");
        }

    } while (opcao != 0);
    




    return 0;
}