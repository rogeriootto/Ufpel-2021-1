#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void listarVetor ( int *vetor, int nVetor);
int limparVetor(int *vetor);
int verificaOrdem (int *vetor, int nVetor);
void insertionSort(int *p, int n);
void selectionSort (int *vetor, int nVetor);
void quickSort (int *data, int left, int right);
void mergeSort(int *vetor, int start, int end);
void merge (int *vetor, int start, int mid, int end);
float time_diff(struct timeval *start, struct timeval *end);

int main () {

    int nVetor = 0, sel = 0, *vetor, i;
    struct timeval begin, end;
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

                gettimeofday(&begin, NULL);
                insertionSort (vetor, nVetor);
                gettimeofday(&end, NULL);
                listarVetor(vetor, nVetor);
                printf("\nDemorou %f segundos para executar o insertion sort;\n", time_diff(&begin, &end));
                
            break;

            case 2:

                gettimeofday(&begin, NULL);
                selectionSort (vetor, nVetor);
                gettimeofday(&end, NULL);
                listarVetor(vetor, nVetor);
                printf("\nDemorou %f segundos para executar o selection sort;\n", time_diff(&begin, &end));

            break;

            case 3:

                gettimeofday(&begin, NULL);
                quickSort(vetor, 0, nVetor-1);
                gettimeofday(&end, NULL);
                listarVetor(vetor, nVetor);
                printf("\nDemorou %f segundos para executar o quick sort;\n", time_diff(&begin, &end));

            break;

            case 4:

                gettimeofday(&begin, NULL);
                mergeSort(vetor, 0, nVetor-1);
                gettimeofday(&end, NULL);
                listarVetor(vetor, nVetor);
                printf("\nDemorou %f segundos para executar o merge sort;\n", time_diff(&begin, &end));

            break;

            case 5:

                if ( verificaOrdem (vetor, nVetor-1) ) {
                    printf("\nOrdenacao esta correta!\n");
                }
                else {
                    printf("\nOrdenacao esta errada!\n");
                }

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

    int flag = 0, i;

    for (i=0; i < nVetor; i++) {

        if(vetor[i] > vetor[i+1]) {
            flag++;
        }

    }
    if (flag == 0) {
        return 1;
    }
    else {
        return 0;
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

    for (i=0; i < (nVetor-1); i++) {

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

    //pivo = vetor[left + (rand() % right)]; // RANDOM FUNCIONOU NEM ACREDITO; FUNCIONOU PORCARIA NENHUMA;
    pivo = vetor[(left + right)/2];

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

void mergeSort(int *vetor, int start, int end) {

    if (start < end) {

        int mid;

        mid = start + (end - start)/2;

        mergeSort(vetor, start, mid);
        mergeSort(vetor, mid +1, end);

        merge (vetor, start, mid, end);
    }

}

void merge (int *vetor, int start, int mid, int end) {
    
    int *temp, p1, p2, tam, i, j, k;
    int end1 = 0, end2 = 0;
    tam = end-start+1;
    p1 = start;
    p2 = mid +1;

    temp = (int *)malloc(tam * sizeof(int));
    if (temp != NULL) {
        for(i=0; i < tam; i++) {
            if( (!end1) && (!end2) ) {

                if (vetor[p1] < vetor[p2]) {
                    temp[i] = vetor[p1++];
                }
                else {
                    temp[i] = vetor[p2++];
                }

                if(p1>mid) {
                    end1=1;
                }
                if(p2>end) {
                    end2=1;
                }
            }
            else {
                if(!end1) {
                    temp[i] = vetor[p1++];
                }
                else {
                    temp[i] = vetor[p2++];
                }
            }
        }
        for(j=0, k=start; j < tam; j++, k++) {
            vetor[k] = temp[j];
        }
    }

    free (temp);
}
float time_diff(struct timeval *start, struct timeval *end) {

    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}