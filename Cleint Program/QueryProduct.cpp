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




void QueryProduct::QueryShowProduct()
{
	auto m = pm.getCleints();
	for (auto& i : m) {
		cout << i.second << endl;
	}
	cout << endl;
}
