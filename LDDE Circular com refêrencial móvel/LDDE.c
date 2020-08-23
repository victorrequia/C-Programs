#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

typedef struct No{
	int info;
	struct No *proximo;
	struct No *anterior;	
}Nodo;

typedef struct Desc{
	int TamInfo;
	int posLogAtual;
	Nodo *refMovel;
	Nodo *primeiraPos;
	Nodo *ultimaPos;
}Descritor;

void iniciaLista(Descritor *lista);
void adicionaNoInicioLista(Descritor *lista, int valor);
void adicionaNaPosicao(Descritor *lista, int valor, int posicao);
void adicionaFinalLista(Descritor *lista, int valor);
int tamanhoDaLista(Descritor *lista);
int buscaNaPosicao(Descritor *lista, int posAlvo);
int removeDaPosLog(Descritor *lista, int posAlvo);

int main (int argc, char **argv){
	setlocale(LC_ALL, "Portuguese");
	Descritor lista;
	iniciaLista(&lista);
	adicionaNoInicioLista(&lista, 10);
	printf("%i\n", lista.refMovel->info);
	adicionaNoInicioLista(&lista, 20);
	printf("%i\n", lista.refMovel->info);
	adicionaNoInicioLista(&lista, 30);
	printf("%i\n", lista.refMovel->info);
	adicionaNoInicioLista(&lista, 40);
	printf("%i\n", lista.refMovel->info);
	adicionaNoInicioLista(&lista, 50);
	printf("%i\n", lista.refMovel->info);
	adicionaFinalLista(&lista, 600);
	printf("%i\n", lista.refMovel->info);
	adicionaNoInicioLista(&lista, 60);
	printf("%i\n", lista.refMovel->info);
	adicionaNaPosicao(&lista, 10000, 2);
	printf("%i\n", lista.refMovel->info);
	printf("Elemento %i removido\n",removeDaPosLog(&lista, 6));
	printf("Posicao atual do auxiliar %i com o valor %i\n", lista.posLogAtual, lista.refMovel->info);
	adicionaFinalLista(&lista, 900);
	printf("Posicaoao atual %i (elemento %i) e o tamanho da lista e %i", lista.posLogAtual, lista.refMovel->info, tamanhoDaLista(&lista));
	printf("\nElemento anterior:%i \nProximo elemento: %i", lista.refMovel->anterior->info, lista.refMovel->proximo->info);
	printf("\nElemento na posicao %i e %i", lista.posLogAtual, buscaNaPosicao(&lista, 7));
	

}

void iniciaLista(Descritor *lista){
	lista->TamInfo = 0;
	lista->posLogAtual = -1;
	lista->refMovel = NULL;
	lista->ultimaPos = NULL;
	lista->primeiraPos = NULL;
}

void adicionaNoInicioLista(Descritor *lista, int valor){
	Nodo *novo_no;
	novo_no = (Nodo*)malloc(sizeof(Nodo));
	novo_no->info = valor;
	
	if(lista->refMovel == NULL){
		novo_no->anterior = NULL;
		novo_no->proximo = NULL;
		lista->refMovel = novo_no;
		lista->posLogAtual++;
		lista->ultimaPos = novo_no;
	}else{
		while(lista->posLogAtual != 0){
			lista->refMovel = lista->refMovel->proximo;
			lista->posLogAtual--; 
		}
		
		Nodo *aux = lista->refMovel;
		lista->refMovel->proximo = novo_no;
		novo_no->anterior = aux;
		novo_no->proximo = lista->ultimaPos;
		lista->refMovel = novo_no;

	}
	lista->TamInfo++;
	lista->primeiraPos = novo_no;
}

void adicionaNaPosicao(Descritor *lista, int valor, int posicao){
	if((posicao <= lista->TamInfo) && (posicao >= 0)){
		if(posicao == 0){
			adicionaNoInicioLista(lista, valor);
		}else{
			if(posicao == lista->TamInfo-1){
				adicionaFinalLista(lista, valor);
			}else{
				Nodo *novo_no;
				novo_no = (Nodo*)(malloc(sizeof(Nodo)));
				novo_no->info = valor;
					
				if(posicao < lista->posLogAtual){
					while(posicao != lista->posLogAtual){
						lista->refMovel = lista->refMovel->proximo;
						lista->posLogAtual--;
					}
					
					Nodo *aux = lista->refMovel;
					lista->refMovel = lista->refMovel->proximo;
					lista->refMovel->anterior = novo_no;
					novo_no->anterior = aux;
					novo_no->proximo = lista->refMovel; 
					aux->proximo = novo_no;
					lista->refMovel = lista->refMovel->anterior;
					lista->TamInfo++;	
				}else{
					while(posicao != lista->posLogAtual){
						lista->refMovel = lista->refMovel->anterior;
						lista->posLogAtual++;
					}
					Nodo *aux = lista->refMovel;
					lista->refMovel = lista->refMovel->proximo;
					lista->refMovel->anterior = novo_no;
					novo_no->anterior = aux;
					novo_no->proximo = lista->refMovel; 
					aux->proximo = novo_no;
					lista->refMovel = lista->refMovel->anterior;
					lista->TamInfo++;	
				}
			}		
		}
	}else{
		printf("Erro ao adicionar elemento, posicao invalida!\n");
	}
}

void adicionaFinalLista(Descritor *lista, int valor){
	Nodo *novo_no;
	novo_no = (Nodo*)malloc(sizeof(Nodo));
	novo_no->info = valor;
	
	if(lista->refMovel == NULL){
		novo_no->anterior = NULL;
		novo_no->proximo = NULL;
		lista->refMovel = novo_no;
		lista->primeiraPos = novo_no;
	}else{
		while(lista->posLogAtual != lista->TamInfo-1){
			lista->refMovel = lista->refMovel->anterior;
			lista->posLogAtual++;
		}
		Nodo *aux = lista->refMovel;
		lista->refMovel->anterior = novo_no;
		novo_no->proximo = aux;
		novo_no->anterior = lista->primeiraPos;
		lista->refMovel = novo_no;
	}
	lista->posLogAtual++;
	lista->TamInfo++;
	lista->ultimaPos = novo_no;
}

int tamanhoDaLista(Descritor *lista){
	return lista->TamInfo;
}

int buscaNaPosicao(Descritor *lista, int posAlvo){
	if(!((posAlvo > lista->TamInfo) || (posAlvo < 0))){
		if((fabs(posAlvo - lista->posLogAtual)) <  (fabs(((lista->TamInfo-1) - (lista->posLogAtual)) + posAlvo))){
			while(lista->posLogAtual != posAlvo){
				lista->refMovel = lista->refMovel->anterior;
				lista->posLogAtual++;
			}
			return lista->refMovel->info;	
		}else{
			while(lista->posLogAtual != posAlvo){
				lista->refMovel = lista->refMovel->proximo;
				lista->posLogAtual--;
			}
			return lista->refMovel->info;
		}
	}else{
		return printf("\nErro, posicao invalida!");
	}
}

int removeDaPosLog(Descritor *lista, int posAlvo){
	if(!((posAlvo > lista->TamInfo) || (posAlvo < 0))){
		int valor = buscaNaPosicao(lista, posAlvo);
		Nodo *auxProximo = lista->refMovel->proximo;
		Nodo *auxAnterior = lista->refMovel->anterior;
		
		free(lista->refMovel);
		auxProximo->anterior = auxAnterior;
		auxAnterior->proximo = auxProximo;
		
		lista->TamInfo--;
		lista->refMovel = auxAnterior;	
		
		return valor;
	}else{
		return printf("\nErro, posicao invalida!");
	}
}
