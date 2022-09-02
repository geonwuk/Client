#pragma once
#include "OrderManager.h"
class QueryOrder
{
public:
	QueryOrder(OrderManager& om) : om{ om } {}

	void QueryShowOrder();
	void QueryAddOrder();
private:
	OrderManager& om;
};

