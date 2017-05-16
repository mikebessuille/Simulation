#pragma once

#include "stdafx.h"
#include <memory>

#include "SocketClass.h"
#include "NetworkManager.h"


class NetworkManagerServer : public NetworkManager
{
public:
	NetworkManagerServer();
	~NetworkManagerServer();
	void run();

private:
	// Client address; this should become a collection of client sockets

	shared_ptr<SocketClass> pUDPSocket{ nullptr };
};

