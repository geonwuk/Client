#include "OrderManager.h"
using namespace std;
using namespace OM;
using namespace PM;
bool OrderManager::addOrder(const unsigned int client_id, vector<unsigned int> product_ids)
{
	Order order;
	order.client_id = client_id;

	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	for (auto product_id : product_ids) {
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			return false;

		auto itr = purchased_products.find(product_id);
		if (itr == purchased_products.end() || itr->second.expired()) { //2번째 컨디션은 상품은 그대로 있는데 관련 오더가 지워지고 혹시 erase가 잘못 코딩 되어 있을 떄를 대비
			order.products.emplace_back(new Product{ found });
			purchased_products.emplace(product_id, order.products.back());
		}
		else {
			(orders.find(client_id)->second).products.emplace_back(itr->second.lock());
		}
	}

	orders.emplace(order_id++, std::move(order));

	return true;
}

OrderIterator OrderManager::getOrders(const unsigned int client_id) const
{
	auto tmp2 = orders.equal_range(client_id);
	return OrderIterator(tmp2.first, tmp2.second);
}