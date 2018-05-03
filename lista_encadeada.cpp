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
	l->primeiro = NULL;
	l->ultimo = NULL;
}

int vazia(lista* l){
	return l->primeiro == NULL;
}

void insere_primeiro(lista *l, item i){
	celula *novo = (celula*)malloc(sizeof(celula));
	novo->item = i;
	if(vazia(l))
		l->ultimo = novo;
	novo->prox = l->primeiro;
	l->primeiro = novo;
}

void insere_ultimo(lista* l, item x){
	if(vazia(l)) 
		insere_primeiro(l, x);
	else{
		celula *c = (celula*)malloc(sizeof(celula));
		c->item = x;
		c->prox = NULL;
		l->ultimo->prox = c;
		l->ultimo = c;
	}
}

int remove_primeiro(lista* l, item* x){
	celula *e;
	if(!vazia(l)){
		e = l->primeiro;
		l->primeiro = e->prox;
		*x = e->item;
		free(e);
		if(vazia(l))
			l->ultimo = NULL;
		return 1;
	}
	return 0;
}

int remove_ultimo(lista* l, item *x){
	celula *e;
	if(!vazia(l) && (l->primeiro == l->ultimo))
		return remove_primeiro(l, x);
	else{
		e=l->primeiro;
		while(e->prox != l->ultimo)
			e = e->prox;
		*x = e->prox->item;
		free(e->prox);
		e->prox = NULL;
		l->ultimo = e;
		return 1;
	}
	return 0;
}

int remove_posicao(lista* l, int pos, item *retorno){
	int i;
	item it;
	celula *e, *ant;
	if(!vazia(l)){
		if(pos==0){
			e = l->primeiro;
			l->primeiro = l->primeiro->prox;
			if(vazia(l))
				l->ultimo = NULL;
			*retorno = e->item;
			free(e);
			return 1;
		}else{
			ant = l->primeiro;
			e = ant->prox;
			i = 1;
			while((e!=NULL) && (i<pos)){
				e = e->prox;
				ant = ant->prox;
				i++;
			}
			if(e != NULL){
				ant->prox = e->prox;
				*retorno = e->item;
				free(e);
				if(ant->prox == NULL)
					l->ultimo = ant;
				return 1;
			}
		}
	}
	return 0;
}

celula* buscar(lista* l, int c){
	celula *i = l->primeiro;
	while(i != NULL){
		if(i->item.chave == c) 
			return i;
		i = i->prox;
	}
	return NULL;
}

void escreve_lista(lista* l){
	celula *i = l->primeiro;
	while(i != NULL){
		cout << i->item.chave << " ";
		i = i->prox;
	}
	cout << endl;
}

void mostra_lista_r(celula *c){ //exercício 1
	if(c != NULL){
		cout << c->item.chave << " ";
		mostra_lista_r(c->prox);
	}
}

int remove_chave(lista* l, item x){ //exercício 2
	celula *aux, *ant;

	aux = l->primeiro;
	if(!vazia(l)){
		if(aux->item.chave == x.chave) {
            remove_primeiro(l, &x);
            return 1;
        }
		while(aux != NULL && aux->item.chave != x.chave){
            ant = aux;
            aux = aux->prox;
        }
        if(aux == NULL) return 0;
        ant->prox = aux->prox;
        if(ant->prox == NULL){
            l->ultimo = ant->prox;
        }
        free(aux);

		return 1;
	}
	return 0;
}

int insere_pos(lista* l, item insert, int i){ //exercício 3
	celula *aux = l->primeiro;
	celula *novo;
	int cont = 0;

	if(!vazia(l)){
		while((cont != i) && (aux != NULL)){
			aux = aux->prox;
			cont++;
		}
		if(cont == i){
			if(cont == 0){ 
				insere_primeiro(l, insert);
				return 1;
			}
			else{
				novo = (celula*)malloc(sizeof(celula));
			    novo->item = insert;
                novo->prox = aux->prox;
                aux->prox = novo;
				if(novo->prox == NULL)
					l->ultimo = novo;
				return 1;
			}
		}
	}
	return 0;
}

