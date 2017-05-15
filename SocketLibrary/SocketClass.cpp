#include "stdafx.h"
#include "SocketClass.h"
#include <iostream>

using namespace std;


SocketClass::SocketClass( bool bIsServer ) : bServer( bIsServer )
{
	int result;
	WORD wVersionRequested = MAKEWORD(2, 2);
	// WSADATA wsaData;
	result = WSAStartup(wVersionRequested, &wsaData);
	if (result != 0)
	{
		cout << "Socket Startup failed" << result << endl;
	}
	else
	{
		bInitialized = true;
		if (bServer)
			cout << "Server started." << endl;
		else
			cout << "Client started." << endl;
	}
}


SocketClass::~SocketClass()
{
	WSACleanup();
}
