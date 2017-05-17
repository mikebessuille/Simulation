#pragma once

#include "stdafx.h"
#include "SocketClass.h"
#include "SocketAddress.h"

#include <string>

using namespace std;

class SocketClass
{
public:
	SocketClass();
	virtual ~SocketClass();
	bool IsInitialized() { return(bInitialized); }

	int Bind( const SocketAddress & inBindAddress );
	int Send(const void* inData, int inLen, const SocketAddress & inTo );
	int Receive(void * inBuffer, int inLen, SocketAddress & outFrom);
	void Cleanup();

private:
	WSADATA wsaData;
	bool bInitialized = false;
	SOCKET mSocket = INVALID_SOCKET;
	static const unsigned int max_buffer_size = 512;
};

