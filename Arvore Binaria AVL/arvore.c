#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {

    int chave;

} Registro;


typedef struct No {

    Registro reg;
    struct No *pEsq;
    struct No *pDir;

}No;

//Funções de "Inserção"
int insere (No **ppRaiz, Registro reg);
void registrarChave (Registro *reg);
void listarArvore (No *pRaiz);
No *criaNodo(void);
void limparArvore (No *pRaiz);

//BALANCEAMENTO
int balanceamento(No **ppRaiz);
int balancaEsquerda (No **ppRaiz);
int balancaDireita (No **ppRaiz);
void RSE (No **ppRaiz);
void RSD (No **ppRaiz);
int FB (No *pRaiz);
int altura (No *pRaiz);
int verificaAVL (No *pRaiz);


int main () {

    int i, nNodos;
    No *pRaiz = NULL;
    Registro reg;

    printf("Digite o numero de nodos: ");
    scanf("%d", &nNodos);
    getchar();
    
    for (i=0; i < nNodos; i++){
        
        registrarChave(&reg);
        insere(&pRaiz, reg); //Insere o numero na arvore

    }
    printf("\n");
    listarArvore(pRaiz);
    printf("\n");

    if(verificaAVL(pRaiz)) {
        printf("\nA arvore eh AVL\n");
    }
    else {
        printf("\nNao eh AVL\n");
    }

    

    limparArvore(pRaiz);

    return 0;

}

void registrarChave (Registro *reg) {

    int random;

    srand(time(0)); // Gera numeros aleatórios não repetidos
    
    random = rand()%1000;
    printf("%d, ", random);
    reg->chave = random;

}

void limparArvore (No *pRaiz) {
    if (pRaiz == NULL) {
        return;
    }

    limparArvore(pRaiz->pEsq);
    limparArvore(pRaiz->pDir);

    free(pRaiz);
}

void listarArvore (No *pRaiz) {

    if (pRaiz != NULL) {
        printf("%d(", pRaiz->reg.chave);
        listarArvore(pRaiz->pEsq);
        listarArvore(pRaiz->pDir);
        printf(")");
    }

}

No *criaNodo(void) {
    No *nNodo = NULL;

    nNodo = (No*)malloc(sizeof(No));

    if (!nNodo) {
        printf("\nAlgum erro ao alocar a memoria\n");
        exit(1);
    }

    nNodo->pEsq = NULL;
    nNodo->pDir = NULL;

    return nNodo;
}

int insere (No **ppRaiz, Registro nReg) {

    if (*ppRaiz == NULL) {

        *ppRaiz = criaNodo();
        (*ppRaiz)->reg = nReg;

        return 1;
    }
    else if ( nReg.chave < (*ppRaiz)->reg.chave ) {

        if ( insere( &(*ppRaiz)->pEsq, nReg ) ){
            if (balanceamento(ppRaiz)) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    else if ( nReg.chave > (*ppRaiz)->reg.chave) {
        if ( insere (&(*ppRaiz)->pDir, nReg) ) {
            if (balanceamento(ppRaiz)) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    else {
        return 0;
    }

    return 0;
}

//-----------------------FUNÇÕES DE BALANCEAMENTO-----------------------//

int FB (No *pRaiz) {
    if (pRaiz == NULL) {
        return 0;
    }

    return altura(pRaiz->pEsq) - altura(pRaiz->pDir);
}

int altura (No *pRaiz) {

    int iEsq, iDir;

    if (pRaiz == NULL) {
        return 0;
    }

    iEsq = altura(pRaiz->pEsq);
    iDir = altura(pRaiz->pDir);

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

    No *pAux = NULL;

    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;

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

    No *pAux = NULL;

    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = (*ppRaiz)->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;

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