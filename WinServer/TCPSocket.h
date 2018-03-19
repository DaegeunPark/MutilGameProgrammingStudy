#pragma once

class TCPSocket;
using TCPSocketPtr = shared_ptr<TCPSocket>;

class TCPSocket
{
public:
	~TCPSocket();
	TCPSocket(const TCPSocket&)				= delete;
	TCPSocket& operator=(const TCPSocket&)	= delete;

	int						Connect(const SocketAddress& address);
	int						Bind(const SocketAddress& toAddress);
	int						Listen(int backlog = 32);
	TCPSocketPtr	Accept(SocketAddress& fromAddress);
	int						Send(const void* data, int length);
	int						Receive(void* buffer, int length);

private :
	friend class SocketUtility;
	TCPSocket(SOCKET socket);

private :
	SOCKET socket;
};

