#include "QueryProduct.h"
#include <iostream>
#include<ctime>
#include  <fstream>
#include <string>
#include <sstream>

using namespace std;
TB::Table QueryProduct::table{ "id","name","price","quantity","date"};
void QueryProduct::QueryAddProduct()
{
	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	string name;
	double price;
	unsigned int qty;
	cout << "product name: ";
	cin >> name;
	cout << "price: ";
	cin >> price;
	cout << "QTY: ";
	cin >> qty;

	pm.addProduct(name, price, qty, local_time);
	std::stringstream ss;
	ss<< std::put_time(&local_time, "%A %c");
	string time = ss.str();
	unsigned int id = pm.getMaxIndex();
	table.setFields({ to_string(id),name,to_string(price),to_string(qty),time });
}

void QueryProduct::QueryEraseProduct()
{
	QueryShowProduct();
	unsigned int id;
	cout << "삭제할 상품 id: ";
	cin >> id;
	bool success = pm.eraseProduct(id);
	if (success) {
		cout << "ID:" << id << " 상품 삭제 완료" << endl;
	}
	else {
		cout << "ID:" << id << " 상품은 존재하지 않습니다. 삭제 실패" << endl;
	}
}
//TB::Table QueryProduct::table{ "id","name","price","quantity","date" };

void QueryProduct::QueryShowProduct()
{
	table.print_header();
	auto m = pm.getProducts();
	for (auto& itr : m) {
		const Product& p = itr.second;
		std::stringstream ss;
		auto t = p.getDate();
		ss << std::put_time(&t, "%A %c");
		string time = ss.str();
		table.print({ std::to_string(p.getId()), p.getName(), to_string(p.getPrice()), to_string(p.getQty()), time });
	}
	table.print_tail();
}

void QueryProduct::QuerySaveProduct(){
	std::ofstream out("Product.txt");
	pm.saveProducts(out);
}

void QueryProduct::QueryLoadProduct()
{
	std::ifstream in{ "Product.txt" };
	auto pr = pm.loadProducts(in);

	for (auto& i : pr.second) {
		pm.addProduct(i.getName(), i.getPrice(), i.getQty(), i.getDate());
		unsigned int new_id = pm.getMaxIndex();
		std::stringstream ss;
		auto time_string = i.getDate();
		ss << std::put_time(&time_string, "%A %c");
		string time = ss.str();
		table.setFields({ to_string(new_id),i.getName(), to_string(i.getPrice()), to_string(i.getQty()), time });
	}
}

std::ostream& operator<< (std::ostream& os, const tm& p) {
	cout << p.tm_year + 1900 << "년 " << p.tm_mon + 1 << "월 " << p.tm_mday << "일";
	return os;
}

