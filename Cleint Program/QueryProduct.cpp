#include "QueryProduct.h"
#include <iostream>
#include<ctime>
#include  <fstream>
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

void QueryProduct::QuerySaveProduct(){
	std::ofstream out("Product.txt");
	pm.saveProducts(out);
}

void QueryProduct::QueryLoadProduct()
{
	std::ifstream in{ "Product.txt" };
	pm.loadProducts(in);
}

std::ostream& operator<< (std::ostream& os, const tm& p) {
	cout << p.tm_year + 1900 << "³â " << p.tm_mon + 1 << "¿ù " << p.tm_mday << "ÀÏ";
	return os;
}

