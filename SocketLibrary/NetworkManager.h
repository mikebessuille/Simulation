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

protected:
	// const string default_port = "27015";
	static const unsigned int default_buffer_size = 512;
	static const unsigned int max_buffer_size = 512;
	char recvbuf[default_buffer_size];
	int recvbuflen = default_buffer_size;
	const string default_server_port = "27015";
	const string default_client_port = "27020";
};


// Not a member function!
bool IsKeyHit();