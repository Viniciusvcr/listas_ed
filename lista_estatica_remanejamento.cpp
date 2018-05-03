#include <iostream>
#define TAM 100

using namespace std;

typedef struct tipo_item{
	int chave;
}item;

typedef struct tipo_lista{
	int tam;
	struct tipo_item dados[TAM];
}lista;

void inicia_lista(lista* l){
	l->tam = 0;
}

int lista_cheia(lista* l){
	return l->tam == TAM;
}

int lista_vazia(lista* l){
	return l->tam == 0;
}

int busca_chave(lista* l, int chave);

int insere_fim(lista* l, item x){
	if(!lista_cheia(l)){
		if(!busca_chave(l, x.chave)){
			l->dados[l->tam] = x;
			l->tam++;
			return 1;
		}
	}

	return 0;
}

int insere_pos(lista* l, item x, int p){
	if((!lista_cheia(l) && (p <= l->tam))){
		if(!busca_chave(l, x.chave)){
			for(int i=l->tam-1; i>=p; i--) 
				l->dados[i+1] = l->dados[i];
			l->dados[p] = x;
			l->tam++;
			return 1;
		}	
	}

	return 0;
}

int exclui_pos(lista* l, int p){
	if(!lista_vazia(l) && (p < l->tam)){
		for(int i=p+1; i<l->tam; i++)
			l->dados[i-1] = l->dados[i];
		l->tam--;
		return 1;
	}

	return 0;
}

void print_lista(lista* l){ //exercício 1
	int i = 0;
	if(!lista_vazia(l)){
		while(i < l->tam){
			cout << l->dados[i].chave;
			i++;
			cout << " ";
		}
		cout << endl;
	}
}

int busca_chave(lista* l, int chave){ //exercício 2

	if(!lista_vazia(l)){
		for(int i=0; i<l->tam; i++){
			if(chave == l->dados[i].chave) return 1;
		}
	}

	return 0;
}

void ordena_lista(lista* l){
	item aux;

	for(int i=0; i<l->tam - 1; i++){
		for(int j=i+1; j<=(l->tam-1); j++){
			if(l->dados[i].chave > l->dados[j].chave){
				aux = l->dados[j];
				l->dados[j]= l->dados[i];
				l->dados[i] = aux;
			}
		}
	}
}

int exclui_chave(lista* l, int chave){ //exercício 4
	if(!busca_chave(l, chave)) return -1;

	for(int i=0; i<l->tam; i++){
		if(chave == l->dados[i].chave) return exclui_pos(l, i);
	}
}

int insere_ordenado(lista* l, item x){ //exercício 5
	if(lista_vazia(l)){
		l->dados[0] = x;
		l->tam++;
		return 1;
	}
	if(!lista_cheia(l)){
		if(!busca_chave(l, x.chave)){
			ordena_lista(l);
			for(int i=0; i<l->tam; i++){
				if(x.chave < l->dados[i].chave){
					return insere_pos(l, x, i);
					//return 1;
				}
			}
			return insere_pos(l, x, l->tam);
			//return 1;
		}
	}
	return 0;
}

int busca_binaria(lista* l, int chave){
	int e = 0, d = l->tam -1, m = (e+d)/2;

	while(e<=d){
		if(l->dados[m].chave == chave)
			return m;
		else if(l->dados[m].chave > chave)
			d = m-1;
		else
			e = m+1;
		m = (e+d)/2;
	}
	return -1;
}

int main(){
	lista chiforinfola;
	item i;
	i.chave = 5;

	inicia_lista(&chiforinfola);
	insere_fim(&chiforinfola, i);
	i.chave = 4;
	insere_fim(&chiforinfola, i);
	i.chave = 3;
	insere_fim(&chiforinfola, i);
	
	print_lista(&chiforinfola);

	ordena_lista(&chiforinfola);
	cout << endl << "ORDENADO: ";
	print_lista(&chiforinfola);
	i.chave = 6;
	insere_ordenado(&chiforinfola, i);
	print_lista(&chiforinfola);

	i.chave = 2;
	insere_ordenado(&chiforinfola, i);
	print_lista(&chiforinfola);

	exclui_chave(&chiforinfola, 6);
	print_lista(&chiforinfola);

	i.chave = 5;
	cout << insere_fim(&chiforinfola, i) << endl;
	cout << insere_pos(&chiforinfola, i, chiforinfola.tam) << endl;
	cout << insere_ordenado(&chiforinfola, i) << endl;
	i.chave = 1;
	cout << insere_pos(&chiforinfola, i, 0) << endl;
	print_lista(&chiforinfola);
	//cout << endl << busca_chave(&chiforinfola, 15) << endl;
}