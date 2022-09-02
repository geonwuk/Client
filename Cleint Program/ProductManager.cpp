#include "ProductManager.h"
using namespace std;
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

const map<unsigned int, Product>& ProductManager::getCleints() const
{
	return products;
}



