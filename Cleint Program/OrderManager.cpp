#include "OrderManager.h"
using namespace std;
using namespace OM;
using namespace PM;
bool OrderManager::addOrder(string client_ID, const string& product_ID)
{
	Order order;
	order.client_ID = client_ID;

	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	const PM::Product found = pm.findProduct(product_ID);
	if (found == PM::no_product)
		return false;

	auto itr = purchased_products.find(product_ID);
	if (itr != purchased_products.end()) {
		order.products.emplace_back(new Product{ found });
		purchased_products.emplace(product_ID, order.products.back());
	}
	else {
		order.products.emplace_back((*itr).second.lock());
	}

	auto created_order = orders.emplace(order_id++, std::move(order));
	orders_by_client_id.emplace(client_ID, &(created_order.first)->second);
	return true;
}
//OrderIterator getOrders(const string& client_ID) const;

OM::OrderIterator OM::OrderManager::getOrders(const string& client_ID)
{
	auto tmp2 = this->orders_by_client_id.equal_range(client_ID);

	using itr_type = std::multimap<string, OM::OrderManager::Order*>::const_iterator;

	return OM::OrderIterator(tmp2.first, tmp2.second);
}