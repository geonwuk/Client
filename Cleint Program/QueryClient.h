#pragma once
#include "ClientManager.h"
#include <array>
#include "Table.h"

class QueryClient
{
public:
	QueryClient(ClientManager& cm);

	void QueryAddClient();
	void QueryEraseClient();
	void QueryShowClient();
	void QueryLoadClient()const;
	void QuerySaveClient();

private:
	ClientManager& cm;

	static TB::Table table;
};

