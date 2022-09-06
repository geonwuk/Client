#include "OrderManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
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

std::pair<const unsigned int, bool> OrderManager::addOrder(const Client_ID client_id, vector<unsigned int> product_ids)
{
	Order order;

	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	for (auto product_id : product_ids) {
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			return { product_id,false };
		auto itr = purchased_products.find(product_id);
		if (itr == purchased_products.end()) {
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(&inserted.first->second);
		}
		else {
			order.products.emplace_back(&itr->second);
		}
	}
	order.order_id = order_id;
	order.client_id = client_id;
	auto inserted_order = orders.emplace(order_id, std::move(order));
	orders_CID.emplace(client_id, &inserted_order.first->second);


	return {order_id++, true};
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
static std::ofstream& operator<< (std::ofstream& out, tm p) {
	out << std::put_time(&p, "%A %c");
	return out;
}
static std::ofstream& operator<<(std::ofstream& out, const OrderManager::Order& o)
{
	out << o.order_id << ',' << o.client_id << ',';
	out << o.date;
	for (auto product : o.products) {
		const Product& p = *product;
		out << p.getId() << ',' << p.getName() << ',' << p.getPrice();
	}
	return out;
}

std::ofstream& OM::OrderManager::saveOrders(std::ofstream& out) const
{
	for (const auto& p : orders) {
		out << p.second << endl;
	}
	return out;
}

std::pair<std::ifstream&, std::vector<OrderManager::Order>> OM::OrderManager::loadOrders(ifstream& in)
{
	vector<Order> order_vector;
	vector<Product*> products;
	std::string str;
	while (getline(in, str)) {
		vector<string> tmp;
		auto begIdx = str.find_first_not_of(',');
		while (begIdx != string::npos) {
			auto endIdx = str.find_first_of(',', begIdx);
			if (endIdx == string::npos) {
				endIdx = str.length();
			}
			tmp.emplace_back(str.substr(begIdx, endIdx - begIdx));
			begIdx = str.find_first_not_of(',', endIdx);
		}
		unsigned int price = stoul(tmp[5]);
		string product_name = tmp[4];
		unsigned int pid = stoul(tmp[3]);
		string time_string = tmp[2];
		unsigned int cid = stoul(tmp[1]);
		unsigned int oid = stoul(tmp[0]);

		tm time;
		istringstream ss{ time_string };
		ss >> std::get_time(&time, "%a %m/%d/%y %H:%M:%S");
		products.emplace_back(new Product{ pid, product_name, price, 0, tm{} });
	}

	order_vector.emplace_back(order_id, cid, move(products), time);

	return  { in, move(order_vector) };
}


