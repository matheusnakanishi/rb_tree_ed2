#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct no {
    int id;
    int cor;
    struct no *pai;
    struct no *esq;
    struct no *dir;
} No;

typedef struct {
    No *raiz;
} Arvore;

No *criarNo(int id) {
    No *novo = (No*)malloc(sizeof(No));

    novo->id = id;
    novo->cor = RED;
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

void rotacaoEsq(No *x, Arvore *arvore) {
    No *y = x->dir;

    x->dir = y->esq;
    if (y->esq)
        y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai) {
        if (x == x->pai->esq)
            x->pai->esq = y;
        else
            x->pai->dir = y;
    }
    else
        arvore->raiz = y;
    
    y->esq = x;
    x->pai = y;
}

void rotacaoDir(No *x, Arvore *arvore) {
    No *y = x->esq;

    x->esq = y->dir;
    if (y->dir)
        y->dir->pai = x;

    y->pai = x->pai;
    if (x->pai) {
        if (x == x->pai->esq)
            x->pai->esq = y;
        else
            x->pai->dir = y;
    }
    else
        arvore->raiz = y;

    y->dir = x;
    x->pai = y;
}

void arrumarArvore(No *no, Arvore *arvore) {
    if (no != arvore->raiz && no->pai->cor == RED) {
        No *avo = no->pai->pai;
        if (avo) {
            // Pai a esquerda
            if (no->pai == avo->esq) { 
                No *tio = avo->dir;

                // Caso 1E
                if (tio && tio->cor == RED && no->pai->cor == RED) {
                    if (avo->cor == RED) {
                        avo->cor = BLACK;
                        printf("Avo fica negro - ");
                    }
                    else {
                        avo->cor = RED;
                        printf("Avo fica rubro - ");
                    }
                    tio->cor = BLACK;
                    printf("Tio fica negro - ");
                    no->pai->cor = BLACK;
                    printf("Pai fica negro - ");
                    
                    arrumarArvore(avo, arvore);
                }
                else {
                    // Caso 2E
                    if (no == no->pai->dir && no->pai->cor == RED && (tio == NULL || tio->cor == BLACK)) {
                        no = no->pai;
                        printf("Rotaciona pai a esquerda - ");
                        rotacaoEsq(no, arvore);
                    }
                    // Caso 3E
                    if (no == no->pai->esq && no->pai->cor == RED && (tio == NULL || tio->cor == BLACK)) {
                        printf("Rotaciona avo a direita - ");
                        rotacaoDir(avo, arvore);
                        printf("Avo fica rubro - ");
                        avo->cor = RED;
                        printf("Pai fica negro - ");
                        no->pai->cor = BLACK;
                    }
                }
            }
            // Pai a direita
            else {
                No *tio = avo->esq;
                // Caso 1D
                if (tio && tio->cor == RED && no->pai->cor == RED) {
                    if (avo->cor == RED) {
                        avo->cor = BLACK;
                        printf("Avo fica negro - ");
                    }
                    else {
                        avo->cor = RED;
                        printf("Avo fica rubro - ");
                    }
                    tio->cor = BLACK;
                    printf("Tio fica negro - ");
                    no->pai->cor = BLACK;
                    printf("Pai fica negro - ");
                
                    arrumarArvore(avo, arvore);
                }
                else {
                    // Caso 2D
                    if (no == no->pai->esq && no->pai->cor == RED && (tio == NULL || tio->cor == BLACK)) {
                        no = no->pai;
                        rotacaoDir(no, arvore);
                        printf("Rotaciona pai a direita - ");
                    }
                    // Caso 3D
                    if (no == no->pai->dir && no->pai->cor == RED && (tio == NULL || tio->cor == BLACK)) {
                        rotacaoEsq(avo, arvore);
                        printf("Rotaciona avo a esquerda - ");
                        avo->cor = RED;
                        printf("Avo fica rubro - ");
                        no->pai->cor = BLACK;
                        printf("Pai fica negro - ");
                    }
                }
            }
        }
    arvore->raiz->cor = BLACK;
    printf("Raiz fica negra - ");
    }
}

void inserir(Arvore *arvore, int id) {
    No* novo = criarNo(id);
    if (novo == NULL)
        printf("erro memoria");
    
    No *pai = NULL;
    No *aux = arvore->raiz;

    while (aux) {
        pai = aux;

        if (id < aux->id)
            aux = aux->esq;
        else if (id > aux->id)
            aux = aux->dir;
        else {
            printf("\nMatricula [%d] ja inserida anteriormente\n", id);
            return;
        }
    }
    
    novo->pai = pai;

    if (novo->pai == NULL){
        novo->cor = BLACK;
        arvore->raiz = novo;
    }
    else {
        if (id < pai->id)
            pai->esq = novo;
        else
            pai->dir = novo;
    }

    //fix
    arrumarArvore(novo, arvore);
}

