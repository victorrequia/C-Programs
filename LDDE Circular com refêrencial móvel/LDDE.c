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
	
	adicionaNoInicioLista(&lista, 5);
	printf("Elemento %i inserido no Inicio da Lista\n", lista.primeiraPos->info);
	adicionaNoInicioLista(&lista, 10);
	printf("Elemento %i inserido no Inicio da Lista\n", lista.primeiraPos->info);
	adicionaNoInicioLista(&lista, 15);
	printf("Elemento %i inserido no Inicio da Lista\n", lista.primeiraPos->info);
	adicionaFinalLista(&lista, 205);
	printf("Elemento %i inserido no Final da Lista\n", lista.ultimaPos->info);
	adicionaFinalLista(&lista, 2300);
	printf("Elemento %i inserido no Final da Lista\n", lista.ultimaPos->info);
	adicionaNoInicioLista(&lista, 1);
	printf("Elemento %i inserido no Inicio da Lista\n", lista.primeiraPos->info);
	adicionaFinalLista(&lista, 9300);
	printf("Elemento %i inserido no Final da Lista\n", lista.ultimaPos->info);
	adicionaNoInicioLista(&lista, 10000);
	printf("Elemento %i inserido no Inicio da Lista\n", lista.primeiraPos->info);
	adicionaFinalLista(&lista, 9300);
	printf("Elemento %i inserido no Final da Lista\n", lista.ultimaPos->info);
	adicionaNaPosicao(&lista, 100, 8);
	printf("Elemento %i inserido na Posicao %i da Lista\n", lista.refMovel->info, lista.posLogAtual);
	adicionaNaPosicao(&lista, 200, 10);
	printf("Elemento %i inserido na Posicao %i da Lista\n", lista.refMovel->info, lista.posLogAtual);
	adicionaNaPosicao(&lista, 2200, 0);
	printf("Elemento %i inserido na Posicao %i da Lista\n", lista.refMovel->info, lista.posLogAtual);

	printf("\nPosicao log atual %i com o elemento %i, Tamanho da lista %i", lista.posLogAtual,
	lista.refMovel->info, lista.TamInfo, lista.ultimaPos->info);
	printf("\nPrimeiro elemento da lista %i e ultimo elemento %i\n", lista.primeiraPos->info, lista.ultimaPos->info);
	imprimeLista(&lista);
	printf("\n");
	/*removeDaPosLog(&lista, 3);
	printf("Elemento removida da posicao 3\n");
	removeDaPosLog(&lista, 2);
	printf("Elemento removida da posicao 2\n");
	removeDaPosLog(&lista, 2);
	printf("Elemento removida da posicao 2\n");
	imprimeLista(&lista);  ????????*/
	printf("\n");
	printf("\nPosicao log atual %i com o elemento %i, Tamanho da lista %i", lista.posLogAtual,
	lista.refMovel->info, lista.TamInfo, lista.ultimaPos->info);
	
	printf("\nElemento na posicao %i = %i", lista.posLogAtual,buscaNaPosicao(&lista, 6));
	printf("\nElemento na posicao %i = %i", lista.posLogAtual,buscaNaPosicao(&lista, 9));
}

void iniciaLista(Descritor *lista){
	lista->TamInfo = 0;
	lista->posLogAtual = -1;
	lista->refMovel = NULL;
	lista->ultimaPos = NULL;
	lista->primeiraPos = NULL;
}

void imprimeLista(Descritor *lista){
	Descritor *aux;
	
	memcpy(aux, lista, sizeof(Descritor));

	aux->refMovel = lista->primeiraPos;
	aux->posLogAtual = 0;
	int i=0;
	while(aux->posLogAtual < aux->TamInfo){
		printf("%i-%i, ", i,aux->refMovel->info);
		aux->refMovel = aux->refMovel->anterior;
		aux->posLogAtual++;
		i++;
	}
	free(aux);
}

void adicionaNoInicioLista(Descritor *lista, int valor){
	Nodo *novo_no;
	novo_no = (Nodo*)malloc(sizeof(Nodo));
	novo_no->info = valor;
	
	if(lista->refMovel == NULL){
		novo_no->anterior = NULL;
		novo_no->proximo = NULL;
		lista->refMovel = novo_no;
		lista->ultimaPos = novo_no;
	}else{
		lista->ultimaPos->anterior = novo_no;
		
		lista->refMovel = lista->primeiraPos;
		lista->refMovel->proximo = novo_no;
			
		lista->refMovel = novo_no; 
		
		novo_no->anterior = lista->primeiraPos;
		novo_no->proximo = lista->ultimaPos;
	}
	
	lista->TamInfo++;
	lista->primeiraPos = novo_no;
	lista->posLogAtual = 0;
}

