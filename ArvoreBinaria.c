#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no{
	int valor;
	struct no *direita, *esquerda;
}NoArv;

NoArv* inserir_v1(NoArv *raiz, int num){
	if(raiz == NULL){
		NoArv *aux = (NoArv*)malloc(sizeof(NoArv));
		aux->valor = num;
		aux->esquerda = NULL;
		aux->direita = NULL;
		return aux;
	}else{
		if(num < raiz->valor)
			raiz->esquerda = inserir_v1(raiz->esquerda, num);
		else
			raiz->direita = inserir_v1(raiz->direita, num);
		return raiz;
	}
}

void inserir_v2(NoArv **raiz, int num){
	if(*raiz == NULL){
		*raiz = (NoArv*)malloc(sizeof(NoArv));
		(*raiz)->valor = num;
		(*raiz)->esquerda = NULL;
		(*raiz)->direita = NULL;
	}else{
		if(num < (*raiz)->valor)
			inserir_v2(&((*raiz)->esquerda), num);
		else
			inserir_v2(&((*raiz)->direita), num);
	}
}

void inserir_v3(NoArv **raiz, int num){
	NoArv *aux = *raiz;
	while(aux){
		if(num < aux->valor)
			raiz = &aux->esquerda;
		else
			raiz = &aux->direita;
		aux = *raiz;
	}
	aux = (NoArv*)malloc(sizeof(NoArv));
	aux->valor = num;
	aux->esquerda = NULL;
	aux->direita = NULL;
	*raiz = aux;
}

NoArv* buscar_v1(NoArv *raiz, int num){
	if(raiz){
		if(num == raiz->valor)
			return raiz;
		else if(num < raiz->valor)
			return buscar_v1(raiz->esquerda, num);
		else
			return buscar_v1(raiz->direita, num);
	}
	return NULL;
}

NoArv* buscar_v2(NoArv *raiz, int num){
	while(raiz){
		if(num < raiz->valor)
			raiz = raiz->esquerda;
		else if(num > raiz->valor)
			raiz = raiz->direita;
		else
			return raiz;
	}
	return NULL;
}

int altura(NoArv *raiz){
	if(raiz == NULL){
		return -1;
	}else{
		int esq = altura(raiz->esquerda);
		int dir = altura(raiz->direita);
		if(esq > dir)
			return esq + 1;
		else
			return dir + 1;
	}
}

int quantidade_nos(NoArv *raiz){
	if(raiz == NULL)
		return 0;
	else
		return 1 +
			quantidade_nos(raiz->esquerda) +
			quantidade_nos(raiz->direita);
}

int quantidade_folhas(NoArv *raiz){
	if(raiz == NULL)
		return 0;
	else if(raiz->esquerda == NULL && raiz->direita == NULL)
		return 1;
	else
		return quantidade_folhas(raiz->esquerda)
			+ quantidade_folhas(raiz->direita);
}

NoArv* remover(NoArv *raiz, int chave){
	if(raiz == NULL){
		printf("Valor não encontrado.\n");
		return NULL;
	}else{
		if(raiz->valor == chave){
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				printf("Elemento removido: %d\n", chave);
				return NULL;
			}else{
				if(raiz->esquerda != NULL && raiz->direita != NULL){
					NoArv *aux = raiz->esquerda;
					while(aux->direita != NULL)
						aux = aux->direita;
					raiz->valor = aux->valor;
					aux->valor = chave;
					printf("Elemento trocado: %d\n", chave);
					raiz->esquerda = remover(raiz->esquerda, chave);
					return raiz;
				}else{
					NoArv *aux;
					if(raiz->esquerda != NULL)
						aux = raiz->esquerda;
					else
						aux = raiz->direita;
					free(raiz);
					printf("Elemento com 1 filho removido: &d\n", chave);
					return aux;
				}
			}
		}else{
			if(chave < raiz->valor)
				raiz->esquerda = remover(raiz->esquerda, chave);
			else
				raiz->direita = remover(raiz->direita, chave);
			return raiz;
		}
	}
}

void imprimir_arvore(NoArv *raiz, int nivel) {
    if (raiz == NULL)
        return;

    nivel += 5;

    imprimir_arvore(raiz->direita, nivel);

    printf("\n");
    for (int i = 5; i < nivel; i++)
        printf(" ");
    printf("%d\n", raiz->valor);

    imprimir_arvore(raiz->esquerda, nivel);
}







int main(void){
	NoArv *busca, *raiz = NULL;
	int opcao, valor;
	setlocale(LC_ALL,"Portuguese");
	
//	raiz = inserir_v1(raiz,24);
//	raiz = inserir_v1(raiz,32);
//	raiz = inserir_v1(raiz,10);
//	raiz = inserir_v1(raiz,5);
//	raiz = inserir_v1(raiz,29);
//	raiz = inserir_v1(raiz,12);
//	raiz = inserir_v1(raiz,35);
//	raiz = inserir_v1(raiz,39);
//	
//	imprimir_pre_ordem(raiz);
//	printf("\n");
//	imprimir_in_ordem(raiz);
//	printf("\n");
//	imprimir_pos_ordem(raiz);
//	printf("\n");
//	
	do{
		printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - Altura\n5 - Tamanho\n6 - Folhas\n7 - Remover\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				printf("\nValor: ");
				scanf("%d", &valor);
				inserir_v2(&raiz, valor);
				break;
			case 2:
				printf("\nÁrvore:\n");
                imprimir_arvore(raiz, 0);
				break;
			case 3:
				printf("\nValor (busca): ");
				scanf("%d", &valor);
				busca = buscar_v1(raiz, valor);
				if(busca)
					printf("\nValor encontrado: %d\n", busca->valor);
				else
					printf("\nValor não encontrado.\n");
				break;
			case 4:
				printf("\nAltura: %d\n", altura(raiz));
				break;
			case 5:
				printf("\nQuantidade de Nós: %d\n", quantidade_nos(raiz));
				break;
			case 6:
				printf("\nQuantidade de Folhas: %d\n", quantidade_folhas(raiz));
				break;
			case 7:
				printf("\nRemover valor: ");
				scanf("%d", &valor);
				raiz = remover(raiz, valor);
				break;
			default:
				if(opcao != 0)
					printf("\nOpção inválida.\n");
		}
	}while(opcao != 0);
}
