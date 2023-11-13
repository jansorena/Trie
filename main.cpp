#include "TrieArray.h"
#include "TrieMap.h"
#include <bits/stdc++.h>
using namespace std;

string printRandomString(int n, int size){
  char alphabet[26] = {'a','b','c','d','e','f','g','h', 'i', 'j', 'k', 'l', 'm', 'n',
                      	'o', 'p', 'q', 'r', 's', 't', 'u','v', 'w', 'x', 'y', 'z' };
  string res = "";
  for (int i = 0; i < n; i++) res = res + alphabet[rand() % size];
  return res;
}

int main(){
	srand(time(NULL));
	freopen("AnalisisExperimental/input/words_alpha.txt", "r", stdin); // leer cadenas desde txt
	freopen("AnalisisExperimental/output.txt", "w", stdout); // escribir en txt
	double time;

	TrieArray *triearr = new TrieArray; // declaracion de ambos tries
	TrieMap *triemap = new TrieMap;

	string s;
	int count = 300000;

	//TrieArray
	clock_t start = clock();
	for (int i = 0; i < count; i++) { // loop para ingresar palabras al trie
		cin >> s;
		if(s.length() == 0) break;
		triearr->insert(s);
	}
	time = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("TrieArray insert: %.10f\n",time);

	start = clock();
	vector<string> v = triearr->getAll();
	time = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("TrieArray getAll: %.10f\n",time);

	start = clock();
	for (int i = 0; i < v.size(); i++) {
		triearr->search(v[i]);
	}
	time = ((double)clock() - start) / CLOCKS_PER_SEC;
	printf("TrieArray search: %.10f\n",time);

	start = clock();
	vector<string> v3;
	for (int i = 0; i < 26; i++) {
		v3 = triearr->getKTopMatches(to_string(i+97),10);
	}
	time = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("TrieArray getKTopMatches: %.10f\n",time);

	start = clock();
	for (int i = 0; i < v.size(); i++) {
		triearr->remove(v[i]);
	}
	time = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("TrieArray remove: %.10f\n",time);

	// // TrieMap
	// clock_t start = clock();
	// for (int i = 0; i < count; i++) { // loop para ingresar palabras al trie
	// 	cin >> s;
	// 	if(s.length() == 0) break;
	// 	triemap->insert(s);
	// }
	// time = ((double)clock() - start) / CLOCKS_PER_SEC;
	// printf("TrieMap insert: %.10f\n",time);
  //
	// start = clock();
	// vector<string> v = triemap->getAll();
	// time = ((double)clock() - start) / CLOCKS_PER_SEC;
	// printf("TrieMap getAll: %.10f\n",time);
  //
	// start = clock();
	// for (int i = 0; i < v.size(); i++) {
	// 	triemap->search(v[i]);
	// }
	// time = ((double)clock() - start) / CLOCKS_PER_SEC;
	// printf("TrieMap search: %.10f\n",time);
  //
	// start = clock();
	// vector<string> v2;
	// for (int i = 0; i < 26; i++) {
	// 	v2 = triemap->getKTopMatches(to_string(i+97),10);
	// }
	// time = ((double)clock() - start) / CLOCKS_PER_SEC;
	// printf("TrieMap getKTopMatches: %.10f\n",time);
  //
	// start = clock();
	// for (int i = 0; i < v.size(); i++) {
	// 	triemap->remove(v[i]);
	// }
	// time = ((double)clock() - start) / CLOCKS_PER_SEC;
	// printf("TrieMap remove: %.10f\n",time);

	return 0;
}
