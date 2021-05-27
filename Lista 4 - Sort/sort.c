#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void listarVetor ( int *vetor, int nVetor);
int limparVetor(int *vetor);
int verificaOrdem (int *vetor, int nVetor);
void insertionSort(int *p, int n);
void selectionSort (int *vetor, int nVetor);
void quickSort (int *data, int left, int right);
void mergeSort();

int main () {

    int nVetor = 0, sel = 0, *vetor, i;
    srand(time(NULL));
    
    do {

        if (nVetor == 0) {
            printf("\nDigite o tamanho do vetor: ");
            scanf("%d", &nVetor);
            getchar();

            vetor = malloc(sizeof(int) * nVetor);
            for (i = 0; i < nVetor; i++) {
                vetor[i] = rand () % 1000;
            }
        }

        printf("\n -- Escolha o metodo de Ordenacao --\n");
        printf("\n1) Insetion Sort;");
        printf("\n2) Selection Sort;");
        printf("\n3) Quick Sort;");
        printf("\n4) Merge Sort;");
        printf("\n5) Verifica Ordenacao;");
        printf("\n6) Listar Vetor;");
        printf("\n7) Limpar Vetor;");
        printf("\n8) Sair;\n");
        scanf("%d", &sel);
        getchar();

        switch (sel) {

            case 1:

                insertionSort (vetor, nVetor);
                listarVetor(vetor, nVetor);

            break;

            case 2:

                selectionSort (vetor, nVetor);
                listarVetor(vetor, nVetor);

            break;

            case 3:

                quickSort(vetor, 0, nVetor-1);
                listarVetor(vetor, nVetor);

            break;

            case 4:

                mergeSort();

            break;

            case 5:

                verificaOrdem (vetor, nVetor);

            break;

            case 6:

                listarVetor(vetor, nVetor);

            break;

            case 7: // Limpar Vetor;

                nVetor = limparVetor(vetor);
                
            break;

            case 8:

                free (vetor);
                return 0;

            break;

            default:
                printf("\nInsira um valor valido;\n");

        }

    }while(sel != 8);

    return 0;

}

void listarVetor ( int *vetor, int nVetor) {

    int i;

    printf("\n");

    for (i = 0; i < nVetor; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");
}

int limparVetor(int *vetor) {

    free(vetor);
    return 0;
}

int verificaOrdem (int *vetor, int nVetor) {
    int i;
    for (i = 0; i < nVetor; i++) {
        
    }

}

void insertionSort(int *vetor, int nVetor) {
    int i, j, temp;

    for (i = 1; i < nVetor; i++) {
        j = i - 1;
        temp = vetor[i];

        while ((j >= 0) && (temp < vetor[j])) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = temp;
    }
}

void selectionSort (int *vetor, int nVetor) {

    int min, temp, i, j, min_id;

    for (i=0; i < nVetor-1; i++) {

        min = vetor[i];

        for(j=i+1; j < nVetor; j++) {
            if (vetor[j] < min) {
                min = vetor[j];
                min_id = j;
            }
        }

        temp = vetor[i];
        vetor[i] = vetor[min_id];
        vetor[min_id] = temp;
        min_id = i+1;

    }
}

void quickSort (int *vetor, int left, int right) {

    int pivo, temp, i, j;
    i = left;
    j = right;

    pivo = vetor[left + (rand() % right)]; // RANDOM FUNCIONOU NEM ACREDITO

    do {

        while ( vetor[i] < pivo ) {
            i++;
        }
        while (pivo < vetor[j]) {
            j--;
        }
        
        if ( i <= j) {
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
            i++;
            j--;
        }

    }while (i <= j);

    if (left < j) {
        quickSort(vetor, left, j);
    }
    if (i < right) {
        quickSort (vetor, i, right);
    }
}

void mergeSort() {

//    if (strlen(m) <= 1) {
//        return m;
//    }

//    int *esquerda, *direita, meio = strlen(m)/2;
}