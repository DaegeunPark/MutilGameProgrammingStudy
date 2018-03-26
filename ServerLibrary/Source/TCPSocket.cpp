#include "ServerLibraryPCH.h"

TCPSocket::TCPSocket(SOCKET socket)
	: socket(socket)
{

}

TCPSocket::~TCPSocket()
{
#if _WIN32
	closesocket(socket);
#else
	close(socket);
#endif
}

int TCPSocket::Connect(const SocketAddress & address)
{
	int error = connect(socket, &address.socketAddress, address.GetSize());
	if (error < 0)
	{
		SocketUtility::ReportError("TCPSocket::Connect");
		return -SocketUtility::GetLastError();
	}
	return NO_ERROR;
}

int TCPSocket::Bind(const SocketAddress & toAddress)
{
	int error = bind(socket, &toAddress.socketAddress, toAddress.GetSize());
	if (error != 0)
	{
		SocketUtility::ReportError("TCPSocket::Bind");
		return -SocketUtility::GetLastError();
	}

	return NO_ERROR;
}

int TCPSocket::Listen(int backlog)
{
	int error = listen(socket, backlog);
	if (error < 0)
	{
		SocketUtility::ReportError("TCPSocket::Listen");
		return -SocketUtility::GetLastError();
	}
	return NO_ERROR;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& fromAddress)
{
	socklen_t length = fromAddress.GetSize();
	SOCKET newSocket = accept(socket, &fromAddress.socketAddress, &length);
	
	if (newSocket != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(newSocket));
	else
	{
		SocketUtility::ReportError("TCPSocket::Accept");
		return nullptr;
	}
}

int32_t TCPSocket::Send(const void * data, int length)
{
	int bytesSentCount = send(socket, static_cast<const char*>(data), length, 0);
	if (bytesSentCount < 0)
	{
		SocketUtility::ReportError("TCPSocket::Send");
		return -SocketUtility::GetLastError();
	}
	else
		return bytesSentCount;
}

int32_t TCPSocket::Receive(void * buffer, int length)
{
	int bytesReceivedCount = recv(socket, static_cast<char*>(buffer), length, 0);
	if (bytesReceivedCount < 0)
	{
		SocketUtility::ReportError("TCPSocket::Receive");
		return -SocketUtility::GetLastError();
	}
	else
		return bytesReceivedCount;
}
