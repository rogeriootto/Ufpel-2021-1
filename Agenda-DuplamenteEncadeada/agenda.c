#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{

    char nome[10];
    int idade, telefone;
    struct No *next;
    struct No *previous;

} No;

typedef struct {

    No *start;
    No *end;

}Lista;

void insere (Lista *lista, void *pBuffer);
void remover (Lista *lista, void *pBuffer);
void buscar (Lista *lista, void *pBuffer);
void listar (Lista *lista, void *pBuffer);
void freeLista (Lista *lista);

int main () {

    void *pBuffer = NULL;

    pBuffer = malloc(sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))); 
    // 0 - Int para laços (int i)
    // 1 - Int para o Switch case
    // 2 - Int Tamanho da lista
    // 3 - String auxiliar para buscar e remover

    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = 0;
    //tamanho = 0

    Lista lista;
    lista.start = NULL;
    lista.end = NULL;

    do {

        printf("\n--Menu do Programa--\n");
        printf("1- Inserir na lista;\n");
        printf("2- Remove da lista;\n");
        printf("3- Buscar na lista\n");
        printf("4- Listar a lista;\n");
        printf("5- Ordenar a lista;\n");
        printf("6- Sair;\n\n");
        scanf("%d", (int*)(pBuffer + sizeof(int)));
        getchar();

        switch (*(int*)(pBuffer + sizeof(int))) {

            case 1:

                insere(&lista, pBuffer); //insere no fim da lista

            break;

            case 2:

                remover(&lista, pBuffer);

            break;

            case 3:

                buscar (&lista, pBuffer);

            break;

            case 4:

                listar(&lista, pBuffer);

            break;

            case 5:

            break;

            case 6:

                freeLista(&lista);
                free(pBuffer);
                return 0;

            break;

            default:
                printf("\nDigite um valor valido;\n");

        }

    }while(*(int*)pBuffer != 6);

    return 0;

}

void insere (Lista *lista, void *pBuffer) {

    No *pNovo;
    pNovo = (No*)malloc(sizeof(No));

    pNovo->next = NULL;
    pNovo->previous = NULL;

    printf("\n--Inserindo na lista--\n");

    printf("Insira o nome: ");
    scanf("%s", pNovo->nome);
    getchar();

    printf("Insira a idade: ");
    scanf("%d", &pNovo->idade);
    getchar();

    printf("Insira o telefone: ");
    scanf("%d", &pNovo->telefone);

    if (lista->start == NULL) {

        lista->start = pNovo;

    }
    else {

        lista->end->next = pNovo;
        pNovo->previous = lista->end;

    }

    lista->end = pNovo;

    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) + 1;
    //tamanho++;

}

void remover (Lista *lista, void *pBuffer) {

    if (lista->start == NULL) {

        printf("\nLista vazia;\n");

    }
    else {

        No *pStart = lista->start;

        printf("\nDigite o nome a ser removido: ");
        scanf("%s", (char*)pBuffer + sizeof(int) + sizeof(int) + sizeof(int));
        getchar();

        while(pStart != NULL) {

            if(strcmp(pStart->nome, (char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int))) == 0) {
                
                //Testa se é o primeiro elemento da lista
                if(pStart->previous == NULL) {

                    if(pStart->next == NULL) { // Unico da lista

                        lista->start = NULL;
                        lista->end = NULL;

                        free(pStart);

                        *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) - 1;
                        //tamanho--

                        return;

                    }
                    else { //Primeiro da lista

                        pStart->next->previous = NULL;
                        lista->start = pStart->next;

                        free(pStart);

                        *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) - 1;
                        //tamanho--

                        return;

                    }

                }
                else if (pStart->next != NULL) { //Testa se ta no meio da lista

                    pStart->previous->next = pStart->next;
                    pStart->next->previous = pStart->previous;

                    free(pStart);

                    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) - 1;
                    //tamanho--

                    return;

                }
                else { //Testa se é o ultimo elemento da lista

                    pStart->previous->next = NULL;
                    lista->end = pStart->previous;

                    free(pStart);

                    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) - 1;
                    //tamanho--

                    return;
                }
                
            }

            pStart = pStart->next;
        }
    }
}

void buscar (Lista *lista, void *pBuffer) {

    if (lista->start == NULL) {
        
        printf("\nLista vazia;\n");

    }
    else {

        No *pStart = lista->start;

        printf("\nDigite o nome a ser buscado: ");
        scanf("%s", (char*)pBuffer + sizeof(int) + sizeof(int) + sizeof(int));
        getchar();

        while(pStart != NULL) {

            if(strcmp(pStart->nome, (char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int))) == 0) {

                printf("\nNome: %s;\n", pStart->nome);
                printf("Idade: %d;\n", pStart->idade);
                printf("Telefone %d;\n", pStart->telefone);

            }

            pStart = pStart->next;
        }
    }
}

void listar (Lista *lista, void *pBuffer) {

    if (lista->start == NULL) {

        printf("\nLista vazia;\n");
        
    }
    else {

        No *pStart = lista->start;

        while(pStart != NULL) {

            printf("\nNome: %s;\n", pStart->nome);
            printf("Idade: %d;\n", pStart->idade);
            printf("Telefone %d;\n", pStart->telefone);

            pStart = pStart->next;
        }
        printf("\n%d Pessoas na Lista;\n", *(int*)(pBuffer + sizeof(int) + sizeof(int)));
    }
}

void freeLista (Lista *lista) {

    No *auxiliar, *p;

    p = lista->start;

    while (p != NULL ) {

        auxiliar = p;
        p = p->next;

        free(auxiliar);
    }
}