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
	struct tipo_celula *primeiro;
	struct tipo_celula *ultimo;
}lista;

void inicializa(lista* l){
	l->primeiro = (celula*)malloc(sizeof(celula));
	l->primeiro->prox = NULL;
	l->ultimo = l->primeiro;
}

int vazia(lista* l){
	return l->primeiro == l->ultimo;
}

void insere_primeiro(lista*l, item x){
	celula *novo = (celula*)malloc(sizeof(celula));
	novo->item = x;
	novo->prox = l->primeiro->prox;
	l->primeiro->prox = novo;
	if(vazia(l)){
		l->ultimo = novo;
	}
}

void insere_ultimo(lista* l, item x){
	celula *novo = (celula*)malloc(sizeof(celula));
	novo->item = x;
	novo->prox = NULL;
	l->ultimo->prox = novo;
	l->ultimo = novo;
}

int insere_apos(lista* l, item x, int pos){
	celula *novo, *ptr = l->primeiro->prox;
	int i = 0;
	while((ptr != NULL) && (i<pos)){
		ptr = ptr->prox;
		i++;
	}
	if(ptr != NULL){
		novo = (celula*)malloc(sizeof(celula));
		novo->item = x;
		novo->prox = ptr->prox;
		ptr->prox = novo;
		if(novo->prox == NULL)
			l->ultimo = novo;
	}
}

int remove_primeiro(lista* l, item *retorno){
	celula *ptr = l->primeiro->prox;
	if(!vazia(l)){
		l->primeiro->prox = ptr->prox;
		*retorno = ptr->item;
		free(ptr);
		if(l->primeiro->prox == NULL)
			l->ultimo = l->primeiro;
		return 1;
	}
	return 0;
}

int busca_chave(lista* l, int busca){ //exercício 1 - sala | exercício 5 - slide
	celula *ptr = l->primeiro->prox;
	while(ptr != NULL){
		if(ptr->item.chave == busca)
			return 1;
		ptr = ptr->prox;
	}
	return 0;
}

void print_lista(lista* l){ //exercício 2 - sala | exercício 4 - slide
	celula *ptr = l->primeiro->prox;
	while(ptr != NULL){
		cout << ptr->item.chave << " ";
		ptr = ptr->prox;
	}
	cout << endl;
}

int remove_fim(lista* l, item* retorno){ //exercício 3 - sala | exercício 2 - slide
	celula *ptr = l->primeiro->prox;
	*retorno = l->ultimo->item;
	if(!vazia(l)){
		while(ptr->prox != l->ultimo)
			ptr = ptr->prox;
		ptr->prox = NULL;
		free(l->ultimo);
		l->ultimo = ptr;
		return 1;
	}
	return 0;
}

int remove_pos(lista* l, int pos, item* retorno){ //exercício 1 - slide
	celula *ptr = l->primeiro->prox, *anterior = l->primeiro;
	int cont = 0;
	if(!vazia(l)){
		while((cont != pos) && (ptr != NULL)){
			ptr = ptr->prox;
			anterior = anterior->prox;
			cont++;
		}
		if(ptr != NULL){
			anterior->prox = ptr->prox;
			*retorno = ptr->item;
			free(ptr);
			if(anterior->prox == NULL)
				l->ultimo = anterior;
			return 1;
		}
	}
	return 0;
}

void insere_ordenado(lista* l, item x){ //exercício 3
	celula *novo, *aux = l->primeiro;

	while(aux != l->ultimo){
		if(x.chave <= aux->prox->item.chave){
			novo = (celula*)malloc(sizeof(celula));
			novo->item = x;
			novo->prox = aux->prox;
			aux->prox = novo;
			return;
		}else aux = aux->prox;
	}
	insere_ultimo(l, x);
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
	int opt, pos, busca;
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
		cout << "[08] Buscar um elemento por chave" << endl;
		cout << "[09] Printar lista" << endl;
		cout << "[10] Remover na posicao X" << endl;
		cout << "[11] Insere ordenado" << endl;
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
				insere_primeiro(&A, insere);
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
				if(remove_primeiro(&A, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 7:
				if(remove_fim(&A, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 8:
				clear_screen();
				cout << "Digite a chave que deseja buscar: ";
				cin >> busca;
				if(busca_chave(&A, busca))
					cout << "CHAVE EXISTE" << endl;
				else
					cout << "CHAVE NAO EXISTE" << endl;
				pause_screen();
			break;

			case 9:
				cout << "LISTA COMPLETA:" << endl;
				print_lista(&A);
				pause_screen();
			break;

			case 10:
				clear_screen();
				cout << "Digite a posicao que deseja excluir: ";
				cin >> pos;
				if(remove_pos(&A, pos, &removido))
					cout << removido.chave << " REMOVIDO COM SUCESSO" << endl;
				else
					cout << "ERRO NA REMOCAO" << endl;
				pause_screen();
			break;

			case 11:
				clear_screen();
				cout << "Digite o elemento que deseja inserir: ";
				cin >> insere.chave;
				insere_ordenado(&A, insere);
				cout << "ELEMENTO INSERIDO COM SUCESSO" << endl;
				pause_screen();
			break;
		}
	}while(opt != 0);
}