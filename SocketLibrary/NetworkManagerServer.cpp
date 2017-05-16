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

	auto iResult = pUDPSocket->Bind(default_server_port);
	if (iResult != 0)
	{
		cout << "Server failed to bind" << endl;
		return;
	}

	do
	{
		// TODO: Listen for clients.
		// If it's a new client, add it to the list.
		// Otherwise, just receive its messages.

		cout << ".";

	} while (IsKeyHit() == false);

/*
	// Send an initial buffer
	char *sendbuf = "this is a test";
	auto ret = pUDPSocket->Send(sendbuf, (int)strnlen_s(sendbuf, max_buffer_size));
	if (ret <= 0)
	{
		cout << "Failed to send!!" << endl;
	}

	// see what the server sends back
	auto nBytesReceived(0);
	do
	{
		nBytesReceived = pUDPSocket->Receive(recvbuf, recvbuflen);
	} while (nBytesReceived > 0);
*/

}