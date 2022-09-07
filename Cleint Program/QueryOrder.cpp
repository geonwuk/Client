#include "QueryOrder.h"
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace PM;
using namespace OM;
using namespace std;

//inline std::ostream& operator<< (std::ostream& os, const tm& p);

TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };

static int getSelection() {
again:
	int selection;
	try {
		cin >> selection;
	}
	catch (const std::ios_base::failure&) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "입력 오류입니다. 다시 입력하십시오. 숫자만 입력할 수 있습니다." << endl;
		goto again;
	}
	if (selection < 0) {
		cout << "입력 오류입니다. 다시 입력하십시오. 양수만 입력할 수 있습니다." << endl;
	}
	return selection;
}


void QueryOrder::QueryAddOrder() {
	unsigned int client_ID;

	TB::Table client_table{ "client id" };
	client_table.printHeader();
	for (auto& itr : om.cm.getCleints()) {
		const Client& c = itr.second;
		client_table.print({ to_string(c.getId()) });
	}
	client_table.printTail();
	cout << "구매자 아이디 입력" << endl;
	cout << "Cleint ID: ";
	client_ID = getSelection();

	TB::Table product_table{ "product id" };
	product_table.printHeader();
	for (auto& itr : om.pm.getProducts()) {
		const Product& p = itr.second;
		product_table.print({ to_string(p.getId()) });
	}
	product_table.printTail();
	string product_IDs;
	cout << "구매할 Product IDs (use commas):  예) 1,2,3 "<<endl;
	cin >> product_IDs;

	vector<unsigned int> products_vector;
	auto begIdx = product_IDs.find_first_not_of(',');
	while (begIdx != string::npos) {
		auto endIdx = product_IDs.find_first_of(',', begIdx);
		if (endIdx == string::npos) {
			endIdx = product_IDs.length();
		}
		unsigned int pid;
		try {
			pid = stoul(product_IDs.substr(begIdx, endIdx - begIdx));
		}
		catch (std::invalid_argument) {
			cout << "오류 제품 아이디를 숫자로 변경할 수 없습니다." << endl;
			return;
		}
		products_vector.emplace_back(pid);
		begIdx = product_IDs.find_first_not_of(',', endIdx);
	
	}
	int order_id; bool success;
	std::tie(order_id,success)= om.addOrder(client_ID, products_vector);
	if (!success) {
		cout << "오류: 추가할려는 제품 아이디 "<<order_id<< "가 없습니다." << endl;
		return ;
	}
	//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price", "quantity" };

	for (auto pid : products_vector) {
		const Product& product = om.pm.findProduct(pid);
		table.setFields({ to_string(order_id),to_string(client_ID), to_string(product.getId()),product.getName(), to_string(product.getPrice()) });
	}
}

void QueryOrder::QueryShowOrder(){
	//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };
	table.printHeader();
	auto orders = om.getOrders();
	for (auto& order : orders) {
		const OrderManager::Order& o = order;
		for (auto product_id : order.products) {
			const Product& p = om.getPurchasedProducts(product_id);
			table.print({ to_string(o.order_id),to_string(o.client_id), to_string(p.getId()), p.getName(), to_string(p.getPrice()) });
		}
	}
	table.printTail();
}


void QueryOrder::QuerySaveOrder(){
	std::ofstream out("Orders.txt");
	om.saveOrders(out);
}


//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };

void QueryOrder::QueryLoadOrder()
{
	std::ifstream in{ "Orders.txt" };
	std::vector<OrderManager::Order > loaded_orders;

	std::tie(std::ignore, loaded_orders) = om.loadOrders(in);

	for (auto& order : loaded_orders) {
		try {
			om.addOrder(order);
		}
		catch (No_Matching_Product e) {
			cout << "오류: 상품ID " << e.pid << "가 상품 목록에 없습니다." << endl;
			return;
		}
		catch (No_Matching_Client e) {
			cout << "오류: 고객ID " << e.cid << "가 고객 목록에 없습니다." << endl;
			return;
		}
		catch (Already_In_Order e) {
			cout << "오류: 주문ID " << e.oid << "가 이미 존재합니다." << endl;
			return;
		}
		for (auto product_id : order.products) {
			const Product& p = om.pm.getProduct(product_id);
			table.setFields({ to_string(order.order_id), to_string(order.client_id), to_string(product_id), p.getName(), to_string(p.getPrice()) });
		}
	}
}
void QueryOrder::QueryEraseOrder()
{
}




