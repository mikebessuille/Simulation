#pragma once

#include "stdafx.h"
#include "SocketClass.h"
#include "NetworkManager.h"

#include <memory>


class NetworkManagerClient : public NetworkManager
{
public:
	NetworkManagerClient();
	~NetworkManagerClient();
	virtual void run();

protected:
	virtual bool HandleMessage(char * msgbuf, int msgbuflen, int nBytesReceived, SocketAddress senderAddr);

private:
	SocketAddressPtr m_pServerAddress{ nullptr };
};