void adicionaNaPosicao(Descritor *lista, int valor, int posAlvo){
	if((posAlvo <= lista->TamInfo) && (posAlvo >= 0)){	
		if(posAlvo == lista->TamInfo){
			adicionaFinalLista(lista, valor);	
		}else{
			if(posAlvo == 0){
				adicionaNoInicioLista(lista, valor);		
			}else{
				Nodo *novo_no;
				novo_no = (Nodo*)(malloc(sizeof(Nodo)));
				novo_no->info = valor;
							
				if(posAlvo < lista->posLogAtual){
					while(posAlvo != lista->posLogAtual){
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
					while(posAlvo != lista->posLogAtual){
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
		adicionaNoInicioLista(lista, valor);
	}else{
		lista->primeiraPos->proximo = novo_no;
		
		lista->refMovel = lista->ultimaPos;
		lista->refMovel->anterior = novo_no;
		novo_no->proximo = lista->refMovel;
		
		lista->refMovel = novo_no;
	}
	
	novo_no->anterior = lista->primeiraPos;
	lista->TamInfo++;
	lista->posLogAtual = lista->TamInfo-1;
	lista->ultimaPos = novo_no;
}

int tamanhoDaLista(Descritor *lista){
	return lista->TamInfo;
}

int buscaNaPosicao(Descritor *lista, int posAlvo){
	if((posAlvo < lista->TamInfo) && (posAlvo >= 0)){ //Verifica se a posicao e valida
		if(posAlvo <= lista->posLogAtual){ //Alvo esta a direita do referencial movel
			if((fabs(lista->TamInfo-lista->posLogAtual) + posAlvo) < (fabs(lista->posLogAtual-posAlvo))){  //Percorre atual-direita
				while(lista->posLogAtual != posAlvo){
					lista->refMovel = lista->refMovel->anterior;
					lista->posLogAtual++;
					if(lista->posLogAtual == lista->TamInfo){
						lista->posLogAtual = 0;
					}
				}
				return lista->refMovel->info;
			}else{ //Percorre atual-esquerda
				while(lista->posLogAtual != posAlvo){
					lista->refMovel = lista->refMovel->proximo;
					lista->posLogAtual --;
				}
				return lista->refMovel->info;
			}
		}else{ //Alvo esta  a esquerda do referencial movel 
			if((lista->posLogAtual+(fabs(lista->TamInfo-posAlvo))) < (fabs(posAlvo-lista->posLogAtual))){ //Percorre atual-esquerda
				while(lista->posLogAtual != posAlvo){
					lista->refMovel = lista->refMovel->proximo;
					lista->posLogAtual--;
					if(lista->posLogAtual == -1){
						lista->posLogAtual = lista->TamInfo-1;
					}
				}
				
				return lista->refMovel->info;
			}else{ //Percorre atual-direita
			while(lista->posLogAtual != posAlvo){
				lista->refMovel = lista->refMovel->anterior;
				lista->posLogAtual++;
			}
			
			return lista->refMovel->info;
			}
		}
		}else{
			printf("\nPosicao invalida!\n");
			return NULL; //????
		}
}

int removeDaPosLog(Descritor *lista, int posAlvo){
	if((posAlvo < lista->TamInfo) && (posAlvo >= 0)){
		int valor = buscaNaPosicao(lista, posAlvo);
		
		Nodo *auxProximo = lista->refMovel->proximo;
		Nodo *auxAnterior = lista->refMovel->anterior;
		
		auxProximo->anterior = auxAnterior;
		auxAnterior->proximo = auxProximo;
		
		lista->TamInfo--;
		
		Nodo *remover = lista->refMovel;
		free(remover); //????????
		
		lista->refMovel = auxAnterior;	
		
		if(posAlvo == lista->TamInfo-1){
			lista->primeiraPos->proximo = lista->refMovel->anterior;
		}
		
		if(posAlvo == 0){
			lista->ultimaPos->anterior = lista->refMovel->proximo; 
		}
		
		
		return valor;
	}else{
		return printf("\nErro, posicao invalida!");
	}
}
