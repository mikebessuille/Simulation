// SocketTestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "SocketClass.h"

using namespace std;

char WaitForChar(string str)
{
	// Get any char as input, without requiring Enter.
	cout << str.c_str() << endl;
	while (_kbhit() == 0) {}
	char ch = _getch();
	return(ch);
}


int main(int argc, char* argv[])
{
	bool bServer = false;
	if (argc > 20)
		return 0;

	for (int i = 1; i < argc; ++i)
	{
		string arg = argv[i];
		if (arg == "-server" || arg == "-s")
		{
			bServer = true;
		}
	}

	WaitForChar("Hit any key to start socket");

	SocketClass sc(bServer);
	WaitForChar( "Hit any key to exit");
    return 0;
}

