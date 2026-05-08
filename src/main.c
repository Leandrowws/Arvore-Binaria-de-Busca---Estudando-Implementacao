#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *direita, *esquerda;
} NoArv;

/*
NoArv* Inserir(NoArv *raiz, int num) {
    if(raiz == NULL) {
        NoArv *aux = malloc(sizeof(NoArv));
        aux->valor = num;
        aux->esquerda = NULL;               //OUTRA VERSÃO PARA INSERIR
        aux->direita = NULL;
        return aux;
    } else {
        if(num < raiz->valor) {
            raiz->esquerda = Inserir(raiz->esquerda, num);
        } else {
            raiz->direita = Inserir(raiz->direita, num);
        }
        return raiz;
    }
} 
*/

void Inserir(NoArv **raiz, int num) {
    if(*raiz == NULL) {
        *raiz = (NoArv*)malloc(sizeof(NoArv));
        (*raiz)->valor = num;
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
    } else {
        if(num < (*raiz)->valor) {
            Inserir(&(*raiz)->esquerda, num);
        } else if(num > (*raiz)->valor){
            Inserir(&(*raiz)->direita, num);
        } else {
            printf("\nErro: Registro ja existe na arvore!\n");
        }
    }
}

NoArv* Buscar(NoArv *raiz, int num) {
    if( raiz != NULL ) {    
        if( num == raiz->valor ) {
            return raiz;
        }
        else if ( num < raiz->valor ) {
            return Buscar(raiz->esquerda, num);
        } else {
            return Buscar(raiz->direita, num);
        }
    } 
        return NULL;
}

int Altura(NoArv *raiz) {
    if(raiz==NULL) {
        return -1;
    } else {
        int esq = Altura(raiz->esquerda);
        int dir = Altura(raiz->direita);
        if(esq > dir) {
            return esq + 1;
        } else {
            return dir + 1;
        }
    }
}

int QtdNos(NoArv *raiz) {
    return (raiz == NULL) ? 0: 1 + QtdNos(raiz->esquerda) + QtdNos(raiz->direita);
}

int QtdFolhas(NoArv *raiz) {
    if(raiz == NULL) {
        return 0;
    } else if(raiz->esquerda == NULL && raiz->direita == NULL) {
        return 1;
    } else {
        return QtdFolhas(raiz->esquerda) + QtdFolhas(raiz->direita);
    }
}

NoArv *Remover(NoArv *raiz, int num) {
    if(raiz == NULL) {
        printf("Valor nao encontrado!\n");
    } else {
        if(raiz->valor == num) {
            if(raiz->esquerda == NULL && raiz->direita == NULL) { //remove nós folhas (sem filhos)
                free(raiz); 
                return NULL;
            } else {    
                if(raiz->esquerda != NULL && raiz->direita != NULL) { //remove nós com 2 filhos
                    NoArv *aux = raiz->esquerda;
                    while(aux->direita != NULL) {
                        aux = aux->direita;
                    }
                    raiz->valor = aux->valor;
                    aux->valor = num;           //troca de lugar o nó que eu achei com o nó mais a direita da esquerda dele
                    raiz->esquerda= Remover(raiz->esquerda, num);
                    return raiz;
                } else { //remove nós que possuem apenas 1 filho
                    NoArv *aux;
                    if(raiz->esquerda != NULL) {
                        aux = raiz->esquerda;
                    } else {
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;
                }
            }
        } else {
            if(num < raiz->valor) {
                raiz->esquerda = Remover(raiz->esquerda, num);
            } else {
                raiz->direita = Remover(raiz->direita, num);
            }
            return raiz;
        }
    }
}


void Imprimir(NoArv *raiz) {
    if(raiz != NULL) {
        Imprimir(raiz->esquerda);
        printf("%d ", raiz->valor);
        Imprimir(raiz->direita);
    } 
}

int main() {

    int sel = -1, num;
    NoArv *raiz = NULL, *busca = NULL;

    do {
        printf("\n1 - Inserir\n2 - Imprimir\n3 - Buscar No\n4 - Encontrar Altura\n5 - Contar Quantidade de Nos\n6 - Contar Quantidade de Folhas\n7 - Remover Elemento\n0 - Sair\n\n");
        scanf("%d", &sel);

        switch(sel) {

            case 1: 
                printf("\nDigite o numero a ser inserido: ");
                scanf("%d", &num);
                //raiz = Inserir(raiz, num);  OUTRA VERSÃO PARA INSERIR
                Inserir(&raiz, num);
                break;

            case 2:
                printf("\nArvore: ");
                Imprimir(raiz);
                printf("\n");
                break;

            case 3:
            printf("\nDigite o numero a ser buscado: ");
            scanf("%d", &num);
            busca = Buscar(raiz,num);
            if(busca != NULL) {
                printf("\nValor encontrado: %d\n", busca->valor);
            } else {
                printf("Valor nao encontrado!");
            }
            break;

            case 4:
            printf("\nAltura da Arvore: %d\n", Altura(raiz));
            break;

            case 5:
            printf("\nQuantidade de nos: %d\n", QtdNos(raiz));
            break;

            case 6:
            printf("\nQuantidade de Folhas: %d\n", QtdFolhas(raiz));
            break;

            case 7:
            printf("\nDigite o numero a ser removido: ");
            scanf("%d", &num);
            Remover(raiz, num);
            break;

            case 0: 
                printf("Saindo...");
                break;
        }

    } while(sel != 0);


    return 0;
}
