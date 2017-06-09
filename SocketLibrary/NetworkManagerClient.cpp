#include "stdafx.h"
#include "NetworkManagerClient.h"
#include "SocketClass.h"

#include <iostream>
#include <memory>
#include <chrono>

using namespace std;


NetworkManagerClient::NetworkManagerClient()
{
	pUDPSocket = make_shared<SocketClass>();
	if (pUDPSocket && pUDPSocket->IsInitialized())
	{
		cout << "Client started." << endl;
		
		string addrString = "localhost:" + default_server_port;
		cout << "Client will communicate with server at: " << addrString << endl;
		m_pServerAddress = SocketAddressFactory::CreateIPv4FromString(addrString);
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


// This is an example game loop to test sockets.  Don't use this method in a real application.
// TODO:  Support more than localhost, by passing in a command-line argument with the server IP address to all clients?
void NetworkManagerClient::run()
{
	if (pUDPSocket && pUDPSocket->IsInitialized() && m_pServerAddress)
	{
		if (ConnectToServer())
		{

			chrono::system_clock::time_point startTime = chrono::system_clock::now();
			const chrono::seconds pingRate{ chrono::seconds(1) };
			cout << "Hit any key to stop the client." << endl;
			do
			{
				// see what the server sends back
				ProcessMessages();

				if (chrono::system_clock::now() > (startTime + pingRate))
				{
					startTime = chrono::system_clock::now();
					PingServer();
				}
			} while (IsKeyHit() == false);
		}
	}
	else
	{
		cout << "ERROR: NetworkManagerClient::run() called when not initialized!" << endl;
	}
}


bool NetworkManagerClient::HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr)
{
	if (nBytesReceived > 0)
	{
		string recvStr(msgbuf, msgbuf + nBytesReceived );
		cout << "Received: [" << recvStr << "]" << endl;
		return(true);
	}	
	return(false);
}


bool NetworkManagerClient::ConnectToServer()
{
	{
		// Send an initial connection message
		char *sendbuf = "this is a test";
		auto ret = pUDPSocket->Send(sendbuf, (int)strnlen_s(sendbuf, max_buffer_size), (*m_pServerAddress));
		if (ret <= 0)
		{
			cout << "ERROR: Failed to send!!" << endl;
			return(false);
		}
		else
			return(true);
	}
	return(false);
}


bool NetworkManagerClient::PingServer()
{
	{
		// Send an initial connection message
		char *sendbuf = ".";
		auto ret = pUDPSocket->Send(sendbuf, (int)strnlen_s(sendbuf, max_buffer_size), (*m_pServerAddress));
		if (ret <= 0)
		{
			cout << "ERROR: Failed to send!!" << endl;
			return(false);
		}
		else
			return(true);
	}
	return(false);
}