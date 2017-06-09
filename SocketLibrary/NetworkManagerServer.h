#pragma once

#include "stdafx.h"
#include <memory>
#include <vector>

#include "SocketClass.h"
#include "NetworkManager.h"


class NetworkManagerServer : public NetworkManager
{
public:
	NetworkManagerServer();
	~NetworkManagerServer();
	virtual void run();

protected:
	virtual bool HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr);

private:
	bool HandleNew(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr);
	bool HandleExisting(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr);

private:
	vector<SocketAddress> clientSocketAddresses;  // Client address collection (all clients that have sent packets to this server).
};

