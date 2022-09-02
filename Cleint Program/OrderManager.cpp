#include "OrderManager.h"

void OrderManager::addOrder(string client_ID, const std::vector<Product>& products)
{
	Order order;
	order.client_ID = client_ID;
	for (const auto& product : products) {
		product_id id = product.getId();
		auto it = purchased_products.find(id);
		if (it == purchased_products.end()) {
			auto inserted = purchased_products.emplace(id, new Product{ product });
			auto inserted_it = *inserted.first;
			order.products.emplace_back(inserted_it.second);
		}
		else {
			order.products.emplace_back(it->second);
		}
	}
	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;
}

const std::map<unsigned int, OrderManager::Order>& OrderManager::getOrders() const
{
	return orders;
}



//struct Order {
//	string client_ID;
//	vector<product_ptr> products;
//	std::tm date;
//};
//std::map<string, Order> orders;
//const ProductManager& pm;
//const ClientManager& cm;
//map<unsigned int, std::shared_ptr<Product>> purchased_products;