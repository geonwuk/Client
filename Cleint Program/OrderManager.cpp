#include "OrderManager.h"

using namespace std;
using namespace OM;
using namespace PM;

const Product& OM::OrderManager::getPurchasedProducts(const Product_ID pid) const
{
	auto it = purchased_products.find(pid);
	if (it == purchased_products.end()) {
		return no_product;
	}
	else {
		return it->second;
	}
}

int OrderManager::addOrder(const unsigned int client_id, vector<unsigned int> product_ids)
{
	Order order;

	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	for (auto product_id : product_ids) {
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			return -1;
		auto itr = purchased_products.find(product_id);
		if (itr == purchased_products.end()){
			purchased_products.emplace(product_id, Product{ found });
		}
		order.products.emplace_back(found.getId());
	}
	order.order_id = order_id;
	order.client_id = client_id;
	auto inserted_order = orders.emplace(order_id, std::move(order));
	orders_CID.emplace(client_id, &inserted_order.first->second);


	return order_id++;
}

OrderIterator OrderManager::getOrders(const unsigned int client_id) const
{
	auto tmp2 = orders.equal_range(client_id);
	return OrderIterator(tmp2.first, tmp2.second);
}

OrderIterator OrderManager::getOrders() const
{
	return OrderIterator(orders.begin(), orders.end());
}

const OrderManager::Order& OrderManager::getOrder(const Order_ID order_id) const {
	//todo: emptyOrder
	try {
		orders.at(order_id);
	}
	catch(std::out_of_range){
		return OrderManager::Order{};
	}
	return OrderManager::Order{};
}


