#pragma once

class UDPSocket;
using UDPSocketPtr = shared_ptr<UDPSocket>;

class UDPSocket
{
public:
	~UDPSocket();
	UDPSocket(const UDPSocket&)				= delete;
	UDPSocket& operator=(const UDPSocket&)	= delete;

	int Bind(const SocketAddress& bindAddress);
	int SendTo(const void* data, int length, const SocketAddress& toAddress);
	int ReceiveFrom(void* buffer, int length, SocketAddress& fromAddress);

private :
	friend class SocketUtility;
	UDPSocket(SOCKET socket);

private :
	SOCKET socket;
};