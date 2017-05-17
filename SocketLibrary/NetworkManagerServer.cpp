#include "stdafx.h"
#include "NetworkManagerServer.h"
#include <iostream>
#include <conio.h>

using namespace std;

NetworkManagerServer::NetworkManagerServer()
{
	pUDPSocket = make_shared<SocketClass>();
	if (pUDPSocket && pUDPSocket->IsInitialized())
	{
		cout << "Server started." << endl;
	}
	else
	{
		cout << "Server Startup failed." << endl;
		pUDPSocket = nullptr;
	}
}


NetworkManagerServer::~NetworkManagerServer()
{
}


void NetworkManagerServer::run()
{
	cout << "Hit any key to stop the server." << endl;

	if ( !pUDPSocket || !pUDPSocket->IsInitialized())
	{
		cout << "Called Run when the server is not initialized!" << endl;
		return;
	}

	string addrString = "localhost:" + default_server_port;
	cout << "Trying to bind to: " << addrString << endl;
	SocketAddressPtr pServerAddress = SocketAddressFactory::CreateIPv4FromString( addrString );
	auto iResult = pUDPSocket->Bind( (*pServerAddress) );
	if (iResult != 0)
	{
		cout << "Server failed to bind" << endl;
		return;
	}

	do
	{
		// TODO: Listen for clients.
		// If it's a new client (not yet in our list), add it to the list.
		// Otherwise, just receive its messages.
		auto nBytesReceived = pUDPSocket->Receive(recvbuf, recvbuflen);
		if (nBytesReceived > 0)
		{
			// TODO: Make this non-blocking
			// 
			string recvStr(recvbuf, recvbuf + nBytesReceived );
			cout << endl << "Received: [" << recvStr << "]" << endl;
		}
		else
		{
			cout << ".";
			// Nothing received
		}

	} while (IsKeyHit() == false);
}