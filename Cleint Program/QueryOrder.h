#pragma once
#include "OrderManager.h"
#include "Table.h"
namespace OM {
	class QueryOrder
	{
	public:
		QueryOrder(OM::OrderManager& om) : om{ om } {}
		void QueryAddOrder();
		void QueryEraseOrder();
		void QueryShowOrder();
		void QuerySaveOrder();
		void QueryLoadOrder();
	private:
		OM::OrderManager& om;
		static TB::Table table;
	};
}


