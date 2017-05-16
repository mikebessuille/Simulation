#include "stdafx.h"
#include "NetworkManager.h"


NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}


// Not a member function!
bool IsKeyHit()
{
	// Check if any kit was just hit
	if (_kbhit() != 0)
	{
		char ch = _getch(); // to clear the buffer, so future calls to kbhit will return false.
		return true;
	}
	return false;
}