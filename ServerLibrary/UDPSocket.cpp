#include "stdafx.h"


UDPSocket::UDPSocket(SOCKET socket)
	: socket(socket)
{
}


UDPSocket::~UDPSocket()
{
#if _WIN32
	closesocket(socket);
#else
	close(socket);
#endif
}

int UDPSocket::Bind(const SocketAddress & bindAddress)
{
	int error = bind(socket, &bindAddress.socketAddress, bindAddress.GetSize());
	if (error != 0)
	{
		SocketUtility::ReportError("UDPSOcket::Bind");
		return SocketUtility::GetLastError();
	}

	return NO_ERROR;
}

int UDPSocket::SendTo(const void * data, int length, const SocketAddress & toAddress)
{
	int byteSentCount = sendto(socket,
		static_cast<const char*>(data),
		length,
		0, &toAddress.socketAddress, toAddress.GetSize());

	if (byteSentCount <= 0)
	{
		SocketUtility::ReportError("UDPSocket::SendTo");
		return -SocketUtility::GetLastError();
	}
	else
		return byteSentCount;
}

int UDPSocket::ReceiveFrom(void * buffer, int length, SocketAddress & fromAddress)
{
	socklen_t fromLength = fromAddress.GetSize();
	int readByteCount = recvfrom(socket,
		static_cast<char*>(buffer),
		length,
		0, &fromAddress.socketAddress, &fromLength);

	if (readByteCount >= 0)
		return readByteCount;
	else
	{
		int error = SocketUtility::GetLastError();
		if (error == WSAEWOULDBLOCK)
			return 0;
		else if (error == WSAECONNRESET)
		{
			LOG("Connection Reset from %s", fromAddress);
			return -WSAECONNRESET;
		}
		else
		{
			SocketUtility::ReportError("UDPSocket::ReceiveFrom");
			return -error;
		}
	}
}
