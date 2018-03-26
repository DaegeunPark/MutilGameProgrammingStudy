// TestClient.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

int main()
{
	TCPSocketPtr socket = SocketUtility::CreateTCPSocket(SocketAddressFamily::INET);
	SocketAddressPtr socketAddress = SocketAddressFactory::CreateIPv4FromString("localhost:8080");
	socket->Bind(*socketAddress);
    return 0;
}
 
