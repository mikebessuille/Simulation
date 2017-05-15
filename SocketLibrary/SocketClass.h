#pragma once

#include "stdafx.h"

class SocketClass
{
public:
	SocketClass(bool bIsServer);
	SocketClass() : SocketClass(false) {};
	virtual ~SocketClass();

private:
	WSADATA wsaData;
	bool bInitialized = false;
	bool bServer = false;
};

