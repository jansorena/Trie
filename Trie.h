#include <string>
#include <vector>

#ifndef TRIE
#define TRIE

class Trie{
public:
	virtual void insert(const std::string &) = 0;
	virtual bool search(const std::string &) = 0;
	virtual bool remove(const std::string &) = 0;
	virtual std::vector <std::string> getAll() = 0;
	virtual std::vector <std::string> getKTopMatches(const std::string &, int) = 0;
};

#endif