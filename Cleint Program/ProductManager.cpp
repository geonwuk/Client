#include "ProductManager.h"
using namespace std;
using namespace PM;

unsigned int ProductManager::product_id=0;

bool PM::operator== (const Product& p, const NoProduct&) {
	const Product& np{ no_product };
	if (&p == &np)
		return true;
	else
		return false;
}

bool ProductManager::addProduct(const string name, double price, unsigned int qty)
{
	time_t base_time = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &base_time);
	bool success;
	tie(ignore, success) = products.emplace(product_id, Product{ product_id, name, price, qty, local_time });
	product_id++;
	return success;
}

bool ProductManager::eraseProduct(const unsigned int id){
	using int_type = decltype(products)::size_type;
	int_type success = products.erase(id);
	if (success == 1)
		return true;
	else
		return false;
}

const Product& ProductManager::findProduct(const unsigned int id) const
{
	auto it = products.find(id);
	if (it == products.end()) {
		return no_product;
	}
	else {
		return it->second;
	}
}

const map<unsigned int, Product>& ProductManager::getProducts() const
{
	return products;
}



