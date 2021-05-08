#include <stdio.h>
#include <stdlib.h>

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
int remover (No **ppRaiz, int dado);

//BALANCEAMENTO
int balanceamento(No **ppRaiz);
int balancaEsquerda (No **ppRaiz);
int balancaDireita (No **ppRaiz);
void RSE (No **ppRaiz);
void RSD (No **ppRaiz);
int FB (No *pRaiz);
int altura (No *pRaiz);
int verificaAVL (No *pRaiz);
No *procuraNoMenor (No *atual);


int main () {

    int sel = 0, nRemove = 0;
    No *pRaiz = NULL;
    Registro reg;

    do {

        printf("\n--Menu do Programa--\n");
        printf("1) Inserir nodo na arvore;\n");
        printf("2) Remover nodo da arvore;\n");
        printf("3) Listar Arvore;\n");
        printf("4) Testar se a arvore eh AVL;\n");
        printf("5) Sair;\n");

        scanf("%d", &sel);
        getchar();

        switch (sel) {

            case 1:

                registrarChave(&reg);
                insere(&pRaiz, reg); //Insere o numero na arvore

            break;

            case 2:

                printf("\nDigite o valor a ser removido: ");
                scanf("%d", &nRemove);
                getchar();

                remover(&pRaiz, nRemove);

            break;

            case 3:

                listarArvore(pRaiz);

            break;
            
            case 4:

                if(verificaAVL(pRaiz)) {
                    printf("\nA arvore eh AVL\n");
                }
                else {
                    printf("\nNao eh AVL\n");
                }

            break;

            case 5:

                limparArvore(pRaiz);
                return 0;

            break;

            default:
                printf("Digite um valor valido;\n");

        }
    }while(sel != 5);

    limparArvore(pRaiz);
    return 0;

}

void registrarChave (Registro *reg) {

    printf("\nDigite o dado a ser inserido: ");
    scanf("%d", &reg->chave);
    getchar();

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
    printf("\n");
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

int remover (No **ppRaiz, int dado) {
    int resposta;
    if (*ppRaiz == NULL) { // Arvore Vazia
        return 0;
    }
    else if ( dado < (*ppRaiz)->reg.chave){
        if ( (resposta = remover ( &(*ppRaiz)->pEsq, dado)) == 1) {
            if (FB((*ppRaiz)) >= 2) {
                if(altura((*ppRaiz)->pDir->pEsq) <= altura ((*ppRaiz)->pDir->pDir)) {

                    // Rotação simples a Esquerda
                    RSE (&(*ppRaiz)); 
                }
                else {
                    
                    // Rotação dupla a Esquerda
                    RSD ( &((*ppRaiz)->pDir) ); 
                    RSE (ppRaiz);

                }
            }
        }
    }
    else if (( dado > (*ppRaiz)->reg.chave)) {
        if ( (resposta = remover ( &(*ppRaiz)->pEsq, dado)) == 1) {
            if (FB((*ppRaiz)) >= 2) {
                if(altura((*ppRaiz)->pEsq->pDir) <= altura ((*ppRaiz)->pEsq->pEsq)) {

                    // Rotação simples a Direita
                    RSD(ppRaiz); 
                }
                else {

                    // Rotação dupla a Direita
                    RSE ( &((*ppRaiz)->pEsq) ); 
                    RSD (ppRaiz);

                }
            }
        }
    }
    else if (( dado == (*ppRaiz)->reg.chave)) {
        if ((*ppRaiz)->pEsq == NULL || (*ppRaiz)->pDir == NULL) {
            No *oldNode = (*ppRaiz);
            if ((*ppRaiz)->pEsq != NULL) {
                *ppRaiz = (*ppRaiz)->pEsq;
            }
            else {
                *ppRaiz = (*ppRaiz)->pDir;
            }
            free(oldNode);
        }
        else {
            No *temp = procuraNoMenor((*ppRaiz)->pDir);
            (*ppRaiz)->reg.chave = temp->reg.chave;
            remover(&(*ppRaiz)->pDir, (*ppRaiz)->reg.chave);
            if (FB((*ppRaiz)) >= 2) {
                if(altura((*ppRaiz)->pEsq->pDir) <= altura((*ppRaiz)->pEsq->pEsq)) {

                    RSD(ppRaiz);

                }
                else {

                    RSE ( &((*ppRaiz)->pEsq) );
                    RSD (ppRaiz);

                }
            }
        }
        return 1;
    }
    return resposta;
}

//-----------------------FUNÇÕES DE BALANCEAMENTO-----------------------//

No *procuraNoMenor (No *atual) {
    No *no1 = atual;
    No *no2 = atual->pEsq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->pEsq;
    }
    return no1;
}

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

void RSE (No **ppRaiz) { 

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
    else if (fbd > 0) { 

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