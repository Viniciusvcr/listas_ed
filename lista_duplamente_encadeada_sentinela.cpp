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
	struct tipo_celula *ant;
}celula;

typedef struct tipo_lista{
	struct tipo_celula *primeiro;
}lista;

void inicializa(lista* l){
	l->primeiro = (celula*)malloc(sizeof(celula));
	l->primeiro->prox = l->primeiro;
	l->primeiro->ant = l->primeiro;
}

int vazia(lista* l){
	return l->primeiro->prox == l->primeiro;
}

void insere_inicio(lista *l, item x){
	celula *novo = (celula*)malloc(sizeof(celula));

	novo->item = x;
	novo->ant = l->primeiro;
	novo->prox = l->primeiro->prox;
	l->primeiro->prox = novo;
	novo->prox->ant = novo;
}

void insere_fim(lista* l, item x){
	celula *novo = (celula*)malloc(sizeof(celula));

	novo->item = x;
	novo->prox = l->primeiro;
	novo->ant = l->primeiro->ant;
	l->primeiro->ant->prox = novo;
	l->primeiro->ant = novo;
}

int insere_apos(lista* l, item x, int pos){
	celula *novo;
	celula *aux = l->primeiro->prox;
	int cont = 0;

	while(aux != l->primeiro && cont < pos){
		aux = aux->prox;
		cont++;
	}
	if(cont == pos){
		novo = (celula*)malloc(sizeof(celula));
		novo->item = x;
		novo->prox = aux->prox;
		novo->ant = aux;
		aux->prox = novo;
		novo->prox->ant = novo;
		return 1;
	}
	return 0;
}

void print_lista(lista* l){ //exercício 1
	celula *aux = l->primeiro->prox;

	if(!vazia(l)){
		do{
			cout << aux->item.chave << " ";
			aux = aux->prox;
		}while(aux != l->primeiro);
		cout << endl;
	}else
		cout << "LISTA VAZIA" << endl;
}

int remove_inicio(lista* l, item *retorno){
	celula *aux = l->primeiro->prox;

	if(!vazia(l)){
		*retorno = aux->item;
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		free(aux);
		return 1;
	}
	return 0;
}

celula* busca(lista* l, int chave){
	celula *aux = l->primeiro->prox;
	
	while(aux != l->primeiro){
		if(aux->item.chave == chave)
			return aux;
		aux = aux->prox;
	}
	return NULL;
}

int remove_chave(lista* l, int chave, item* retorno){
	celula *aux = busca(l, chave);

	if(aux == NULL)
		return 0;
	*retorno = aux->item;
	aux->ant->prox = aux->prox;
	aux->prox->ant = aux->ant;
	free(aux);
	return 1;
}

int remove_pos(lista* l, int pos, item* retorno){ //exercício 3
	celula *aux = l->primeiro->prox;
	int cont = 0;

	if(!vazia(l)){
		while(aux != l->primeiro && cont < pos){
			aux = aux->prox;
			cont++;
		}
		if(cont == pos){
			aux->ant->prox = aux->prox;
			aux->prox->ant = aux->ant;
			*retorno = aux->item;
			free(aux);
			return 1;
		}
	}
	return 0;
}

int tamanho_lista(lista* l){ //exercício 2
	celula *aux = l->primeiro->prox;
	int cont = 0;

	while(aux != l->primeiro){
		aux = aux->prox;
		cont++;
	}
	return cont;
}

void rotaciona_direita(lista *l, int pos){ //exercício 4
	celula *aux;

	for(int i=0; i<pos; i++){
		aux = l->primeiro->prox;
		l->primeiro->prox = l->primeiro->ant;
		aux->ant = l->primeiro->prox;
		l->primeiro->ant = l->primeiro->prox->ant;
		l->primeiro->ant->prox = l->primeiro;
		l->primeiro->prox->prox = aux;
		l->primeiro->prox->ant = l->primeiro;
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
		cout << "[07] Remover elemento na posicao X" << endl;
		cout << "[08] Remover um elemento por chave" << endl;
		cout << "[09] Printar lista" << endl;
		cout << "[10] Buscar chave" << endl;
		cout << "[11] Rotacionar a direita" << endl;
		cout << "[12] Tamanho da lista" << endl;
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
				insere_inicio(&A, insere);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;

			case 4:
				clear_screen();
				cout << "Digite o elemento que deseja inserir: ";
				cin >> insere.chave;
				insere_fim(&A, insere);
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
				clear_screen();
				cout << "Digite a posicao que deseja remover: ";
				cin >> pos;
				if(remove_pos(&A, pos, &removido))
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
				cout << "Digite a quantidade de vezes: ";
				cin >> pos;
				rotaciona_direita(&A, pos);
			break;

			case 12:
				cout << "Tamanho da Lista: " << tamanho_lista(&A) << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}