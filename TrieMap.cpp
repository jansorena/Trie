#include "TrieMap.h"
#include <bits/stdc++.h>
using namespace std;

/********************** funciones auxiliares ************************************/

/* funcion para ordenar el vector en funcion de su frecuencia */
bool sortIntMap(const pair<string,int> &a,const pair<string,int> &b){
    if (a.second > b.second) return true;
    if (a.second < b.second) return false;
    return false;
}
/* funcion recursiva que agrega al vector v las strings contenidas en el trie */
void getStrings(vector<string> &v, nodeMap* aux, string s){
	map<char,nodeMap*>::iterator it;
	if(aux->finPalabra) v.push_back(s);
	for (it = aux->m.begin(); it != aux->m.end(); ++it){
		getStrings(v,it->second,s+it->first);
	}
}
/* funcion recursiva que agrega al vector v el par <string,int> contenidas en el trie */
void getKTopStrings(vector<pair<string,int>> &v, nodeMap* aux, string s){
	map<char,nodeMap*>::iterator it;
	if(aux->finPalabra) {
		v.push_back(make_pair(s,aux->contador));
	}
	for (it = aux->m.begin(); it != aux->m.end(); ++it){
		getKTopStrings(v,it->second,s+it->first);
	}
}
/*************************************************************************************/

TrieMap::TrieMap(){ /* constructor de la raiz del trie */
	struct nodeMap *aux = new nodeMap;
	aux->finPalabra = false;
	root = aux;
}

TrieMap::~TrieMap(){} /* destructor del trie */

void TrieMap::insert(const string &s){ /* insertar las cadenas al trie */
	nodeMap *aux = root;
	for (int i = 0; i < s.length(); ++i){
		if(!aux->m.count(s[i])){
			nodeMap *nuevo = new nodeMap;
			aux->m[s[i]] = nuevo;
		}
		aux = aux->m[s[i]];
	}
	aux->finPalabra = true;
	aux->contador++;
}

bool TrieMap::search(const string &s){ /* buscar la cadena dada en el trie */
	nodeMap *aux = root;
	for (int i = 0; i < s.length(); ++i){
		if(aux->m.count(s[i])) aux = aux->m[s[i]];
		else return false;
	}
	if(aux->finPalabra) return true;
	else return false;
}

bool TrieMap::remove(const string &s){ /* borra la cadena en caso de estar en el trie */
	nodeMap *aux = root;
	nodeMap *lastNode = root;
	int posLastNode = 0;

	for (int i = 0; i < s.length(); ++i){ /* itera hasta encontrar el ultimo nodo */
		if(aux->m.count(s[i])) {
			if(aux->m.size()>1) { /* marcamos el ultimo nodo que contenga mas de 1 llave */
				lastNode = aux;
				posLastNode = i;
			}
			aux = aux->m[s[i]];
		}else return false;
	}

	if(!aux->finPalabra) return false;

	if(aux->m.size()>0) { /* si el ultimo nodo contiene mas de un puntero lo marcamos como false */
		aux->finPalabra = false;
		aux->contador = 0;
		return true;
	}

	for (int i = posLastNode; i < s.length(); ++i){ /* borra a partir del ultimo nodo que contenga mas de 1 llave */
		nodeMap *erase = lastNode;
		lastNode = lastNode->m[s[i]];
		if(i == posLastNode) erase->m.erase(s[i]);
		else delete erase;
	}
  delete lastNode;
	return true;
}

vector<string> TrieMap::getAll(){ /* devuelve un vector con todas las cadenas del trie */
	vector<string> v;
	string s;
	nodeMap *aux = root;
	getStrings(v,aux,s);
	return v;
}

vector<string> TrieMap::getKTopMatches(const string &s, int n){ /* devuelve un vector con las n cadenas de mayor frecuencia */
	vector<pair<string,int>> vec;
	nodeMap *aux = root;
	for (unsigned int i = 0; i < s.length(); ++i){
		if(aux->m.count(s[i])) {
			aux = aux->m[s[i]];
		}
	}
	getKTopStrings(vec,aux,s);
	sort(vec.begin(),vec.end(),sortIntMap);
	vector<string> v;
	for (int i = 0; i < n; ++i){
		if(i < vec.size()) v.push_back(vec[i].first);
	}
	return v;
}
