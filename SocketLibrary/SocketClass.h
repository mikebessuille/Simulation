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

	/*  TODO: REMOVE THIS  COMMENT 
	Relies on SocketAddress class...
	int Bind(const SocketAddress& inToAddress);
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);
	*/
	int Bind( const SocketAddress & inBindAddress );
	int Send(const void* inData, int inLen, const SocketAddress & inTo );
	int Receive(void * inBuffer, int inLen);
	void Cleanup();

private:
	WSADATA wsaData;
	bool bInitialized = false;
	SOCKET mSocket = INVALID_SOCKET;
	static const unsigned int max_buffer_size = 512;
};

