#include <iostream>

#include "CPP11Features.h"

using namespace std;

int main()
{
	cout << "Learning Code Project.  Hit Enter to start:" << endl;
	std::cin.get(); // gets any user input (requires user to hit enter as well)


	CPP11Features cpp11;
	cpp11.run();

	cout << "Learning Code Project Complete.  Hit Enter to end." << endl;
	std::cin.get(); // gets any user input (requires user to hit enter as well)
}