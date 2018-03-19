#pragma once
class SocketAddress
{
public:
	SocketAddress();
	SocketAddress(uint32_t inAddress, uint16_t inPort);
	SocketAddress(const sockaddr& socketAddress);

	string ToString() const;

	const size_t GetSize() const { return sizeof(sockaddr); }

private :
	friend class UDPSocket;
	friend class TCPSocket;

	sockaddr_in*		GetAsSocketAddressIn()			{ return reinterpret_cast<sockaddr_in*>(&socketAddress);		}
	const sockaddr_in*	GetAsSocketAddressIn() const	{ return reinterpret_cast<const sockaddr_in*>(&socketAddress);	}

private:
	sockaddr socketAddress;
};

using SocketAddressPtr = std::shared_ptr<SocketAddress>;