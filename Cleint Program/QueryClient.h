#pragma once
#include "ClientManager.h"
class QueryClient
{
public:
	QueryClient(ClientManager& cm) : cm{ cm } {}

	void QueryAddClient();
	void QueryEraseClient();
	void QueryTest();
	void QueryShowClient();

private:
	ClientManager& cm;
};

