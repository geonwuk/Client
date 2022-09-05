#include "QueryProduct.h"
#include <iostream>
#include<ctime>
using namespace std;

void QueryProduct::QueryAddProduct()
{
	string name;
	double price;
	unsigned int qty;
	cout << "product name: ";
	cin >> name;
	cout << "price: ";
	cin >> price;
	cout << "QTY: ";
	cin >> qty;
	pm.addProduct(name, price, qty);
}

void QueryProduct::QueryEraseProduct()
{
	unsigned int ID;
	cout << "product ID: ";
	cin >> ID;
	pm.eraseProduct(ID);
}




void QueryProduct::QueryShowProduct()
{
	auto m = pm.getProducts();
	for (auto& i : m) {
		cout << i.second << endl;
	}
	cout << endl;
}

std::ostream& operator<< (std::ostream& os, const tm& p) {
	cout << p.tm_year + 1900 << "³â " << p.tm_mon + 1 << "¿ù " << p.tm_mday << "ÀÏ";
	return os;
}

std::ostream& operator<< (std::ostream& os, const Product& p) {
	cout << "id: " << p.getId() << " ";
	cout << "Name: " << p.name << " ";
	cout << "Price: " << p.price << " ";
	cout << "quantity: " << p.qty << " ";
	cout << "registered_date: " << p.registered_date << " ";
	return os;
}