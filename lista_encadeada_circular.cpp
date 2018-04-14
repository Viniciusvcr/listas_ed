#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_celula{
	struct tipo_item item;
	struct tipo_celula *prox;
}celula;

typedef struct tipo_lista{
	struct tipo_celula *ultimo;
}lista;

void inicializa(lista* l){
	l->ultimo = NULL;
}

int vazia(lista* l){
	return l->ultimo == NULL;
}

celula* busca(lista* l, int chave){
	celula *ret, *ult;

	if(vazia(l)) return NULL;

	ret = l->ultimo->prox;
	ult = l->ultimo;
	while((ret != ult) && (ret->item.chave != chave)){
		ret = ret->prox;
	}
	if(ret->item.chave == chave)
		return ret;
	else return NULL;
}

void insere_ultimo(lista* l, item x){
	celula *novo = (celula*)malloc(sizeof(celula));
	novo->item = x;

	if(vazia(l)){
		novo->prox = novo;
	}else{
		novo->prox = l->ultimo->prox;
		l->ultimo->prox = novo;
	}

	l->ultimo = novo;
}

void insere_incio(lista* l, item x){
	celula *novo;

	if(vazia(l))
		insere_ultimo(l, x);
	else{
		celula *novo = (celula*)malloc(sizeof(celula));
		novo->item = x;
		novo->prox = l->ultimo->prox;
		l->ultimo->prox = novo;
	}
}

int remove_inicio(lista* l, item* retorno){
	celula *aux;

	if(vazia(l))
		return 0;

	aux = l->ultimo->prox;
	*retorno = aux->item;
	if(l->ultimo != l->ultimo->prox){
		l->ultimo->prox = aux->prox;
		free(aux);
		return 1;
	}
	l->ultimo = NULL;
	free(aux);
	return 1;
}

int remove_chave(lista* l, int chave, item* retorno){ //exercício 1
	celula *aux = l->ultimo->prox;
	celula *ant = l->ultimo;

	while((aux != l->ultimo) && (aux->item.chave != chave)){
		aux = aux->prox;
		ant = ant->prox;
	}
	if(aux->item.chave == chave){
		ant->prox = aux->prox;
		if(ant->prox == l->ultimo)
			l->ultimo = ant;
		*retorno = aux->item;
		free(aux);
	}
}

int remove_ultimo(lista* l, item *retorno){ //exercício 2
	celula *aux = l->ultimo->prox;

	if(!vazia(l)){
		while(aux->prox != l->ultimo)
			aux = aux->prox;
		aux->prox = l->ultimo->prox;
		*retorno = l->ultimo->item;
		free(l->ultimo);
		l->ultimo = aux;
		return 1;
	}

	return 0;
}

int insere_apos(lista* l, item x, int pos){ //exercício 3
	celula *aux = l->ultimo->prox;
	celula *novo;
	int cont = 0;

	if(vazia(l)){
		insere_ultimo(l, x);
		return 1;
	}

	while(aux != l->ultimo && cont < pos){
		aux = aux->prox;
		cont++;
	}
	if(cont == pos){
		novo = (celula*)malloc(sizeof(celula));
		novo->item = x;
		novo->prox = aux->prox;
		aux->prox = novo;
		if(aux == l->ultimo)
			l->ultimo = novo;
		return 1;
	}
	return 0;
}

int insere_ordenado(lista *l, item x){ //exercício 4
	celula *aux;
	celula *novo;

	if(vazia(l)){
		insere_ultimo(l, x);
		return 1;
	}
	
	if(x.chave < aux->item.chave){
		insere_incio(l, x);
		return 1;
	}

	aux = l->ultimo->prox;
	while(aux != l->ultimo && x.chave >= aux->prox->item.chave){
		aux = aux->prox;
	}
	novo = (celula*)malloc(sizeof(celula));
	novo->item = x;
	novo->prox = aux->prox;
	aux->prox = novo;
	if(aux == l->ultimo)
		l->ultimo = novo;
	return 1;		
}

void print_lista(lista *l){
	celula *aux = l->ultimo->prox;

	if(!vazia(l)){
		do{
			cout << aux->item.chave << " ";
			aux = aux->prox;
		}while(aux != l->ultimo->prox);
		cout << endl;
	}
}

void clear_screen(){
	system("cls");
}

void pause_screen(){
	system("pause");
	cout << endl;
}

int main(){
	lista A;
	int opt, pos, _busca;
	celula *search;
	item insere, removido;

	do{
		fflush(stdin);
		clear_screen();
		cout << "[01] Inicializar lista" << endl;
		cout << "[02] Verificar se a lista esta vazia" << endl;
		cout << "[03] Inserir elemento no inicio" << endl;
		cout << "[04] Inserir elemento no fim" << endl;
		cout << "[05] Inserir apos X posicoes" << endl;
		cout << "[06] Remover primeiro elemento" << endl;
		cout << "[07] Remover ultimo elemento" << endl;
		cout << "[08] Remover um elemento por chave" << endl;
		cout << "[09] Printar lista" << endl;
		cout << "[10] Buscar chave" << endl;
		cout << "[11] Inserir ordenado" << endl;
		cin >> opt;

		switch(opt){
			case 1:
				inicializa(&A);
				cout << "LISTA INICIALIZADA!" << endl;
				pause_screen();
			break;

			case 2:
				if(vazia(&A)) cout << "A LISTA ESTA VAZIA" << endl;
				else cout << "A LISTA NAO ESTA VAZIA" << endl;
				pause_screen();
			break;

			case 3:
				clear_screen();
				cout << "Digite o elemento que deseja inserir: ";
				cin >> insere.chave;
				insere_incio(&A, insere);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;

			case 4:
				clear_screen();
				cout << "Digite o elemento que deseja inserir: ";
				cin >> insere.chave;
				insere_ultimo(&A, insere);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;

			case 5:
				clear_screen();
				cout << "Digite o elemento que deseja inserir: ";
				cin >> insere.chave;
				cout << "Digite a posicao anterior ao novo elemento: ";
				cin >> pos;
				if(insere_apos(&A, insere, pos))
					cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA INSERCAO" << endl;
				pause_screen();
			break;

			case 6:
				if(remove_inicio(&A, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 7:
				if(remove_ultimo(&A, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 8:
				clear_screen();
				cout << "Digite a chave que deseja remover: ";
				cin >> _busca;
				if(remove_chave(&A, _busca, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 9:
				cout << "LISTA COMPLETA:" << endl;
				print_lista(&A);
				pause_screen();
			break;

			case 10:
				clear_screen();
				cout << "Digite a chave que deseja buscar: ";
				cin >> _busca;
				search = busca(&A, _busca);
				if(search != NULL)
					cout << "CHAVE EXISTENTE" << endl << "ENDEREÇO: " << search << endl;
				else
					cout << "CHAVE INEXISTENTE" << endl;
				pause_screen();
			break;

			case 11:
				clear_screen();
				cout << "Digite a chave que deseja inserir ordenadamente: ";
				cin >> insere.chave;
				if(insere_ordenado(&A, insere))
					cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA INSERCAO" << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}