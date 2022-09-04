#include "QueryOrder.h"
#include <iostream>
using namespace PM;
using namespace OM;
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
	string client_id;
	cout << "Cleint ID: ";
	cin >> client_id;
	auto orders = om.getOrders(client_id);
	int idx = 1;
	vector<int> x;
	x.begin();
	for (auto i = orders.begin(); i != orders.end(); ++i) {
		//cout << "#" << idx++ << "order" << endl;
		//for (auto j : i->products) {
		//	cout << j;
		//}
		//cout << endl;
	}
	cout << endl;
}

void QueryOrder::QueryAddOrder() {
	//string client_ID;
	//cout << "Cleint ID: ";
	//cin >> client_ID;

	//string product_IDs;
	//cout << "Product IDs (use commas): ";
	//cin >> product_IDs;

	//vector<string> products_vector;
	//auto begIdx = product_IDs.find_first_not_of(',');
	//while (begIdx != string::npos) {
	//	auto endIdx = product_IDs.find_first_of(',' , begIdx);
	//	if (endIdx == string::npos) {
	//		endIdx = product_IDs.length();
	//	}
	//	//products_vector.emplace_back(product_IDs.substr(begIdx,endIdx-begIdx));
	//	begIdx = product_IDs.find_first_not_of(',');
	//}

	//for (auto i : products_vector) {
	//	om.addOrder(client_ID, i);
	//}
}




