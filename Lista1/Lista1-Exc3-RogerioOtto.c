#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *incluir (void *pBuffer);
void imprime (void *pBuffer);
void *remover (void *pBuffer);
void buscar (void *pBuffer);

int main () {

    // Variaveis

    void *pBuffer = NULL;
    int sel = 0;

    pBuffer = malloc (sizeof(int)); //int nNomes

    //Teste de memoria
    if (!pBuffer) {
        printf("Erro, nao foi possivel alocar espaco.");
        return -1;
    }

    *(int *)pBuffer = 0; //nNomes = 0

    do {
        
        printf("\nMenu do Programa\n");
        printf("1) Incluir na agenda;\n");
        printf("2) Remover na agenda;\n");
        printf("3) Buscar na agenda;\n");
        printf("4) Listar na agenda;\n");
        printf("5) Sair;\n");
        scanf("%d", &sel);
        getchar();

        switch (sel) {

            // Incluir
            case 1:

                pBuffer = incluir(pBuffer);

            break;

            // Remover
            case 2:

                pBuffer = remover(pBuffer);

            break;

            case 3:

                buscar (pBuffer);

            break;

            // Imprimir
            case 4:

                imprime (pBuffer);

            break;

            // Sair
            case 5:
            
                free (pBuffer);
                return 0;

            break;

            default:
                printf("Insira um valor valido!\n");

        }

    } while (sel != 5);

    return 0;

}

void *incluir (void *pBuffer) {

    pBuffer = realloc(pBuffer, sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int))  * ((*(int*)pBuffer) + 1))); // nNomes + nome[10] + idade + telefone; o +1 pq nNomes n pode começar em zero;

    //Teste de memoria
    if (!pBuffer) {
        printf("Erro, nao foi possivel alocar espaco.");
        return NULL;
    }

    printf("\nInsira um nome: \n");
    scanf("%s", (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer)));   // scanf do nome[10];
    getchar();

    printf("Insira a Idade: \n");
    scanf("%d", (int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer)))); // scanf da idade
    getchar();

    printf("Insira o Telefone: \n");
    scanf("%d", (int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)pBuffer)))); // scanf do telefone
    getchar();

    *(int *)(pBuffer) = *(int *)(pBuffer) + 1; // nNomes ++

    return pBuffer;
    
}

void imprime (void *pBuffer) {

    int i;
    if (*(int*)pBuffer == 0) {

        printf("Lista Vazia\n");

    }
    else {
        
        for(i = 0; i < *(int*)(pBuffer) ; i++) {

            printf("\nNome: %s;\n", (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
            printf("Idade: %d;\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
            printf("Telefone: %d;\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));

        }
    }
}

void *remover (void *pBuffer) {

    if (*(int*)(pBuffer) == 0) {

        printf("Agenda vazia, por favor insira algo nela.");
        return pBuffer;

    }

    else {

        // Variaveis
        char aux[10];
        int i;

        printf("\nDigite o nome a ser removido: \n");
        scanf("%s", aux);
        getchar();

        for(i = 0 ; i < *(int*)pBuffer ; i++) {

            if (strcmp((char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i), aux) == 0) {
                
                strcpy((char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i) , (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer)-1)));
                *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) = *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer) - 1)));
                *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) = *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int*)(pBuffer) - 1)));
                *(int *)pBuffer = *(int *)pBuffer - 1;
                pBuffer = realloc(pBuffer, sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int))  * ((*(int*)pBuffer))));

                //Teste de memoria
                if (!pBuffer) {
                    printf("Erro, nao foi possivel alocar espaco.");
                    return NULL;
                }

                return pBuffer;
            }
        }
            printf("\nNome pesquisado não foi encontrado;\n");
    }
    return pBuffer;
}

void buscar (void *pBuffer) {

    if (*(int*)(pBuffer) == 0) {

        printf("Agenda vazia, por favor insira algo nela.\n");

    }

    else {

        // Variaveis
        char aux[10];
        int i, flag = 0;

        printf("\nDigite o nome a ser buscado: \n");
        scanf("%s", aux);
        getchar();

        for(i = 0 ; i < *(int*)pBuffer ; i++) {

            if (strcmp((char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i), aux) == 0) {

                printf("\nNome: %s;\n", (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
                printf("Idade: %d;\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
                printf("Telefone: %d;\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
                flag++;

            }
        }

        if (flag == 0) {
            printf("\nNome pesquisado não foi encontrado;\n");
        }
    }
}