#include "stdafx.h"

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
