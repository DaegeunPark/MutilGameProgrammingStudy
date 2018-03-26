#pragma once

enum SocketAddressFamily
{
	INET	= AF_INET,
	INET6	= AF_INET6
};

class SocketUtility
{
public:
	SocketUtility() = delete;

	static bool Initialize();
	static void CleanUp();

	static void ReportError(const char* operationDesc);
	static int	GetLastError();

	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily family);
	static TCPSocketPtr CreateTCPSocket(SocketAddressFamily family);
};

