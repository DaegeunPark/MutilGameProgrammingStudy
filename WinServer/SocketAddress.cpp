#include "stdafx.h"

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	GetAsSocketAddressIn()->sin_family				= AF_INET;
	GetAsSocketAddressIn()->sin_addr.S_un.S_addr	= htonl(inAddress);
	GetAsSocketAddressIn()->sin_port				= htons(inPort);
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
