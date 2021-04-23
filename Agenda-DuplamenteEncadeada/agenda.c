#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{

    char nome[10];
    int idade, telefone;

    struct No *next;
    struct No *previous;

} No;

typedef struct Ward{

    No *start;
    No *end;

}Ward;

void insere (Ward *lista, void *pBuffer);
void remover (Ward *lista, void *pBuffer);
void buscar (Ward *lista, void *pBuffer);
void listar (Ward *lista, void *pBuffer);
void listarOrdenada (Ward *lista, void *pBuffer);
Ward *criaWard (void);
void freeLista (Ward *lista);
void ordenaMenu (Ward *lista, void *pBuffer);
void ordenaIdadeCrescente (Ward *lista, void *pBuffer);
void ordenaIdadeDecrescente (Ward *lista, void *pBuffer);
void PUSH (Ward *lista, No *NoOriginal, void *pBuffer);
void POP (No *pStart);


int main () {

    void *pBuffer = NULL;

    pBuffer = malloc(sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int) + sizeof(int)); 
    // 0 - Salva o menor valor
    // 1 - Int para o Switch case
    // 2 - Int Tamanho da lista
    // 3 - String auxiliar para buscar e remover
    // 4 - Switch case do menu ordenar
    // 5 - Salva o ultimo menor valor

    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = 0;
    //tamanho = 0

    Ward *lista = NULL;
    lista = criaWard();

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

                insere(lista, pBuffer); //insere no fim da lista

            break;

            case 2:

                remover(lista, pBuffer);

            break;

            case 3:

                buscar (lista, pBuffer);

            break;

            case 4:

                listar(lista, pBuffer);

            break;

            case 5:

                ordenaMenu(lista, pBuffer);
                
            break;

            case 6:

                freeLista(lista);
                free(pBuffer);
                return 0;

            break;

            default:
                printf("\nDigite um valor valido;\n");

        }

    }while(*(int*)(pBuffer + sizeof(int)) != 6);

    return 0;

}

void ordenaMenu (Ward *lista, void *pBuffer) {

    if(lista->start == NULL) {
        printf("\nLista vazia;\n");
        return;
    }

    printf("\n\t--Menu de Ordenação--\n");
    printf("\t1- Ordenar Idade, ordem crescente;\n");
    printf("\t2- Ordenar Idade, ordem decrescente;\n");
    printf("\t3- Voltar ao menu principal;\n");
    scanf("%d", (int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))));
    getchar();

    switch (*(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char)))) {

        case 1:
            printf("Cheguei aqui case menu\n");
            ordenaIdadeCrescente (lista, pBuffer);

        break;

        case 2:

            ordenaIdadeDecrescente (lista, pBuffer);

        break;

        case 3:
            return;
        break;

        default:
            printf("\nValor digitado invalido, voltando para o menu principal;\n");
    }
}

void ordenaIdadeCrescente (Ward *lista, void *pBuffer) {

    printf("Cheguei aqui ordena\n");

    Ward *ordenalista = NULL;
    ordenalista = criaWard(); 

    No *auxi, *auxj, *auxk;

    // GRANDÃO
    *(int*)(pBuffer) = -1; // Para pegar o primeiro menor valor, valor maximo de um int
   
    for (auxi = lista->start; auxi != NULL; auxi = auxi->next) {
        // Pinei um valor e vou testar

        //NUMERO PEQUENO
        *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int)) = 2147483647; // Inicializa com um valor mt pequeno para os testes
        
        for(auxj = lista->start; auxj != NULL; auxj = auxj->next) { 

            if (auxj->idade > *(int*)(pBuffer) && auxj->idade < *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int))) { 
            // Esse && serve para não ler valores iguais ou menores do que ja foram testados
                *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int)) = auxj->idade; // Salva o menor valor
            }   
        }

        *(int*)(pBuffer) = *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int));  
            // Iguala pois no proximo loop ele não pode ser menor que esse valor que já foi testado

        for(auxk = lista->start; auxk != NULL; auxk = auxk->next) { //Insere todos com o valor igual o menor valor
            if(auxk->idade == *(int*)(pBuffer)){
                PUSH(ordenalista, auxk, pBuffer);
            }
        }
    }

    listarOrdenada(ordenalista, pBuffer);
}

