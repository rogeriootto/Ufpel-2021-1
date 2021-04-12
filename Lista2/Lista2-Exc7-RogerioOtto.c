#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {

    char nome[10];
    int idade;
    int telefone;

} Agenda;

void insere (Agenda *lista, void *pBuffer);
void listar(Agenda *lista, void *pBuffer);
void remover (Agenda *lista, Agenda *ultimo, void *pBuffer);
void buscar (Agenda *lista, void *pBuffer);

int main () {

    void *pBuffer = NULL;
    Agenda lista[10];

    pBuffer = malloc(sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char)) + sizeof(int)); // int sel, tamanho, i, aux[10], flagzinha;//

    *(int*)(pBuffer + sizeof(int)) = 0;

    do {

        printf("\nMenu do Programa\n");
        printf("1) Incluir na agenda;\n");
        printf("2) Remover na agenda;\n");
        printf("3) Buscar na agenda;\n");
        printf("4) Listar na agenda;\n");
        printf("5) Sair;\n");
        scanf("%d", (int*)pBuffer);
        getchar();

        switch (*(int*)pBuffer) {

            case 1:

                insere (&lista[*(int*)(pBuffer + sizeof(int))], pBuffer);

            break;

            case 2:

                remover(lista, &lista[(*(int*)(pBuffer + sizeof(int)))-1], pBuffer);

            break;

            case 3:

                buscar(lista, pBuffer);

            break;

            case 4:

                listar(lista, pBuffer);

            break;

            case 5:

                free(pBuffer);

            return 0;

            break;

            default:
                printf("\nDigite um valor valido;\n");

        }

    }while(*(int*)pBuffer != 5);

}

void insere (Agenda *lista, void *pBuffer) {

    if (*(int*)(pBuffer + sizeof(int)) == 10) {
        printf("\nLista cheia;\n");
    }

    else {

        printf("Insira o nome: \n");
        scanf("%s", lista->nome);
        getchar();

        printf("Insira a idade: \n");
        scanf("%d", &lista->idade);
        getchar();

        printf("Insira o telefone: \n");
        scanf("%d", &lista->telefone);
        getchar();

        *(int*)(pBuffer + sizeof(int)) = *(int*)(pBuffer + sizeof(int)) + 1; // tamanho++;

    }

}

void listar(Agenda *lista, void *pBuffer) {
    
    if(*(int*)(pBuffer + sizeof(int)) == 0) {

        printf("\nNenhum nome na lista\n");

    }
    else {

        for (*(int*)(pBuffer + sizeof(int) + sizeof(int)) = 0 ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) < *(int*)(pBuffer + sizeof(int)) ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) + 1 ) {
            //for i < tamanho//

            if (lista->nome[0] != '\0') {

                printf("\nNome: %s;\n", lista->nome);
                printf("Idade: %d;\n", lista->idade);
                printf("Telefone: %d;\n", lista->telefone);
                lista++;
                
            }

        }
    }

}

void remover (Agenda *lista, Agenda *ultimo, void *pBuffer) {

    if(*(int*)(pBuffer + sizeof(int)) == 0) {

        printf("\nNenhum nome na lista\n");

    }
    else {

        printf("\nDigite o nome a ser removido: \n");
        scanf("%s", (char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int)));
        getchar();

        *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) = 0;

        for (*(int*)(pBuffer + sizeof(int) + sizeof(int)) = 0 ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) < *(int*)(pBuffer + sizeof(int)) ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) + 1 ) {
            //for i < tamanho//
            if (strcmp ((char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int)), lista->nome) == 0) {

                strcpy(lista->nome , ultimo->nome);
                lista->idade = ultimo->idade;
                lista->telefone = ultimo->telefone;

                ultimo->nome[0] = '\0';
                ultimo->idade = -1;
                ultimo->telefone = -1;
                
                *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) = 1;

                *(int*)(pBuffer + sizeof(int)) = *(int*)(pBuffer + sizeof(int)) - 1;

            }
            lista ++;
        }

        if (*(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) == 0) {
            printf("\nNome não encontrado;\n");
        }
    }
    
}

void buscar (Agenda *lista, void *pBuffer) {

    if(*(int*)(pBuffer + sizeof(int)) == 0) {

        printf("\nNenhum nome na lista\n");

    }
    else {

        printf("\nDigite o nome a ser buscado: \n");
        scanf("%s", (char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int)));
        getchar();

        *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) = 0;

        for (*(int*)(pBuffer + sizeof(int) + sizeof(int)) = 0 ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) < *(int*)(pBuffer + sizeof(int)) ; *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) + 1 ) {
            //for i < tamanho//
            if (strcmp ((char*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int)), lista->nome) == 0) {

                printf("\nNome: %s;\n", lista->nome);
                printf("Idade: %d;\n", lista->idade);
                printf("Telefone: %d;\n", lista->telefone);
                
                *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) = 1;

            }
            lista++;
        }

        if (*(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))) == 0) {
            printf("\nNome não encontrado;\n");
        }
    }
    
}