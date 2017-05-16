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

void NetworkManagerClient::run()
{
	// Send an initial buffer
	char *sendbuf = "this is a test";
	auto ret = pUDPSocket->Send(sendbuf, (int)strnlen_s(sendbuf, max_buffer_size), default_server_port );
	if (ret <= 0)
	{
		cout << "Failed to send!!" << endl;
	}

	// see what the server sends back
	auto nBytesReceived(0);
	do
	{
		// TODO: I believe this is a blocking call, and shouldn't be...
		nBytesReceived = pUDPSocket->Receive(recvbuf, recvbuflen);
	} while (nBytesReceived > 0 && (IsKeyHit() == false));
}