int concatena_lista(lista* A, lista* B){ //exercício 4
    celula *aux = A->primeiro;

	if(!vazia(A) && !vazia(B)){
		A->ultimo = B->ultimo;
		while(aux->prox != NULL) aux = aux->prox;
		aux->prox = B->primeiro;
		inicializa(B);
		return 1;
	}
	if(vazia(A) && !vazia(B)){
		A->primeiro = B->primeiro;
		A->ultimo = B->ultimo;
		inicializa(B);
		return 1;
	}
	if((!vazia(A) && vazia(B)) || (vazia(A) && vazia(B))){
		return 0;
	}
}

void insere_ordenado(lista* l, item x){ //exercício 5
	celula *novo, *aux;

	if(vazia(l)){
		insere_primeiro(l, x);
		return;
	}

	aux = l->primeiro;
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

int conta_celula(lista* l){ //exercício 6
	celula *aux = l->primeiro;
	int qntd = 0;

	while(aux != NULL){
		aux = aux->prox;
		qntd++;
	}
	return qntd;
}

void exclui_lista(lista* l){ //exercício 8
	celula *aux = l->primeiro, *excluir;

	while(aux != NULL){
		excluir = aux;
		aux = aux->prox;
		free(excluir);
	}
	inicializa(l);
}

int crescente(lista* l){ //exercício 1a - LISTA PROVA
	celula *aux, *sucessor;

	if(!vazia(l)){
		aux = l->primeiro;
		sucessor = aux->prox;
		while(sucessor != NULL){
			if(aux->item.chave < sucessor->item.chave){
				aux = aux->prox;
				sucessor = sucessor->prox;
			}
			else return 0;
		}
		return 1;
	}
	return 0;
}

void clear_screen(){
	system("clear");
}

void pause_screen(){
	cout << endl;
	//system("pause");
}

int a_or_b(){
	int opt;
	cout << "Lista [0]A ou Lista [1]B? ";
	cin >> opt;
	return opt;
}

int main(){
	lista A, B;
	item x, retorno;
	int opt, aux;

	do{
		fflush(stdin);
		//clear_screen();
		cout << "[01] Inicializar lista A e B" << endl;
		cout << "[02] Verificar se uma lista esta vazia" << endl;
		cout << "[03] Inserir no inicio de uma lista" << endl;
		cout << "[04] Inserir no final de uma lista" << endl;
		cout << "[05] Remover o primeiro item de uma lista" << endl;
		cout << "[06] Remover o ultimo item de uma lista" << endl;
		cout << "[07] Remover um item de uma posicao na lista" << endl;
		cout << "[08] Buscar um item em uma lista" << endl;
		cout << "[09] Imprimir uma lista na tela" << endl;
		cout << "[10] Imprimir uma lista na tela (recursivo)" << endl;
		cout << "[11] Remover uma chave especifica da lista" << endl;
		cout << "[12] Inserir um item depois de uma posicao" << endl;
		cout << "[13] Concatenar A e B" << endl;
		cout << "[14] Verificar a quantidade de elementos da lista" << endl;
		cout << "[15] Excluir lista" << endl;
		cout << "[16] Inserir ordenado" << endl;
		cout << "[17] Crescente?" << endl;
		cin >> opt;
		switch(opt){
			case 1:
				inicializa(&A);
				inicializa(&B);
			break;

			case 2:
				cout << endl << "Lista A: " << vazia(&A) << endl;
				cout << "Lista B: " << vazia(&B) << endl;
				pause_screen();
			break;

			case 3:
				clear_screen();
				cout << "Item a adicionar: ";
				cin >> x.chave;
				if(!a_or_b()) insere_primeiro(&A, x);
				else insere_primeiro(&B, x);
			break;

			case 4:
				clear_screen();
				cout << "Item a adicionar: ";
				cin >> x.chave;
				if(!a_or_b()) insere_ultimo(&A, x);
				else insere_ultimo(&B, x);
			break;

			case 5:
				if(!a_or_b()){
					if(remove_primeiro(&A, &retorno)) cout << retorno.chave << "removido com sucesso!";
					else cout << "Falha na remocao!";
				}else{
					if(remove_primeiro(&B, &retorno)) cout << retorno.chave << "removido com sucesso!";
					else cout << "Falha na remocao!";
				}
			break;

			case 6: 
				if(!a_or_b()){
					if(remove_ultimo(&A, &retorno)) cout << retorno.chave << "removido com sucesso!";
					else cout << "Falha na remocao!";
				}else{
					if(remove_ultimo(&B, &retorno)) cout << retorno.chave << "removido com sucesso!";
					else cout << "Falha na remocao!";
				}
			break;

			case 7:
				cout << "Posicao a ser removida: ";
				cin >> aux;
				if(!a_or_b()){
					if(remove_posicao(&A, aux, &retorno)) cout << retorno.chave << "Removido com sucesso!";
					else cout << "Falha na remocao!";
				}else{
					if(remove_posicao(&B, aux, &retorno)) cout << retorno.chave << "removido com sucesso!";
					else cout << "Falha na remocao!";
				}
				pause_screen();
			break;

			case 8:
				cout << "Chave para busca: ";
				cin >> aux;
				if(!a_or_b()){
					if(buscar(&A, aux) != NULL) cout << "EXISTENTE NA LISTA (Endereço: " << buscar(&A, aux) << ")";
					else cout << "INEXISTENTE NA LISTA";
				}else{
					if(buscar(&B, aux) != NULL) cout << "EXISTENTE NA LISTA (Endereço: " << buscar(&B, aux) << ")";
					else cout << "INEXISTENTE NA LISTA";
				}
				pause_screen();
			break;

			case 9:
				if(!a_or_b()) escreve_lista(&A);
				else escreve_lista(&B);
				pause_screen();
			break;

			case 10:
				if(!a_or_b()){ 
					mostra_lista_r(A.primeiro);
					pause_screen();
				}
				else{
				mostra_lista_r(B.primeiro);
				pause_screen();
				}
			break;

			case 11:
				cout << "Chave para remocao: ";
				cin >> x.chave;
				if(!a_or_b()){
					if(remove_chave(&A, x)) cout << "Removido com sucesso!";
					else cout << "Falha na remocao!";
				}else{
					if(remove_chave(&B, x)) cout << "Removido com sucesso!";
					else cout << "Falha na remocao!";
				}
				pause_screen();
			break;

			case 12:
				cout << "Posicao: ";
				cin >> aux;
				cout << "Item a adicionar: ";
				cin >> x.chave;
				if(!a_or_b()){
					if(insere_pos(&A, x, aux)) cout << "Incluido com sucesso!";
					else cout << "Falha na operacao!";
				}else{
					if(insere_pos(&B, x, aux)) cout << "Incluido com sucesso!";
					else cout << "Falha na operacao!";
				}
				pause_screen();
			break;

			case 13:
				if(concatena_lista(&A, &B)){
					cout << "NOVA LISTA A: ";
					escreve_lista(&A);
					cout << endl;
				}else{
					cout << "Nao houve alteracoes nas listas";
				}
				pause_screen();
			break;

			case 14:
				if(!a_or_b()){
					cout << conta_celula(&A);
				}else{
					cout << conta_celula(&B);
				}
				pause_screen();
			break;

			case 15:
				if(!a_or_b()) exclui_lista(&A);
				else exclui_lista(&B);
			break;

			case 16:
				clear_screen();
				cout << "Item a adicionar: ";
				cin >> x.chave;
				if(!a_or_b()) insere_ordenado(&A, x);
				else insere_ordenado(&B, x);
			break;

			case 17:
				cout << crescente(&A) << endl << endl;
		}
	}while(opt != 0);
}

