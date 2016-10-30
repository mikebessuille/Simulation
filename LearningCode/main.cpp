#include <iostream>
#include <conio.h>
#include <thread>

#include "CPP11Features.h"
#include "CPP11SpecialFunctions.h"

using namespace std;

void WaitForChar(string str)
{
	// Get any char as input, without requiring Enter.
	cout << str.c_str() << endl;
	while (_kbhit() == 0) {}
	char ch = _getch();
	cout << "Char: " << ch << endl; // if we used _getch() directly here, it would output the ASCII (int) value, not the char.
}

int main()
{
	cout << "Learning Code Project.  Hit Enter to start:" << endl;
	cin.get(); // gets any user input (requires user to hit enter as well)

	CPP11Features cpp11;
	cpp11.run();

	CPP11SpecialFunctions cpp11SF;
	cpp11SF.run();

	WaitForChar("Learning Code Project Complete.  Hit any key to end.");	
	this_thread::sleep_for(chrono::seconds(3));
	return(true);
}