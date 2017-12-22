#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include <conio.h>
#include "block.h"

using namespace std;

char WaitForChar(string str)
{
	// Get any char as input, without requiring Enter.
	cout << str.c_str() << endl;
	while (_kbhit() == 0) {}
	char ch = _getch();
	return(ch);
}


int main()
{
	Block genesis( 0, "Mike created 1000 coins");
	Block b2(genesis.GetHash(), "Mike sold Sally 10 coins");
	cout << "Genesis Hash: " << genesis.GetHash() << endl;
	cout << "b2 hash: " << b2.GetHash() << endl;

	// Create some fake info based on a modified genesis (previous) record:
	Block genesisFake(0, "Mike created 100000000 coins");
	Block b2Fake(genesisFake.GetHash(), "Mike sold Sally 10 coins"); // Attempted duplicate of b2 record
	cout << "b2Fake hash: " << b2Fake.GetHash() << endl;

	WaitForChar("Hit any key to exit.");
	return 0;
}
