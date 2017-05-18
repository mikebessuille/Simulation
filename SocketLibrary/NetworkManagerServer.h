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
	// Client address collection (all clients that have sent packets to this server).
	// TODO...

	// Single socket listening for all clients.
	shared_ptr<SocketClass> pUDPSocket{ nullptr };
};

