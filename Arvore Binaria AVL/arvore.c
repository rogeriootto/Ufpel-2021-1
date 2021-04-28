#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {

    int chave;
    int dado;

} Registro;


typedef struct No {

    Registro reg;
    struct No *pEsq;
    struct No *pDir;

}No;
int insere (No **ppRaiz, Registro reg);
void registrarDado (Registro *reg, int random);
void registrarChave (Registro *reg, int i);
No *criaNodo(void);

int main () {

    srand(time(NULL)); // Gera numeros aleatórios não repetidos
    int i, random, nNodos;
    No *pRaiz = NULL;
    Registro reg;

    printf("Digite o numero de nodos: ");
    scanf("%d", &nNodos);
    getchar();
    
    for (i=0; i < nNodos; i++){
        
        random = rand()%1000; // Gerando valores aleatórios na faixa de 0 a 1000
        printf("%d ", random);

        registrarDado(&reg, random); //Registra o i como dado para ver a ordem de inserção dps (acho)
        registrarChave(&reg, i); //Registra a chave com a posição na arvore

        insere(&pRaiz, reg); //Insere o numero na arvore

    }

}
No *criaNodo(void) {
    No *nNodo = NULL;

    nNodo = (No*)malloc(sizeof(No));

    nNodo->pEsq = NULL;
    nNodo->pDir = NULL;

    return nNodo;
}

int insere (No **ppRaiz, Registro reg) {

    if (*ppRaiz == NULL) { // Se é uma folha ele insere

        *ppRaiz = criaNodo();
        (*ppRaiz)->reg = reg;
        return 1;

    }
    else if ((*ppRaiz)->reg.chave > reg.chave) {

        if ( insere (&(*ppRaiz), reg) ) {

            if (balanceamento(ppRaiz)) {
                return 0;

            }
            else {
                return 1;

            }
        }
    }
    else {
        return 0; // Valor já esta presente
    }
}

void registrarDado (Registro *reg, int random) {
    reg->dado = random;
}

void registrarChave (Registro *reg, int i) {
    reg->chave = i + 1;
}

int FB (No *pRaiz) {
    if (pRaiz == NULL) {
        return 0;
    }

    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

int Altura (No *pRaiz) {

    int iEsq, iDir;

    if (pRaiz == NULL) {
        return 0;
    }

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if (iEsq > iDir){
        return iEsq + 1;
    }
    else {
        return iDir + 1;
    }
}