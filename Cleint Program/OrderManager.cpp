#include "OrderManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
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
{//üũ
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
			order.products.emplace_back(inserted.first->second.getId());
		}
		else {
			order.products.emplace_back(itr->second.getId());
		}
	}
	order.order_id = order_id;
	order.client_id = client_id;
	auto inserted_order = orders.emplace(order_id, std::move(order));
	orders_CID.emplace(client_id, &inserted_order.first->second);


	return {order_id++, true};
}
//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };

void OrderManager::addOrder(const Order_ID loaded_order_id, const Client_ID client_id, vector<unsigned int> product_ids, std::tm date) {
	Order order;
	//üũ
	auto order_found = orders.find(loaded_order_id);
	if (order_found == orders.end())
		throw OM::Already_In_Order_No{};
	order.order_id = loaded_order_id;

	const Client& c = cm.findClient(client_id);
	if (c == no_client)
		throw OM::No_Matching_Client{};
	order.client_id = client_id;

	for (auto product_id : product_ids) {
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			throw OM::NoProduct{};
		auto itr = purchased_products.find(product_id);
		if (itr == purchased_products.end()) {
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(inserted.first->second.getId());
		}
		else {
			order.products.emplace_back(itr->second.getId());
		}
	}
	auto inserted_order = orders.emplace(order_id, std::move(order));
	orders_CID.emplace(client_id, &inserted_order.first->second);
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
	auto o = orders.find(order_id);
	if (o == orders.end()) {
		return no_order;
	}
	else {
		return o->second;
	}
	//üũ
}
static std::ofstream& operator<< (std::ofstream& out, tm p) {
	out << std::put_time(&p, "%A %c");
	return out;
}
static std::ofstream& operator<<(std::ofstream& out, const OrderManager::Order& o)
{
	out << o.order_id << ',' << o.client_id << ',';
	out << o.date;
	for (auto product_id : o.products) {
		out << ',' << product_id;
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
	std::vector<Order> order_vector;
	vector<Product_ID> products_ids;
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
		string time_string = tmp[2];//
		Client_ID cid = stoul(tmp[1]);//
		Order_ID oid = stoul(tmp[0]);//
		
		unsigned int idx = 3;
		while (idx<tmp.size()) {
			products_ids.emplace_back(stoul(tmp[idx]));
		}

		std::tm time;
		istringstream ss{ time_string };
		ss >> std::get_time(&time, "%a %m/%d/%y %H:%M:%S");
		Order od{ oid, cid, time, products_ids };
		order_vector.emplace_back(od);
	}
	return  { in, (order_vector) };
}


