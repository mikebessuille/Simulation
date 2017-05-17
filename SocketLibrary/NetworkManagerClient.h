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
	void run();

private:
	shared_ptr<SocketClass> pUDPSocket{ nullptr };
	SocketAddressPtr m_pServerAddress{ nullptr };
};

