#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "Product.h"
#include "ProductManager.h"
#include "ClientManager.h"
using product_ptr = std::shared_ptr<Product>;


using std::string;
using std::vector;
class OrderManager
{
public:
	OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}
private:

public:
	struct Order {
		string client_ID;
		vector<product_ptr> products;
		std::tm date;
	};
	void addOrder(string client_ID, const vector<Product>& products);
	const std::map<unsigned int, Order>& getOrders() const;
private:
	const ProductManager& pm;
	const ClientManager& cm;


	std::map<unsigned int, Order> orders;

	using product_id = unsigned int;
	map<product_id, product_ptr> purchased_products;
};

