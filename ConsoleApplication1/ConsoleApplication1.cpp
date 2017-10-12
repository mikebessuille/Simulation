// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <string>
#include "GameFile.h"
#include "GameGraph.h"

using namespace std;

// TODO: move this to a separate file and header?
char WaitForChar(string str)
{
	// Get any char as input, without requiring Enter.
	cout << str.c_str() << endl;
	while (_kbhit() == 0) {}
	char ch = _getch();
	return(ch);
}

void Print(string str)
{
	cout << str << endl;
}

int main()
{
	/*
	Print("Henry is a wonderful boy.");
	cout << "Day 1, Breakfast: I had cereal which made me sick. Then the doorbell rang." << endl;
	char ch = WaitForChar("Do you answer it? (y/n)");
	if (ch == 'y')
		cout << "It's a demon!  He kills you.  The end." << endl;
	else
		cout << "You go back to eating your cereal." << endl;
	WaitForChar("Hit any key to exit.");
	*/

	/*
	GameFile game;
	game.play();
	*/

	GameGraph game; // This should take an arg as the filename
	game.play();

	WaitForChar("GAME OVER.  Hit any key to exit.");

    return 0;
}




