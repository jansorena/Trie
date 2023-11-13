#include "Trie.h"
#include <string>
#include <vector>
#include <map>

#ifndef TRIEMAP
#define TRIEMAP

struct nodeMap{
	std::map<char,nodeMap*> m;
	bool finPalabra;
	int contador = 0;
};

class TrieMap: public Trie {
private:
	nodeMap *root;
public:
	TrieMap();
	~TrieMap();
	void insert(const std::string &s);
	bool search(const std::string &s);
	bool remove(const std::string &s);
	std::vector <std::string> getAll();
	std::vector <std::string> getKTopMatches(const std::string &s, int);
};

#endif