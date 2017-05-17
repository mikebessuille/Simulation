#include "stdafx.h"
#include "SocketClass.h"
#include "SocketAddress.h"
#include <iostream>
#include <string>

using namespace std;


SocketClass::SocketClass() : mSocket(INVALID_SOCKET)
{
	int result;

	// Start the service
	WORD wVersionRequested = MAKEWORD(2, 2);
	result = WSAStartup(wVersionRequested, &wsaData);
	if (result != 0)
	{
		cout << "Socket Startup failed" << result << endl;
		return;
	}

	// Create the socket
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
	{
		// Success!  We have a socket, but it's not bound to a particular address yet.
		cout << "SocketClass startup succeeded!" << endl;
		mSocket = s;
		bInitialized = true;
	}

	if (mSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect!" << endl;
		Cleanup();
		return;
	}
}


SocketClass::~SocketClass()
{
	Cleanup();
}

void SocketClass::Cleanup()
{
	bInitialized = false;
	if (mSocket != INVALID_SOCKET)
	{
		closesocket(mSocket);
	}
	WSACleanup();
}


// Returns the number of bytes actually sent, or 0 if nothing is sent.
int SocketClass::Send( const void* inData, int inLen, const SocketAddress& inTo )
{
	if (!bInitialized)
		return(-1);

	if (inLen > max_buffer_size)
		inLen = max_buffer_size;

	auto iResult = sendto(	mSocket, static_cast<const char *>(inData), inLen, 0,
							&inTo.mSockAddr, inTo.GetSize());
	if (iResult == SOCKET_ERROR)
	{
		cout << "Send failed with error: " << WSAGetLastError() << endl;
		Cleanup();
		return(0);
	}

	cout << "Bytes Sent: " << iResult << endl;
	return(iResult);
}


// Receive one packet.
// Returns the number of bytes actually received.
// TODO: Change FromPort param to a full socket address, so we can receive messages from a different machine.
int SocketClass::Receive(void * inBuffer, int inLen )
{
	if (!bInitialized)
		return(-1);
	
	if (inLen > max_buffer_size)
		inLen = max_buffer_size;

	auto iResult = recv(mSocket, static_cast<char*>(inBuffer), inLen, 0);
	if (iResult > 0)
		cout << "Bytes received: " << iResult << endl;
	else if (iResult == 0)
	{
		// Do nothing!
	}
	else
	{
		cout << "recv failed with error: " << WSAGetLastError() << endl;
		Cleanup();
	}
	return(iResult); // returns number of bytes received
}


// Binds to a particular address to start listening.  Need to call this from the server.
// Returns 0 for success
int SocketClass::Bind(const SocketAddress & inBindAddress )
{
	auto iResult = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
	if (iResult == SOCKET_ERROR)
	{
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		Cleanup();
		return(1);
	}
	return(0);
}


/*

int UDPSocket::Bind(const SocketAddress& inBindAddress)

{

	int err = bind(mSocket, &inBindAddress.mSockAddr,

		inBindAddress.GetSize());

	if (err != 0)

	{

		SocketUtil::ReportError(L"UDPSocket::Bind");

		return SocketUtil::GetLastError();

	}

	return NO_ERROR;

}



int UDPSocket::SendTo(const void* inData, int inLen,

	const SocketAddress& inTo)

{

	int byteSentCount = sendto(mSocket,

		static_cast<const char*>(inData),

		inLen,

		0, &inTo.mSockAddr, inTo.GetSize());

	if (byteSentCount >= 0)

	{

		return byteSentCount;

	}

	else

	{

		//return error as negative number

		SocketUtil::ReportError(L"UDPSocket::SendTo");

		return -SocketUtil::GetLastError();

	}

}



int UDPSocket::ReceiveFrom(void* inBuffer, int inLen,

	SocketAddress& outFrom)

{

	int fromLength = outFromAddress.GetSize();

	int readByteCount = recvfrom(mSocket,

		static_cast<char*>(inBuffer),

		inMaxLength,

		0, &outFromAddress.mSockAddr,

		&fromLength);

	if (readByteCount >= 0)

	{

		return readByteCount;

	}

	else

	{

		SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");

		return -SocketUtil::GetLastError();

	}

}



UDPSocket::~UDPSocket()

{

	closesocket(mSocket);

}

*/