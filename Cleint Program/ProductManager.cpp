#include "ProductManager.h"
using namespace std;
using namespace PM;

//static const NoProduct no_product{};

bool PM::operator== (const Product& p, const NoProduct&) {
	const Product& np{(no_product) };
	if (&p == &np)
		return true;
	else
		return false;
}


void ProductManager::addProduct(string ID, string name, double price, double discounted_ratio)
{
	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	auto it = products.emplace(product_id, Product{ product_id, ID, name, price, discounted_ratio, local_time });
	products_by_string.emplace(ID, &it.first->second);
	product_id++;
}

bool ProductManager::eraseProduct(string ID)
{
	auto it = products_by_string.find(ID);
	if (it != products_by_string.end()) {
		products.erase(it->second->getId());
		products_by_string.erase(it);
		return true;
	}
	else {
		return false;
	}
}

const Product& ProductManager::findProduct(const string& ID) const
{
	auto it = products_by_string.find(ID);
	if (it == products_by_string.end()) {
		return no_product;
	}
	else {
		return *(it->second);
	}
}

const map<unsigned int, Product>& ProductManager::getProducts() const
{
	return products;
}



