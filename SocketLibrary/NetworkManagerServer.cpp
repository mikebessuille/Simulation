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

		// Bind to the default server port so that the server starts listening for clients.
		string addrString = "localhost:" + default_server_port;
		cout << "Trying to bind to: " << addrString << endl;
		SocketAddressPtr pServerAddress = SocketAddressFactory::CreateIPv4FromString(addrString);
		auto iResult = pUDPSocket->Bind((*pServerAddress));
		if (iResult != 0)
		{
			cout << "ERROR: Server failed to bind" << endl;
			return;
		}
	}
	else
	{
		cout << "ERROR: Server Startup failed." << endl;
		pUDPSocket = nullptr;
	}
}


NetworkManagerServer::~NetworkManagerServer()
{
}


void NetworkManagerServer::run()
{
	if ( !pUDPSocket || !pUDPSocket->IsInitialized())
	{
		cout << "ERROR: Called Run when the server is not initialized!" << endl;
		return;
	}

	cout << "Hit any key to stop the server." << endl;
	do
	{
		ProcessMessages();
	} while (IsKeyHit() == false);
}


bool NetworkManagerServer::HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr)
{
	if (nBytesReceived > 0)
	{
		string recvStr(msgbuf, msgbuf + nBytesReceived);
		cout << "Received: [" << recvStr << "]" << endl;

		// TODO:
		// If it's a new client (not yet in our list), add it to the list.
		// Otherwise, just receive its messages.

		// send a response
		string responseStr("Got it!");
		const char * responseChar = responseStr.c_str();
		auto iResult = pUDPSocket->Send(responseChar, responseStr.size(), senderAddr);
		if (iResult <= 0)
		{
			cout << "ERROR: Failed to send the response!!" << endl;
			return(false);
		}

		return(true);
	}
	return(false);
}