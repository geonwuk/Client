#include "QueryProduct.h"
#include <iostream>
#include<ctime>
#include  <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;
using namespace PM;
TB::Table QueryProduct::table{ "id","name","price","quantity","date"};

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

void QueryProduct::QueryAddProduct()
{
	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	string name;
	unsigned int price;
	unsigned int qty;
	cout << "product name: ";
	cin >> name;
	cout << "price: ";
	price = getSelection();
	cout << "QTY: ";
	qty = getSelection();
	
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
	table.printHeader();
	auto m = pm.getProducts();
	for (auto& itr : m) {
		const Product& p = itr.second;
		std::stringstream ss;
		auto t = p.getDate();
		ss << std::put_time(&t, "%A %c");
		string time = ss.str();
		table.print({ std::to_string(p.getId()), p.getName(), to_string(p.getPrice()), to_string(p.getQty()), time });
	}
	table.printTail();
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


