#include "ServerLibraryPCH.h"

bool SocketUtility::Initialize()
{
#if _WIN32
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR)
	{
		ReportError("Starting Up");
		return false;
	}
#endif
	return true;
}

void SocketUtility::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif
}

void SocketUtility::ReportError(const char * operationDesc)
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	LOG("Error %s : %d - %s", operationDesc, errorNum, lpMsgBuf);
#else
	LOG("Error : %s", operationDesc);
#endif
}

int SocketUtility::GetLastError()
{
#if _WIN32
	return  WSAGetLastError();
#else
	return errno;
#endif
}

UDPSocketPtr SocketUtility::CreateUDPSocket(SocketAddressFamily family)
{
	SOCKET newSocket = socket(family, SOCK_DGRAM, IPPROTO_UDP);
	if (newSocket != INVALID_SOCKET)
		return UDPSocketPtr(new UDPSocket(newSocket));
	else
	{
		ReportError("SocketUtility::CreateUDPSocket");
		return nullptr;
	}
}

TCPSocketPtr SocketUtility::CreateTCPSocket(SocketAddressFamily family)
{
	SOCKET newSocket = socket(family, SOCK_STREAM, IPPROTO_TCP);
	if (newSocket != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(newSocket));
	else
	{
		ReportError("SocketUtility::CreateUDPSocket");
		return nullptr;
	}
}