void ordenaIdadeDecrescente (Ward *lista, void *pBuffer) {

    printf("Cheguei aqui ordena\n");

    Ward *ordenalista = NULL;
    ordenalista = criaWard(); 

    No *auxi, *auxj, *auxk;

    // GRANDÃO
    *(int*)(pBuffer) = 2147483647; // Para pegar o primeiro menor valor, valor maximo de um int
   
    for (auxi = lista->start; auxi != NULL; auxi = auxi->next) {
        // Pinei um valor e vou testar

        //NUMERO PEQUENO
        *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int)) = -1; // Inicializa com um valor mt pequeno para os testes
        
        for(auxj = lista->start; auxj != NULL; auxj = auxj->next) { 

            if (auxj->idade < *(int*)(pBuffer) && auxj->idade > *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int))) { 
            // Esse && serve para não ler valores iguais ou menores do que ja foram testados
                *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int)) = auxj->idade; // Salva o menor valor
            }   
        }

        *(int*)(pBuffer) = *(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char))+ sizeof(int));  
            // Iguala pois no proximo loop ele não pode ser menor que esse valor que já foi testado

        for(auxk = lista->start; auxk != NULL; auxk = auxk->next) { //Insere todos com o valor igual o menor valor
            if(auxk->idade == *(int*)(pBuffer)){
                PUSH(ordenalista, auxk, pBuffer);
            }
        }
    }

    listarOrdenada(ordenalista, pBuffer);
}

void PUSH (Ward *lista, No *NoOriginal, void *pBuffer) {

    printf("Cheguei aqui ordena\n");
    No *pNovo = NULL;
    pNovo = (No*)malloc(sizeof(No));
    pNovo->next = NULL;
    pNovo->previous = NULL;

    strcpy(pNovo->nome, NoOriginal->nome);
    pNovo->idade = NoOriginal->idade;
    pNovo->telefone = NoOriginal->telefone;

    if (lista->start == NULL) {
        lista->start = pNovo;
    }
    else {
        pNovo->previous = lista->end;
        lista->end->next = pNovo;
    }

    lista->end = pNovo;
}

void listarOrdenada (Ward *lista, void *pBuffer){

    if (lista->start == NULL) {

        printf("\nLista vazia;\n");
        
    }
    else {

        No *pStart = lista->start, *aux;

        while(pStart != NULL) {

            aux = pStart->next;
            POP (pStart);
            pStart = aux;

        }
        free(lista);
    }

}

void POP (No *pStart) {

    printf("\nNome: %s;\n", pStart->nome);
    printf("Idade: %d;\n", pStart->idade);
    printf("Telefone %d;\n", pStart->telefone);
    free(pStart);
    
}

void insere (Ward *lista, void *pBuffer) {

    No *pNovo = NULL;
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
    getchar();

    if (lista->start == NULL) {
        lista->start = pNovo;

    }
    else {
        
        pNovo->previous = lista->end;
        lista->end->next = pNovo;
        
    }

    lista->end = pNovo;

    *(int*)(pBuffer + sizeof(int) + sizeof(int)) = *(int*)(pBuffer + sizeof(int) + sizeof(int)) + 1;
    //tamanho++;

}

void remover (Ward *lista, void *pBuffer) {

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

void buscar (Ward *lista, void *pBuffer) {

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

void listar (Ward *lista, void *pBuffer) {

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

Ward *criaWard(void) {

    Ward *lista;

    lista = (Ward*)malloc(sizeof(Ward));
    
    lista->start = NULL;
    lista->end = NULL;

    return lista;

}

void freeLista (Ward *lista) {

    No *auxiliar, *p;

    p = lista->start;

    while (p != NULL ) {

        auxiliar = p;
        p = p->next;

        free(auxiliar);
    }
    free(lista);
}