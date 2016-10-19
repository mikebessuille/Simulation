#include <iostream>
#include <conio.h>
#include <thread>

#include "CPP11Features.h"

using namespace std;

int main()
{
	cout << "Learning Code Project.  Hit Enter to start:" << endl;
	cin.get(); // gets any user input (requires user to hit enter as well)


	CPP11Features cpp11;
	cpp11.run();

	// Get any char as input.
	cout << "Learning Code Project Complete.  Hit any key to end." << endl;
	while (_kbhit() == 0) {}
	char ch = _getch();
	cout << "Char: " << ch << endl; // if we used _getch() directly here, it would output the ASCII (int) value, not the char.
	this_thread::sleep_for(chrono::seconds(3));
	return(true);
}