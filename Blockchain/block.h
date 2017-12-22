#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class Block
{
public:
	Block( size_t prevHash, string trans );
	~Block();
	size_t GetHash() { return(currentHash); };

private:
	string transactions; // should be a separate class
	size_t previousHash;
	size_t currentHash;

private:
	size_t hashCombine(size_t h1, size_t h2);

};

