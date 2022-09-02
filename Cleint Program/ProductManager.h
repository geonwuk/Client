#pragma once
#include <map>
#include <string>
#include "Product.h"
using std::map;
using std::string;
class ProductManager
{
public:
	void addProduct( string ID, string name, double price, double discounted_ratio);
	bool eraseProduct(string ID);

	const map< unsigned int, Product >& getCleints() const;

private:
	unsigned int product_id;
	map < unsigned int, Product > products;
	std::multimap < string, Product* > products_by_string;

};