void exibirArvore(No *raiz){
    if (raiz) {
        printf("(");
        exibirArvore(raiz->esq);
        printf("%d-%d", raiz->id, raiz->cor);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

void caso32(No *no, int lado) {
    if (no && no->pai)
    {
    
        if (lado == 0) {
            No *irmao = no->pai->dir;
            
            if ((!irmao || irmao->cor == BLACK) && (!(irmao->esq) || irmao->esq->cor == BLACK) && (!(irmao->dir) || irmao->dir->cor == BLACK)) {
                if (irmao) {
                    irmao->cor = RED;
                    printf("Irmao fica rubro - ");
                }
                
                no = no->pai;
                printf("No aponta para o pai - ");
                if ((no->cor == RED)) {
                    no->cor = BLACK;
                    printf("No fica negro - ");
                }
                caso32(no, 0);
            }
        }
        else {
            No *irmao = no->pai->esq;

            if ((!irmao || irmao->cor == BLACK) && (!(irmao->dir) || irmao->dir->cor == BLACK) && (!(irmao->esq) || irmao->esq->cor == BLACK)) {
                if (irmao) {
                    irmao->cor = RED;
                    printf("Irmao fica rubro - ");
                }
                
                no = no->pai;
                printf("No aponta pro pai - ");

                if ((no->cor == RED)) {
                    no->cor = BLACK;
                    printf("No fica negro - ");
                }

                caso32(no, 1);
            }
        }
    }
}

void arrumarExclusao(Arvore *arvore, No *no) {
    No *irmao = NULL;
    // Nó a esquerda
    if (no == no->pai->esq) {
        irmao = no->pai->dir;

        if (irmao && irmao->cor == RED) {
            no->pai->cor = RED;
            printf("Pai fica rubro - ");
            irmao->cor = BLACK;
            printf("Irmao fica negro - ");
            rotacaoEsq(no->pai, arvore);
            printf("Rotaciona pai a esquerda - ");
            irmao = no->pai->dir;
            printf("Atualiza irmao - ");
        }

        caso32(no, 0);
        
        if ((irmao && irmao->cor == BLACK) && (irmao->dir == NULL || irmao->dir->cor == BLACK)) {
            if (irmao->esq) {
                irmao->esq->cor = BLACK;
                printf("Filho esquerdo do irmao fica negro - ");
            }
            
            irmao->cor = RED;
            printf("Irmao fica rubro - ");
            rotacaoDir(irmao, arvore);
            printf("Rotaciona irmao a direita - ");
            irmao = no->pai->dir;
            printf("Atualiza irmao - ");
        }

        if (irmao && (irmao->dir && irmao->dir->cor == RED)) {
            irmao->cor = no->pai->cor;
            printf("Irmao copia a cor do pai - ");
            no->pai->cor = BLACK;
            printf("Pai fica negro - ");
            irmao->dir->cor = BLACK;
            printf("Filho direito do irmao fica negro - ");
            rotacaoEsq(no->pai, arvore);
            printf("Rotaciona pai a esquerda - ");

            arvore->raiz->cor = BLACK;
            printf("Raiz fica negra - ");
        }
    }
    // Nó a direita
    else {
        irmao = no->pai->esq;

        if (irmao && irmao->cor == RED) {
            no->pai->cor = RED;
            printf("Pai fica rubro - ");
            irmao->cor = BLACK;
            printf("Irmao fica negro - ");
            rotacaoDir(no->pai, arvore);
            printf("Rotaciona pai a direita - ");
            irmao = no->pai->esq;
            printf("Atualiza irmao - ");
        }

        caso32(no, 1);
        
        if ((irmao && irmao->cor == BLACK) && (!(irmao->esq) || irmao->esq->cor == BLACK)) {
            if (irmao->dir) {
                irmao->dir->cor = BLACK;
                printf("Irmao a direita fica negro - ");
            }
            
            irmao->cor = RED;
            printf("Irmao fica rubro - ");
            rotacaoEsq(irmao, arvore);
            printf("Rotaciona irma a esquerda - ");
            irmao = no->pai->esq;
            printf("Atualiza irmao - ");
        }

        if (irmao && (irmao->esq && irmao->esq->cor == RED)) {
            irmao->cor = no->pai->cor;
            printf("Irmao copia cor do pai - ");
            no->pai->cor = BLACK;
            printf("Pai fica negro - ");
            irmao->esq->cor = BLACK;
            printf("Filho a esquerda do irmao fica negro - ");
            rotacaoDir(no->pai, arvore);
            printf("Rotaciona pai a direita - ");

            arvore->raiz->cor = BLACK;
            printf("Raiz fica negra - ");
        }
    }
}

void excluir(Arvore *arvore, Arvore *arvoreAux, int id) {
    No *aux = arvoreAux->raiz;
    // Nó raiz folha
    if (aux->id == id && aux->esq == NULL && aux->dir == NULL && aux->pai == NULL) {
        free(aux);
        arvore->raiz = NULL;
        return;
    }

    while (aux && aux->id != id) {
        if (id < aux->id)   
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    if (aux == NULL) {
        printf("\nValor nao encontrado.\n");
        return;
    }
    // Nó folha
    if (aux->esq == NULL && aux->dir == NULL) {
        if (aux->cor == BLACK)
            arrumarExclusao(arvore, aux);
        
        if (aux == aux->pai->esq)
            aux->pai->esq = NULL;
        if(aux == aux->pai->dir)
            aux->pai->dir = NULL;
        free(aux);
    } 
    // Nó com 1 ou 2 filhos
    else {
        No *suc;
        Arvore arvoreSuc;

        if (aux->esq) {
            suc = aux->esq;

            while (suc->dir)
                suc = suc->dir;

            aux->id = suc->id;
            suc->id = id;
            arvoreSuc.raiz = aux->esq;
        }
        else {
            suc = aux->dir;

            while (suc->esq)
                suc = suc->esq;

            aux->id = suc->id;
            suc->id = id;
            arvoreSuc.raiz = aux->dir;
        }

        excluir(arvore, &arvoreSuc, id);
    }
}

int altura(No *raiz) {
    if (!raiz)  
        return 0;

    int altEsq = 1 + altura(raiz->esq);
    int altDir = 1 + altura(raiz->dir);
    
    return (altEsq > altDir)? altEsq : altDir;
}

int alturaNegra(No *raiz) {
    if (!raiz) 
        return 1;
    
    int altEsq = 0, altDir = 0;

    if (raiz->cor == BLACK) {
        altEsq = 1 + alturaNegra(raiz->esq);
        altDir = 1 + alturaNegra(raiz->dir);
    }
    else {
        altEsq += alturaNegra(raiz->esq);
        altDir += alturaNegra(raiz->dir);
    }
    
    return (altEsq > altDir)? altEsq : altDir;
}

No *buscar(No *raiz, int id, int *comparacoes) {
    while (raiz && raiz->id != id) {
        if (id < raiz->id)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;

        *(comparacoes) += 1;
    }
    
    return raiz;
}

float contadorNN(No *no) {
    if (!no) 
        return 1;
    
    float cont = 0;

    if (no->cor == BLACK) 
        cont = 1 + contadorNN(no->esq) + contadorNN(no->dir);
    else 
        cont += contadorNN(no->esq) + contadorNN(no->dir);
    
    return cont;
}

float contadorNR(No *no) {
    if (!no) 
        return 0;
    
    float cont = 0;

    if (no->cor == RED) 
        cont = 1 + contadorNR(no->esq) + contadorNR(no->dir);
    else 
        cont += contadorNR(no->esq) + contadorNR(no->dir);
    
    return cont;
}

void percentagemNos(No *raiz, float *percN, float *percR) {
    float numNegros = contadorNN(raiz);
    float numRubros = contadorNR(raiz); 
    float numNos = numNegros + numRubros;

    *(percN) = (numNegros/numNos)*100.00;
    *(percR) = (numRubros/numNos)*100.00; 
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

int main() {
    Arvore arvore;  // Declaração da variável Arvore
    arvore.raiz = NULL;

    int opcao, valor, comparacoes;
    float percN, percR;

    do {
        printf("\n[1]Inserir\n[2]Exibir\n[3]Remover\n[4]Calcular altura\n[5]Buscar matricula\n[6]Calcular porcentagem de cor\n[0]Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\nMatricula a ser inserido: ");
            scanf("%d", &valor);
            if (valor <= 9999)
                inserir(&arvore, valor);  
            else
                printf("\nA matricula deve conter 4 digitos\n");
            break;

        case 2:
            exibirArvore(arvore.raiz);
            break;

        case 3:
            printf("\nMatricula a ser removida: ");
            scanf("%d", &valor);
            excluir(&arvore, &arvore, valor);  
            break;

        case 4:
            printf("\nAltura da arvore: %d", altura(arvore.raiz));
            printf("\nAltura Negra da arvore: %d\n", alturaNegra(arvore.raiz));
            break;

        case 5:
            comparacoes = 1;
            printf("\nMatricula a ser buscada: ");
            scanf("%d", &valor);
            No *buscado = buscar(arvore.raiz, valor, &comparacoes);
            if (buscado)
                printf("\nMatricula: %d\nCusto da busca: %d\n", buscado->id, comparacoes);
            else
                printf("\nMatricula nao encontrada\n");  
            break;

        case 6:
            percentagemNos(arvore.raiz, &percN, &percR);
            printf("\nPorcentagem nos Negros: %.2f%%", percN);
            printf("\nPorcentagem nos Rubros: %.2f%%\n", percR);
            break;

        case 0:
            printf("\nSaindo...\n");
            liberarArvore(arvore.raiz);
            arvore.raiz = NULL;
            break;

        default:
            printf("\nOpcao invalida.\n");
            break;
        }

    } while (opcao != 0);
    
    return 0;
}