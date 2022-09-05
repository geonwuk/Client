#pragma once
#include "ClientManager.h"
class QueryClient
{
public:
	QueryClient(ClientManager& cm) : cm{ cm } {}

	void QueryAddClient();
	void QueryEraseClient();
	void QueryShowClient();

private:
	ClientManager& cm;
	static const unsigned int padding;
	static unsigned int id_f;
	static unsigned int name_f; //= string("name").size();
	static unsigned int phone_f;
	static unsigned int address_f;

};

