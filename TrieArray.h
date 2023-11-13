#include "Trie.h"
#include <string>
#include <vector>

#ifndef TRIEARRAY
#define TRIEARRAY

struct node{
	node *children[26];
	bool finPalabra;
	int contador = 0;
};

class TrieArray: public Trie {
private:
	node *root;
public:
	TrieArray();
	~TrieArray();
	void insert(const std::string &s);
	bool search(const std::string &s);
	bool remove(const std::string &s);
	std::vector <std::string> getAll();
	std::vector <std::string> getKTopMatches(const std::string &s, int);
};

#endif