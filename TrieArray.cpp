#include "TrieArray.h"
#include <bits/stdc++.h>
using namespace std;

/********************** funciones auxiliares ************************************/

/* funcion para ordenar el vector en funcion de su frecuencia */
bool sortInt(const pair<string,int> &a,const pair<string,int> &b){
    if (a.second > b.second) return true;
    if (a.second < b.second) return false;
    return false;
}
/* funcion que un nodo este vacio no considerando la posicion dada */
bool isEmpty(node* aux, int pos) {
    for (int i = 0; i < 26; ++i){
        if (aux->children[i] != NULL && i != pos) return false;
    }
    return true;
}
/* funcion recursiva que agrega al vector v las strings contenidas en el trie */
void getStrings(vector<string> &v, node* aux, string s){
	if(aux->finPalabra) v.push_back(s);
	for (int i = 0; i < 26; ++i){
		if(aux->children[i] != NULL){
			char c = i+97;
			getStrings(v,aux->children[i],s+c);
		}
	}
}
/* funcion recursiva que agrega al vector v el par <string,int> contenidas en el trie */
void getKTopStrings(vector<pair<string,int>> &v, node* aux, string s){
	if(aux->finPalabra) {
		v.push_back(make_pair(s,aux->contador));
	}
	for (int i = 0; i < 26; ++i){
		if(aux->children[i] != NULL){
			char c = i+97;
			getKTopStrings(v,aux->children[i],s+c);
		}
	}
}
/*************************************************************************************/

TrieArray::TrieArray(){ /* constructor de la raiz del trie */
	struct node *aux = new node;
	for (int i = 0; i < 26; ++i){
		aux->children[i] = NULL;
	}
	aux->finPalabra = false;
	root = aux;
}

TrieArray::~TrieArray(){} /* destructor del trie */

void TrieArray::insert(const string &s){ /* insertar las cadenas al trie */
	node *aux = root;
	for (int i = 0; i < s.length(); ++i){
		int pos = s[i]-97;
		if(aux->children[pos] == NULL){
			node *nuevo = new node;
			aux->children[pos] = nuevo;
		}
		aux = aux->children[pos];
	}
	aux->finPalabra = true;
	aux->contador++;
}

bool TrieArray::search(const string &s){ /* buscar la cadena dada en el trie */
	node *aux = root;
	for (int i = 0; i < s.length(); ++i){
		int pos = s[i]-97;
		if(aux->children[pos] != NULL) aux = aux->children[pos];
		else return false;
	}
	if(aux->finPalabra) return true;
	else return false;
}

bool TrieArray::remove(const string &s){ /* borra la cadena en caso de estar en el trie */
	node *aux = root;
	node *lastNode = root;
	int posLastNode = 0;
	for (int i = 0; i < s.length(); ++i){ /* itera hasta encontrar el ultimo nodo */
		int pos = s[i]-97;
		if(aux->children[pos] != NULL) {
			if(!isEmpty(aux,pos)) { /* marcamos el ultimo nodo que contenga mas de 1 puntero */
				lastNode = aux;
				posLastNode = i;
			}
			aux = aux->children[pos];
		}
		else return false;
	}
	if(!aux->finPalabra) return false;

	if(!isEmpty(aux,-1)) { /* si el ultimo nodo contiene mas de un puntero lo marcamos como false */
		aux->finPalabra = false;
		aux->contador = 0;
		return true;
	}
	for (int i = posLastNode; i < s.length(); ++i){ /* borra a partir del ultimo nodo que contenga mas de 1 puntero */
		node *erase = lastNode;
		int pos = s[i]-97;
		lastNode = lastNode->children[pos];
		if(i == posLastNode) erase->children[pos] = NULL;
 		else delete[] erase;
	}
  delete[] lastNode;
	return true;
}

vector<string> TrieArray::getAll(){ /* devuelve un vector con todas las cadenas del trie */
	vector<string> v;
	string s;
	node *aux = root;
	getStrings(v,aux,s);
	return v;
}

vector<string> TrieArray::getKTopMatches(const string &s, int n){ /* devuelve un vector con las n cadenas de mayor frecuencia */
	vector<pair<string,int>> vec;
	node *aux = root;
	for (int i = 0; i < s.length(); ++i){
		int pos = s[i]-97;
		if(aux->children[pos] != NULL) {
			aux = aux->children[pos];
		}
	}
	getKTopStrings(vec,aux,s);
	sort(vec.begin(),vec.end(),sortInt);
	vector<string> v;
	for (int i = 0; i < n; ++i){
		if(i < vec.size()) v.push_back(vec[i].first);
	}
	return v;
}
