#include "block.h"



Block::Block(size_t prevHash, string trans) : 
	previousHash(prevHash), transactions( trans )
{
	// Calculate current hash
	std::size_t transHash = std::hash<std::string>{}(transactions);
	currentHash = hashCombine(transHash, previousHash);
}


Block::~Block()
{
}

// Combine two hashes together
size_t Block::hashCombine(size_t h1, size_t h2)
{
	size_t ret = h1; 
	ret ^= h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
	return(ret);
}