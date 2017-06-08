#include "stdafx.h"
#include "NetworkManager.h"

#include <iostream>


NetworkManager::NetworkManager()
{
}


NetworkManager::~NetworkManager()
{
}


// This should be a call every game-loop and process some small number of messages each game loop;
// make sure it can process all the messages available from all the clients, on each game loop.
// Returns the number of messages received.
int NetworkManager::ProcessMessages()
{
	if (!pUDPSocket || !pUDPSocket->IsInitialized())
	{
		cout << "ERROR: Called ProcessMessages() when the socket is not initialized!" << endl;
		return( -1 );
	}

	auto nBytesReceived(0);
	int nNumMessages(0);
	do
	{
		SocketAddress senderAddr;
		nBytesReceived = pUDPSocket->Receive(recvbuf, recvbuflen, senderAddr);
		if (nBytesReceived > 0)
		{
			HandleMessage( recvbuf, recvbuflen, nBytesReceived, senderAddr );
			nNumMessages++;
		}
	} while( nBytesReceived > 0 && nNumMessages < MAX_MESSAGES_PER_FRAME );
	return( nNumMessages );
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