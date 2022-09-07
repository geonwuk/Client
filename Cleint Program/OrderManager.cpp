
#include "OrderManager.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;
using namespace OM;
using namespace PM;
const Product& OM::OrderManager::getPurchasedProducts(const Product_ID pid) const{
	//purchased_product는 추가된 주문의 제품정보를 저장하고 있는 멤버
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

	time_t base_time = time(nullptr);			//시간 구하기
	tm local_time;
	localtime_s(&local_time, &base_time);
	order.date = local_time;

	for (auto product_id : product_ids) {//사용자가 ,를 이용해 상품을 입력했을 경우 처리 (예: 1,2,3인 경우 상품 번호 1,2,3을 벡터에 담는다)
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)//제품관리에 없는 제품 번호를 입력하면 오류이다
			return { product_id,false };
		auto itr = purchased_products.find(product_id); //구매되는 제품이 처음 구매되는지 확인
		if (itr == purchased_products.end()) {			//만약 처음 구매되는 제품이라면 그 정보를 복사한다(추후에 제품의 정보가 바뀔 수 있으므로 복사)
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(inserted.first->second.getId());//제품 id추가
		}
		else {
			order.products.emplace_back(itr->second.getId());//제품 id추가
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
	//주문을 로드할 때 파일에 있는 주문번호가 이미 등록되어 있다면 추가가 불가능하므로 예외를 던짐

	const Client& c = cm.findClient(order_to_add.client_id);
	if (c == no_client)
		throw OM::No_Matching_Client{ order_to_add.client_id};
	order.client_id = order_to_add.client_id;
	//주문을 로드할 때 만약 파일에 있는 고객 id가 등록되어 있지 않다면 예외를 던짐

	for (auto product_id : order_to_add.products) { //
		const Product& found = pm.findProduct(product_id);
		if (found == no_product)
			throw OM::No_Matching_Product{product_id};
		//주문을 로드할 때 만약 파일에 있는 제품 id가 등록되어 있지 않다면 예외를 던짐
		auto itr = purchased_products.find(product_id); //구매되는 제품이 처음 구매되는지 확인
		if (itr == purchased_products.end()) {			//만약 처음 구매되는 제품이라면 그 정보를 복사한다(추후에 제품의 정보가 바뀔 수 있으므로 복사)
			auto inserted = purchased_products.emplace(product_id, Product{ found });
			order.products.emplace_back(inserted.first->second.getId());
		}
		else {
			order.products.emplace_back(itr->second.getId());
		}
	}

	order.date = order_to_add.date;													//파일로부터 읽은 날짜
	auto inserted_order = orders.emplace(order_to_add.order_id, std::move(order));	//주문을 추가
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