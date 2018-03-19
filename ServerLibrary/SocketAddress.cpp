#include "stdafx.h"

SocketAddress::SocketAddress()
{
	sockaddr_in* addressIn			= GetAsSocketAddressIn();
	addressIn->sin_family			= AF_INET;
	addressIn->sin_addr.S_un.S_addr = INADDR_ANY;
	addressIn->sin_port				= 0;
}

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	sockaddr_in* addressIn = GetAsSocketAddressIn();
	addressIn->sin_family			= AF_INET;
	addressIn->sin_addr.S_un.S_addr	= htonl(inAddress);
	addressIn->sin_port				= htons(inPort);
}

SocketAddress::SocketAddress(const sockaddr& socketAddress)
{
	memcpy_s(&this->socketAddress, sizeof(sockaddr), &socketAddress, sizeof(sockaddr));
}

string SocketAddress::ToString() const
{
#if _WIN32
	const sockaddr_in* s = GetAsSocketAddressIn();
	char destinationBuffer[128];
	InetNtop(s->sin_family,
		const_cast<in_addr*>(&s->sin_addr),
		destinationBuffer, sizeof(destinationBuffer));
	return StringUilities::Sprintf("%s : %d",
		destinationBuffer,
		ntohs(s->sin_port));
#else
	return string("not implemented on mac for now");
#endif
}
