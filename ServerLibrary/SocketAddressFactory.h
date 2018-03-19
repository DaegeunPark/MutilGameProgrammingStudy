#pragma once
class SocketAddressFactory
{
public :
	SocketAddressFactory() = delete;

	static SocketAddressPtr CreateIPv4FromString(const string& data);
};