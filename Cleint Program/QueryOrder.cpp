#include "QueryOrder.h"
#include <iostream>

using namespace std;
inline std::ostream& operator<< (std::ostream& os, const Product& p);
inline std::ostream& operator<< (std::ostream& os, const tm& p);
std::ostream& operator<< (std::ostream& os, const OrderManager::Order& o) {
	cout << "Cleint ID: " << o.client_ID << " ";
	cout << "date: " << o.date << " ";

	for (const auto& e : o.products) {
		cout << e << ",";
	}
	cout << endl;

	return os;
}
void QueryOrder::QueryShowOrder()
{
	auto m = om.getOrders();
	for (auto& i : m) {
		cout << i.second << endl;;
	}
	cout << endl;
}

void QueryOrder::QueryAddOrder() {
	cout << "Cleint ID: ";
	string client_ID;
	cin >> client_ID;
	om.addOrder(client_ID, products);
}




