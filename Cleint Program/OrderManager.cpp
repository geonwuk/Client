
#include "OrderManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;
using namespace OM;
using namespace PM;
const Product& OM::OrderManager::getPurchasedProducts(const Product_ID pid) const{
	//purchased_product�� �߰��� �ֹ��� ��ǰ������ �����ϰ� �ִ� ���
	auto it = purchased_products.find(pid);	
	if (it == purchased_products.end()) {
		return no_product;
	}
	else {
		return it->second;
	}
}

std::pair<const unsigned int, bool> OrderManager::addOrder(const Client_ID client_id, vector<unsigned int> product_ids){
	Order order;

	time_t base_time = time(nullptr);			//�ð� ���ϱ�
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	for (auto product_id : product_ids) {//����ڰ� ,�� �̿��� ��ǰ�� �Է����� ��� ó�� (��: 1,2,3�� ��� ��ǰ ��ȣ 1,2,3�� ���Ϳ� ��´�)
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)//��ǰ������ ���� ��ǰ ��ȣ�� �Է��ϸ� �����̴�
			return { product_id,false };
		auto itr = purchased_products.find(product_id); //���ŵǴ� ��ǰ�� ó�� ���ŵǴ��� Ȯ��
		if (itr == purchased_products.end()) {			//���� ó�� ���ŵǴ� ��ǰ�̶�� �� ������ �����Ѵ�(���Ŀ� ��ǰ�� ������ �ٲ� �� �����Ƿ� ����)
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(inserted.first->second.getId());//��ǰ id�߰�
		}
		else {
			order.products.emplace_back(itr->second.getId());//��ǰ id�߰�
		}
	}
	order.order_id = order_id;
	order.client_id = client_id;
	auto inserted_order = orders.emplace(order_id, std::move(order));
	orders_CID.emplace(client_id, &inserted_order.first->second);

	return {order_id++, true};
}
//TB::Table QueryOrder::table{ "order id", "client id","product id","product name","price" };

void OrderManager::addOrder(const Order& order_to_add) {
	Order order;

	auto order_found = orders.find(order_to_add.order_id);
	if (order_found != orders.end())
		throw OM::Already_In_Order{ order_to_add.order_id};	
	order.order_id = order_to_add.order_id;
	//�ֹ��� �ε��� �� ���Ͽ� �ִ� �ֹ���ȣ�� �̹� ��ϵǾ� �ִٸ� �߰��� �Ұ����ϹǷ� ���ܸ� ����

	const Client& c = cm.findClient(order_to_add.client_id);
	if (c == no_client)
		throw OM::No_Matching_Client{ order_to_add.client_id};
	order.client_id = order_to_add.client_id;
	//�ֹ��� �ε��� �� ���� ���Ͽ� �ִ� �� id�� ��ϵǾ� ���� �ʴٸ� ���ܸ� ����

	for (auto product_id : order_to_add.products) { //
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			throw OM::No_Matching_Product{product_id};
		//�ֹ��� �ε��� �� ���� ���Ͽ� �ִ� ��ǰ id�� ��ϵǾ� ���� �ʴٸ� ���ܸ� ����
		auto itr = purchased_products.find(product_id); //���ŵǴ� ��ǰ�� ó�� ���ŵǴ��� Ȯ��
		if (itr == purchased_products.end()) {			//���� ó�� ���ŵǴ� ��ǰ�̶�� �� ������ �����Ѵ�(���Ŀ� ��ǰ�� ������ �ٲ� �� �����Ƿ� ����)
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(inserted.first->second.getId());
		}
		else {
			order.products.emplace_back(itr->second.getId());
		}
	}

	order.date = order_to_add.date;													//���Ϸκ��� ���� ��¥
	auto inserted_order = orders.emplace(order_to_add.order_id, std::move(order));	//�ֹ��� �߰�
	order_id = order_to_add.order_id;
	order_id++;
	orders_CID.emplace(order_to_add.client_id, &inserted_order.first->second);
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
	
	std::string str;
	while (getline(in, str)) {
		vector<Product_ID> products_ids;
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
			products_ids.emplace_back(stoul(tmp[idx++]));
		}

		std::tm time;
		istringstream ss{ time_string };
		ss >> std::get_time(&time, "%a %m/%d/%y %H:%M:%S");
		Order od{ oid, cid, time, products_ids };
		order_vector.emplace_back(od);
	}
	return  { in, (order_vector) };
}