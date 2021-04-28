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

//Funções de "Inserção"
int insere (No **ppRaiz, Registro reg);
void registrarChave (Registro *reg, int i);
No *criaNodo(void);

//BALANCEAMENTO
int balanceamento(No **ppRaiz);
int balancaEsquerda (No **ppRaiz);
int balancaDireita (No **ppRaiz);
void RSE (No **ppRaiz);
void RSD (No **ppRaiz);
int FB (No *pRaiz);
int Altura (No *pRaiz);


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

        registrarChave(&reg, random); //Registra a chave com a posição na arvore

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

void registrarChave (Registro *reg, int random) {
    reg->chave = random;
}


//-----------------------FUNÇÕES DE BALANCEAMENTO-----------------------//

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

int balanceamento(No **ppRaiz) {

    int fb;
    fb = FB(*ppRaiz);
    if (fb > 1) {
        return balancaEsquerda(ppRaiz);

    }
    else if (fb < -1){
        return balancaDireita(ppRaiz);

    }
    else {
        return 0;
    }

}

int balancaEsquerda (No **ppRaiz) {

    int fbe;
    fbe = FB( (*ppRaiz)->pEsq );

    if (fbe > 0) {

        RSD(ppRaiz);

        return 1;

    }
    else if (fbe < 0) { // Rotação dupla para a Direita

        RSE ( &((*ppRaiz)->pEsq) );
        RSD (ppRaiz);

        return 1;

    }
    return 0;
}

void RSE (No **ppRaiz) { // ROTAÇÃO SIMPLES PARA DIREITA

    No *pAux;

    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
    return;

}

int balancaDireita (No **ppRaiz) {

    int fbd;
    fbd = FB( (*ppRaiz)->pDir );
    
    if (fbd < 0) {

        RSE (ppRaiz);

        return 1;
    }
    else if (fbd > 0) { // ROTAÇÃO SIMPLES PARA ESQUERDA

        RSD ( &((*ppRaiz)->pDir) );
        RSE (ppRaiz);

        return 1;
    }
    return 0;

}

void RSD (No **ppRaiz) {

    No *pAux;

    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
    return;

}

int verificaAVL (No *pRaiz) {

    int fb;

    if (pRaiz == NULL) {
        return 1;
    }

    if (!verificaAVL(pRaiz->pEsq)) {
        return 0;
    }

    if (!verificaAVL(pRaiz->pDir)) {
        return 0;
    }

    fb = FB (pRaiz);

    if ( (fb > 1) || (fb < -1) ) {
        return 0;

    }
    else {
        return 1;

    }
}