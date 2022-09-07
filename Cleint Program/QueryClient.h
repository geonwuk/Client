#pragma once
#include "ClientManager.h"
#include <array>
#include "Table.h"

namespace CM{
	class QueryClient
	{
	public:
		QueryClient(ClientManager& cm);
		void QueryAddClient();
		void QueryEraseClient();
		void QueryShowClient();
		void QuerySaveClient();
		void QueryLoadClient();
	private:
		ClientManager& cm;
		static TB::Table table;
	};
}
