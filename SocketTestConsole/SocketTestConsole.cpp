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


int main()
{
	SocketClass sc;
	int val = sc.TestMethod();
	cout << val << endl;
	WaitForChar( "Hit any key to exit");
    return 0;
}

