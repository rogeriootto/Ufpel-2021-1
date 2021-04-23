void PUSH (Ward *ordenalista, No *aux, void *pBuffer) {

    No *pNovo = NULL, *pAux = ordenalista->start;
    pNovo = (No*)malloc(sizeof(No));
    pNovo->next = NULL;
    pNovo->previous = NULL;

    strcpy(pNovo->nome, aux->nome);
    pNovo->idade = aux->idade;
    pNovo->telefone = aux->telefone;

    switch(*(int*)(pBuffer + sizeof(int) + sizeof(int) + sizeof(int) + (10 * sizeof(char)))) {

        case 1:
        
            if (ordenalista->start == NULL) { // Lista vazia coloca no primeiro
                ordenalista->start = pNovo;
                ordenalista->end = pNovo;
                return;

            }
            else {

                if(ordenalista->start->idade > pNovo->idade) { //Testa o primeiro valor

                    pNovo->next = ordenalista->start;
                    ordenalista->start->previous = pNovo;
                    ordenalista->start = pNovo;
                    return;
                
                }
                
                while(pAux->next != NULL) { // Percorre a lista 

                    //NÃO TA FUNCIONANDO AINDA

                    if(pNovo->idade < pAux->next->idade) { //Meio da lista

                        pNovo->next = pAux->next;
                        pNovo->previous = pAux->previous;
                        pAux->previous->next = pNovo;
                        pAux->next->previous = pNovo;
                        return;
                    }

                    if(pAux->next == NULL) { //Ultimo da lista
                        
                        pNovo->previous = ordenalista->end;
                        ordenalista->end->next = pNovo;
                        ordenalista->end = pNovo;
                        return;

                    }

                    pAux = pAux->next;
                }

                return;
            }

        break;
    }