#include "QueryOrder.h"
#include <iostream>

using namespace PM;
using namespace OM;
using namespace std;

//inline std::ostream& operator<< (std::ostream& os, const tm& p);

TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };

void QueryOrder::QueryAddOrder() {
	unsigned int client_ID;

	TB::Table client_table{ "client id" };
	client_table.print_header();
	for (auto& itr : om.cm.getCleints()) {
		const Client& c = itr.second;
		client_table.print({ to_string(c.getId()) });
	}
	client_table.print_tail();
	cout << "구매자 아이디 입력" << endl;
	cout << "Cleint ID: ";
	cin >> client_ID;

	TB::Table product_table{ "product id" };
	product_table.print_header();
	for (auto& itr : om.pm.getProducts()) {
		const Product& p = itr.second;
		product_table.print({ to_string(p.getId()) });
	}
	product_table.print_tail();
	string product_IDs;
	cout << "구매할 Product IDs (use commas): ";
	cin >> product_IDs;

	vector<unsigned int> products_vector;
	auto begIdx = product_IDs.find_first_not_of(',');
	while (begIdx != string::npos) {
		auto endIdx = product_IDs.find_first_of(',', begIdx);
		if (endIdx == string::npos) {
			endIdx = product_IDs.length();
		}
		products_vector.emplace_back(stoul(product_IDs.substr(begIdx, endIdx - begIdx)));
		begIdx = product_IDs.find_first_not_of(',', endIdx);
	}
	int order_id = om.addOrder(client_ID, products_vector);
	if (order_id == -1) {
		//에러
	}
	//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price", "quantity" };

	for (auto pid : products_vector) {
		const Product& product = om.pm.findProduct(pid);

		table.setFields({ to_string(order_id),to_string(client_ID), to_string(product.getId()),product.getName(), to_string(product.getPrice()) });
	}
}
//std::ostream& operator<< (std::ostream& os, const OrderManager::Order& o) {
//	cout << "Cleint id: " << o.client_id << " ";
//	cout << "date: " << o.date << " ";
//
//	for (const auto& e : o.products) {
//		cout << e << ",";
//	}
//	cout << endl;
//
//	return os;
//}
void QueryOrder::QueryShowOrder()
{
	//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };
	table.print_header();
	auto orders = om.getOrders();
	for (auto& order : orders) {
		const OrderManager::Order& o = order;
		for (auto& product_id : order.products) {
			const Product& p = om.getPurchasedProducts(product_id);
			table.print({ to_string(o.order_id),to_string(o.client_id), to_string(p.getId()), p.getName(), to_string(p.getPrice()) });
		}
	}
	table.print_tail();




	//unsigned int client_id;
	//cout << "Cleint id: ";
	//cin >> client_id;
	//auto orders = om.getOrders(client_id);
	//int idx = 1;

	//for (auto order : orders) {
	//	cout << "#" << idx++ << "order" << endl;
	//	for (auto j : order.products) {
	//		cout << *j.get() << endl;
	//	}
	//	cout << endl;
	//}
	//cout << endl;
}


void QueryOrder::QuerySaveOrder(){

}

void QueryOrder::QueryLoadOrder()
{
}
void QueryOrder::QueryEraseOrder()
{
}




