#include "stdafx.h"
#include "NetworkManagerClient.h"
#include "SocketClass.h"

#include <iostream>
#include <memory>

using namespace std;


NetworkManagerClient::NetworkManagerClient()
{
	pUDPSocket = make_shared<SocketClass>();
	if (pUDPSocket && pUDPSocket->IsInitialized())
	{
		cout << "Client started." << endl;
	}
	else
	{
		cout << "Client Startup failed." << endl;
		pUDPSocket = nullptr;
	}
}


NetworkManagerClient::~NetworkManagerClient()
{
}


// TODO:  Change this method so that it can be run from a game.  It should either run on a separate thread, receiving messages into a
// message collection of some kind, for later processing by the game engine.  Or (preferrably) it should be a call every game-loop
// and process some small number of messages each game loop; make sure it can process all the messages available from all the clients,
// on each game loop.

// TODO:  Support more than localhost, by passing in a command-line argument with the server IP address to all clients?
void NetworkManagerClient::run()
{
	// Send an initial buffer
	char *sendbuf = "this is a test";

	string addrString = "localhost:" + default_server_port;
	cout << "Client sending to server at: " << addrString << endl;
	m_pServerAddress = SocketAddressFactory::CreateIPv4FromString( addrString );

	auto ret = pUDPSocket->Send(sendbuf, (int)strnlen_s(sendbuf, max_buffer_size), (*m_pServerAddress) );
	if (ret <= 0)
	{
		cout << "ERROR: Failed to send!!" << endl;
	}

	// see what the server sends back
	do
	{
		ProcessMessages();
	} while( IsKeyHit() == false );
}


bool NetworkManagerClient::HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr)
{
	if (nBytesReceived > 0)
	{
		string recvStr(msgbuf, msgbuf + nBytesReceived );
		cout << endl << "Received: [" << recvStr << "]" << endl;
		return(true);
	}	
	return(false);
}