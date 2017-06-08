#pragma once

#include "SocketClass.h"
#include <string>
#include <conio.h>

using namespace std;

class NetworkManager
{
public:
	NetworkManager();
	virtual ~NetworkManager();
	virtual void run() = 0; // pure virtual, must be overridden
	int ProcessMessages(); // Processes messages while there are still some to process.  Returns # of messages received.

protected:
	virtual bool HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr) = 0; // Processes a single message.  Will be different on client & server.

protected:
	// const string default_port = "27015";
	static const unsigned int default_buffer_size = 512;
	static const unsigned int max_buffer_size = 512;
	char recvbuf[default_buffer_size];
	int recvbuflen = default_buffer_size;
	const string default_server_port = "27015";
	const string default_client_port = "27020";
	shared_ptr<SocketClass> pUDPSocket{ nullptr }; // The UDP socket this NetworkManager is listening to.  (Single socket for all clients, if this is the server).

private:
	static const int MAX_MESSAGES_PER_FRAME{ 10 }; // max number of messages to process each time ProcessMessages() is called, to avoid hanging
};


// Not a member function!
bool IsKeyHit();