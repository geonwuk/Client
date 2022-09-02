#include "QueryProduct.h"
#include <iostream>
#include<ctime>
using namespace std;
void QueryProduct::QueryAddProduct()
{
	string ID;
	string name;
	double price;
	double discount_ratio;
	cout << "product ID: ";
	cin >> ID;
	cout << "product name: ";
	cin >> name;
	cout << "price: ";
	cin >> price;
	cout << "discount_ratio: ";
	cin >> discount_ratio;
	pm.addProduct(ID, name, price, discount_ratio);
}

void QueryProduct::QueryEraseProduct()
{
	string ID;
	cout << "product ID: ";
	cin >> ID;
	pm.eraseProduct(ID);
}

std::ostream& operator<< (std::ostream& os, const tm& p) {
	cout << p.tm_year << "³â " << p.tm_mon << "¿ù " << p.tm_mday << "ÀÏ";
	return os;
}

std::ostream& operator<< (std::ostream& os, const Product& p) {
	cout << "ID: " << p.ID << " ";
	cout << "Name: " << p.name << " ";
	cout << "Price: " << p.price << " ";
	cout << "discounted_ratio: " << p.discounted_ratio << " ";
	cout << "registered_date: " << p.registered_date << " ";
	return os;
}


void QueryProduct::QueryShowProduct()
{
	auto m = pm.getCleints();
	for (auto& i : m) {
		cout << i.second << endl;
	}
	cout << endl;
}
