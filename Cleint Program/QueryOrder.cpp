#include "QueryOrder.h"
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace PM;
using namespace OM;
using namespace std;

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
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ���ڸ� �Է��� �� �ֽ��ϴ�." << endl;
		goto again;
	}
	if (selection < 0) {
		cout << "�Է� �����Դϴ�. �ٽ� �Է��Ͻʽÿ�. ����� �Է��� �� �ֽ��ϴ�." << endl;
	}
	return selection;
}


void QueryOrder::QueryAddOrder() {
	unsigned int client_ID;
	//�ֹ� �߰��� ����(client_id) ������(product_id)�� ����� �Է��� �޴´�.
	TB::Table client_table{ "client id" };
	client_table.printHeader();
	for (auto& itr : om.cm.getCleints()) {//
		const Client& c = itr.second;
		client_table.print({ to_string(c.getId()) });
	}
	client_table.printTail();
	cout << "������ ���̵� �Է�" << endl;
	cout << "Cleint ID: ";
	client_ID = getSelection();

	const Client& c = om.cm.findClient(client_ID);
	if (c == no_client) {
		cout << "����: �� ID " << client_ID << "�� ��ǰ ��Ͽ� �����ϴ�." << endl;
		return;
	}

	TB::Table product_table{ "product id" };
	product_table.printHeader();
	for (auto& itr : om.pm.getProducts()) {
		const Product& p = itr.second;
		product_table.print({ to_string(p.getId()) });
	}
	product_table.printTail();
	string product_IDs;
	cout << "������ Product IDs (use commas):  ��) 1,2,3 "<<endl;
	cin >> product_IDs;

	vector<unsigned int> products_vector;
	auto begIdx = product_IDs.find_first_not_of(',');
	while (begIdx != string::npos) {// CSV ������ �Ľ��� products_vector�� �����͸� �Է��Ѵ�.
		auto endIdx = product_IDs.find_first_of(',', begIdx);
		if (endIdx == string::npos) {
			endIdx = product_IDs.length();
		}
		unsigned int pid;
		try {
			pid = stoul(product_IDs.substr(begIdx, endIdx - begIdx));
		}
		catch (std::invalid_argument) {
			cout << "���� ��ǰ ���̵� ���ڷ� ������ �� �����ϴ�." << endl;
			return;
		}
		products_vector.emplace_back(pid);
		begIdx = product_IDs.find_first_not_of(',', endIdx);
	}//CSV���� �Ľ� �Ϸ�: products_vector�� ������ ����
	int order_id; bool success;
	std::tie(order_id,success)= om.addOrder(client_ID, products_vector);
	//om.addOrder�� ������ ��� order_id�� ã�� ������ product_id�� �����Ѵ�
	if (!success) {
		cout << "����: �߰��ҷ��� ��ǰ ���̵� "<<order_id<< "�� �����ϴ�." << endl;
		return ;
	}
	//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price", "quantity" };

	for (auto pid : products_vector) {
		const Product& product = om.pm.findProduct(pid);
		table.setFields({ to_string(order_id),to_string(client_ID), to_string(product.getId()),product.getName(), to_string(product.getPrice()) });
	}
}

void QueryOrder::QueryShowOrder(){
	//{ "order id", "client id","product id","product name","price" };
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
			cout << "����: ��ǰID " << e.pid << "�� ��ǰ ��Ͽ� �����ϴ�." << endl;
			return;
		}
		catch (No_Matching_Client e) {
			cout << "����: ��ID " << e.cid << "�� �� ��Ͽ� �����ϴ�." << endl;
			return;
		}
		catch (Already_In_Order e) {
			cout << "����: �ֹ�ID " << e.oid << "�� �̹� �����մϴ�." << endl;
			return;
		}
		for (auto product_id : order.products) {
			const Product& p = om.pm.getProduct(product_id);
			table.setFields({ to_string(order.order_id), to_string(order.client_id), to_string(product_id), p.getName(), to_string(p.getPrice()) });
			//�ҷ����� �� ��ǰ���� ���̺� �ʵ带 ����
		}
	}
}
void QueryOrder::QueryEraseOrder()
{
}




