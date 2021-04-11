#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char nome[30];
    int idade;
    int altura;

} Pessoa;

Pessoa *insere (Pessoa *lista, int tamanho);
void imprime (Pessoa *lista, int tamanho);

int main () {

    Pessoa *lista = NULL;
    int sel, tamanho = 0;


    do {

        printf("\nMenu do programa:\n");
        printf("1) Adicionar pessoa;\n");
        printf("2) Imprimir e sair;\n");
        scanf("%d", &sel);

        switch (sel) {

            case 1:

                lista = insere(lista, tamanho);
                tamanho = tamanho + 1;

            break;

            case 2:

                imprime(lista, tamanho);
                free(lista);
                return 0;

            break;

            default:
                printf("Digite um valor valido;\n");
        }

    }while(sel != 2);
    
}

Pessoa *insere (Pessoa *lista, int tamanho) {

    if (tamanho == 0){
        
        lista = malloc(sizeof(Pessoa));

        printf("Insira o nome: \n");
        scanf("%s", lista[tamanho].nome);
        getchar();

        printf("Insira a idade: \n");
        scanf("%d", &lista[tamanho].idade);
        getchar();

        printf("Insira a altura: \n");
        scanf("%d", &lista[tamanho].altura);
        getchar();

        return lista;

    }
    else {

        lista = realloc(lista, (sizeof(Pessoa) * (tamanho + 1)));

        printf("Insira o nome: \n");
        scanf("%s", lista[tamanho].nome);
        getchar();

        printf("Insira a idade: \n");
        scanf("%d", &lista[tamanho].idade);
        getchar();      

        printf("Insira a altura: \n");
        scanf("%d", &lista[tamanho].altura);
        getchar();

        return lista;

    }

    return lista;

}

void imprime (Pessoa *lista, int tamanho) {

    int i;

    for (i = 0 ; i < tamanho ; i++) {
        printf("\nNome: %s;\n", lista[i].nome);
        printf("Idade: %d;\n", lista[i].idade);
        printf("Altura: %d;\n", lista[i].altura);
    }
}