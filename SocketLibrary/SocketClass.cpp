#include "stdafx.h"
#include "SocketClass.h"
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
int SocketClass::Send( const void* inData, int inLen, string ToPort )
{
	if (!bInitialized)
		return(-1);

	if (inLen > max_buffer_size)
		inLen = max_buffer_size;

	struct addrinfo *resultAddr = NULL,
		*addr = NULL,
		hints;

	// Get the address
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // was AF_UNSPEC
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	// Resolve the server address and port
	auto iResult = getaddrinfo("localhost", ToPort.c_str(), &hints, &resultAddr);
	if (iResult != 0)
	{
		cout << "getaddrinfo failed: " << iResult << endl;
		WSACleanup();
		return(1);
	}

	iResult = sendto(	mSocket, static_cast<const char *>(inData), inLen, 0,
						resultAddr->ai_addr, (int)resultAddr->ai_addrlen );
	freeaddrinfo(resultAddr); // TODO: Instead of creating and destroying this address every time, we should store it
	// in the NetworkManagerClient class and reuse the address each time.  The address, not the port, shoudl be passed 
	// to this send method.
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
int SocketClass::Receive(void * inBuffer, int inLen)
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
int SocketClass::Bind( string ListenPort )
{
	struct addrinfo *resultAddr = NULL,
					*addr = NULL,
					hints;

	// Get the address
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // was AF_UNSPEC
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	// Resolve the server address and port
	auto iResult = getaddrinfo("localhost", ListenPort.c_str(), &hints, &resultAddr);
	if (iResult != 0)
	{
		cout << "getaddrinfo failed: " << iResult << endl;
		WSACleanup();
		return(1);
	}

	iResult = bind(mSocket, resultAddr->ai_addr, (int)resultAddr->ai_addrlen);
	freeaddrinfo(resultAddr);
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