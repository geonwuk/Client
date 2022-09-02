#pragma once
#include "ProductManager.h"
#include <iostream>
using std::cout;
inline std::ostream& operator<< (std::ostream& os, const tm& p) {
	cout << p.tm_year + 1900 << "³â " << p.tm_mon + 1 << "¿ù " << p.tm_mday << "ÀÏ";
	return os;
}

inline std::ostream& operator<< (std::ostream& os, const Product& p) {
	cout << "ID: " << p.ID << " ";
	cout << "Name: " << p.name << " ";
	cout << "Price: " << p.price << " ";
	cout << "discounted_ratio: " << p.discounted_ratio << " ";
	cout << "registered_date: " << p.registered_date << " ";
	return os;
}
class QueryProduct
{
public:
	QueryProduct(ProductManager& pm) : pm{ pm } {}

	void QueryAddProduct();
	void QueryEraseProduct();
	void QueryShowProduct();

private:
	ProductManager& pm;
};

