#include "stdafx.h"

SocketAddressPtr SocketAddressFactory::CreateIPv4FromString(const string & data)
{
	auto	pos		= data.find_last_of(':');
	string	host	= "";
	string	service	= "";

	if (pos != string::npos)
	{
		host	= data.substr(0, pos);
		service = data.substr(pos + 1);
	}
	else
	{
		host	= data;
		service = "0";
	}

	addrinfo configInfo;
	memset(&configInfo, 0, sizeof(configInfo));
	configInfo.ai_family = AF_INET;

	addrinfo* resultInfos = nullptr;
	int error = getaddrinfo(host.c_str(), service.c_str(), &configInfo, &resultInfos);
	addrinfo* firstResultInfo = resultInfos;

	if (error != 0 && resultInfos != nullptr)
	{
		freeaddrinfo(firstResultInfo);
		return nullptr;
	}

	while (!resultInfos->ai_addr && resultInfos->ai_next)
	{
		resultInfos = resultInfos->ai_next;
	}

	if (!resultInfos->ai_addr)
	{
		freeaddrinfo(firstResultInfo);
	}

	auto toRet = std::make_shared<SocketAddress>(*resultInfos->ai_addr);
	
	freeaddrinfo(firstResultInfo);
	return toRet;
}
