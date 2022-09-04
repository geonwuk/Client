#pragma once
#include "OrderManager.h"

class QueryOrder
{
public:
	QueryOrder(OM::OrderManager& om) : om{ om } {}
	void QueryShowOrder();
	void QueryAddOrder();
private:
	OM::OrderManager& om;
};

