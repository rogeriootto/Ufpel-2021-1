#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listar(char *nome);
char *adiciona(char *nome);
char *remover(char *listaNomes);

int main () {

    //Variaveis
    int select;
    char *nome = NULL;

    do {

        // Menu
        printf ("\nMenu do Programa:\n\n");
        printf ("1) Adicionar Nome;\n");        
        printf ("2) Remover Nome;\n");        
        printf ("3) Listar;\n");        
        printf ("4) Sair;\n");

        printf ("Entrada: ");
        scanf ("%d", &select);
        getchar();
        printf ("\n"); 

        switch (select){

            // Adiciona o nome
            case 1:

                nome = adiciona(nome);
   
            break;

            // Remove o nome
            case 2:

                nome = remover(nome);

            break;

            // Lista
            case 3:

                listar(nome);
                
            break;

            // Sai do programa
            case 4:

                // Libera a memoria
                free(nome);
                return 0;
                
            break;

            // Algo inesperado
            default:
                printf("Por favor digite um valor válido\n");
        }

    } while (select != 4);
}


void listar(char *nome) {

    if(!nome) {

        printf("lista esta vazia.\n");    
    }

    else {

        printf("\n");

        while(*nome) {  // Roda até NULL
                
        if (*nome == ';') { // Se achar ponto e virgula, ele quebra uma linha
            printf("\n");
            nome++;
        }

        else {      // Printa letra por letra
            printf("%c",*nome++);
        }

        }
        printf("\n");
    }
}

char *adiciona(char *string) {

    // Variaveis
    int tamanho = 0, total;
    char *temp = NULL;

    temp = (char*)malloc(sizeof(char) * 100);   // Cria uma string para salvar o nome a ser adicionado

    printf("Digite o nome:\n");
    scanf("%s",temp);
    getchar();
        
    tamanho = strlen(temp);     // Pega o tamanho do nome a ser adicionado
    temp[tamanho] = ';';        // Coloca um ponto e virgula
    temp[tamanho + 1] = '\0';   // Coloca o \0 depois do ponto e virgula
    tamanho = tamanho + 2;      // Tamanho vai ser o tamanho do nome mais o ponto e virgula mais o \0

    if(!string) {

        string = (char *)malloc(sizeof(char) * tamanho);

        //Teste de memoria
        if (!string) {
            printf("Erro, nao foi possivel alocar espaco.");
            return NULL;
        }

        strcpy(string, temp);

    }
    else {

        total = strlen (string);        
        string = (char *) realloc(string, total = (tamanho + total));

        // Teste de memoria
        if (!string) {
            printf("Erro, nao foi possivel alocar espaco.");
            return NULL;
        }
        // Concatena a string da lista com o nome a ser adicionado
        strncat (string, temp, total); 

    }

    free(temp);
    return string;
    
}

char *remover(char *string) {

    if(!string) {

        printf("Lista esta vazia.\n");
        return string;

    }

    else {
    
        // Variaveis
        unsigned int tamanhoLista = strlen(string), tamanhoNomeAux, novoTamanho = 0, tamanhoListaAux = 0, limpaLista, i, flag = 0;
        char *listaNomesAux = NULL, *temp = NULL, aux[50];

        temp = (char*)malloc(sizeof(char) * 100);
        
        // Teste de memoria
        if (!temp) {
            printf("Erro, nao foi possivel alocar espaco.");
            return NULL;
        }

        printf("Digite o nome para remover: ");
        scanf("%s", temp);

        for (i = 0; i < tamanhoLista; i++) {  // Percorre a Lista

            limpaLista = 0;

            while(string[i] != ';') {   // Percorre a Lista e salva um nome em aux
                aux[limpaLista++] = string[i++];
            }

            aux[limpaLista] = '\0';  // Coloca o \0 no fim da string do nome salvo

            tamanhoNomeAux = strlen(aux);   //Pega o tamanho do nome salvo

            if (strcmp(temp, aux) != 0) {    //Compara se o nome recebido pelo usuario é o nome em aux

                if (!listaNomesAux) {   // Caso seja a primeira vez passando por esse if, ele faz um malloc para a string q vai armazenar os nomes que irão ficar

                    novoTamanho = tamanhoNomeAux + 2;  // Tamanho para a string nova, o +2 é para inserir o ponto e virgula mais o \0
                    listaNomesAux = (char*)malloc(novoTamanho * sizeof(char));

                    // Teste de memoria
                    if (!listaNomesAux) {
                        printf("Erro, nao foi possivel alocar espaco.");
                        return NULL;
                    }

                    strcpy(listaNomesAux, aux);     // Concatena o nome na string nova
                    strcat(listaNomesAux,";");      //Adiciona o ponto e virgula para separar os nomes

                } 
                else {      // Caso seja a segunda vez passando na repetição

                    novoTamanho = tamanhoListaAux + tamanhoNomeAux + 2;     // Tamanho para a string nova, o +2 é para inserir o ponto e virgula mais o \0

                    listaNomesAux = (char*)realloc(listaNomesAux, novoTamanho * sizeof(char));

                    // Teste de memoria
                    if (!listaNomesAux) {
                        printf("Erro, nao foi possivel alocar espaco.");
                        return NULL;
                    }

                    strcat (listaNomesAux, aux);    // Concatena o nome na string nova
                    strcat (listaNomesAux, ";");    // Adiciona o ponto e virgula para separar os nomes

                }

                tamanhoListaAux = novoTamanho;      // Salva o novo tamanho para não se perder no loop
            }
            else {

                flag++;

            }
        }

        if(flag==0) {

            printf("Nome nao foi encontrado.\n");
            free(listaNomesAux);
            free (temp);
            return string;

        }
        else {

            string = (char*)realloc(string, tamanhoListaAux * sizeof(char));

            if(listaNomesAux==NULL) {

                free(listaNomesAux);
                free (temp);
                return NULL;

            }
            else {

                strcpy(string, listaNomesAux);
                free(listaNomesAux);
                free (temp);
                return string;

            }
        }
    }
}