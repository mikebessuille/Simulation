#include "stdafx.h"
#include "SocketAddress.h"
#include <iostream>


/*
string	SocketAddress::ToString() const
{
	const sockaddr_in* s = GetAsSockAddrIn();
	char destinationBuffer[128];
	InetNtop(s->sin_family, const_cast< in_addr* >(&s->sin_addr), destinationBuffer, sizeof(destinationBuffer));

	return StringUtils::Sprintf("%s:%d",
		destinationBuffer,
		ntohs(s->sin_port));
}


string StringUtils::Sprintf(const char* inFormat, ...)
{
	//not thread safe...
	static char temp[4096];

	va_list args;
	va_start(args, inFormat);

#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
	vsnprintf(temp, 4096, inFormat, args);
#endif
	return string(temp);
}
*/

SocketAddressPtr SocketAddressFactory::CreateIPv4FromString(const string& inString)
{
	auto pos = inString.find_last_of(':');
	string host, service;
	if (pos != string::npos)
	{
		host = inString.substr(0, pos);
		service = inString.substr(pos + 1);
	}
	else // there is no colon; the address is just an IP address.
	{
		host = inString;
		//use default port...
		service = "0";
	}
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	addrinfo* resultAddr; // will be allocated by getaddrinfo()
	int error = getaddrinfo(host.c_str(), service.c_str(), &hints, &resultAddr);
	if (error != 0 && resultAddr != nullptr)
	{
		cout << "Could not create address!" << endl;
		return nullptr;
	}

	while (!resultAddr->ai_addr && resultAddr->ai_next)
	{
		resultAddr = resultAddr->ai_next;
	}

	if (!resultAddr->ai_addr)
	{
		freeaddrinfo(resultAddr);
		return nullptr;
	}

	auto toRet = std::make_shared< SocketAddress >(*resultAddr->ai_addr);

	freeaddrinfo(resultAddr);

	return toRet;

}