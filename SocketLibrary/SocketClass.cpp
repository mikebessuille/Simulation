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
		cout << "ERROR: Socket Startup failed" << result << endl;
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
		cout << "ERROR: Unable to connect!" << endl;
		Cleanup();
		return;
	}

	// Set non-blocking mode so Bind/Send/Receive methods don't block.
	u_long arg = 1;
	result = ioctlsocket(mSocket, FIONBIO, &arg);
	if (result == SOCKET_ERROR)
	{
		cout << "ERROR: Unable to set to non-blocking!" << endl;
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
		cout << "ERROR: Send failed with error: " << WSAGetLastError() << endl;
		Cleanup();
		return(0);
	}

	cout << "Bytes Sent: " << iResult << endl;
	return(iResult);
}


// Receive one packet.
// Returns the number of bytes actually received.
int SocketClass::Receive(void * inBuffer, int inLen, SocketAddress & outFrom )
{
	if (!bInitialized)
		return(-1);
	
	if (inLen > max_buffer_size)
		inLen = max_buffer_size;
	
	int fromLength = outFrom.GetSize();

	auto bytes = recvfrom(mSocket, static_cast<char*>(inBuffer), inLen, 0, &outFrom.mSockAddr, &fromLength );
	if (bytes > 0)
	{
		cout << "Bytes received: " << bytes << endl;
	}
	else if (bytes == 0)
	{
		// Received, but no bytes.  Do nothing!
	}
	else if (bytes == -1)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			// Receive would have blocked, but nothing was received.
			// Do nothing!
		}
		else
		{
			cout << "ERROR: receive returned -1 but error code not as expected." << endl;
			Cleanup();
		}
	}
	else
	{
		cout << "ERROR: recv failed with error: " << WSAGetLastError() << endl;
		Cleanup();
	}
	return( bytes ); // returns number of bytes received
}


// Binds to a particular address to start listening.  Need to call this from the server.
// Returns 0 for success
int SocketClass::Bind(const SocketAddress & inBindAddress )
{
	auto iResult = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());
	if (iResult == SOCKET_ERROR)
	{
		cout << "ERROR: bind failed with error: " << WSAGetLastError() << endl;
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