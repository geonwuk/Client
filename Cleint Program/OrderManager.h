#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <memory>

#include "ProductManager.h"
#include "ClientManager.h"
using namespace std;
using namespace PM;
using std::string;
using std::vector;


namespace OM {
	struct OrderIterator;
	class OrderManager
	{
	public:
		OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}

	public:
		using product_sptr = std::shared_ptr<Product>;
		struct Order {
			string client_ID;
			vector<product_sptr> products;
			std::tm date{};
		};
	private:
		const ProductManager& pm;
		const ClientManager& cm;

		unsigned int order_id = 0;
		std::map<unsigned int, Order> orders;
		std::multimap<string, Order*> orders_by_client_id;
		map<string, std::weak_ptr<Product>> purchased_products;
		
	public:
		bool addOrder(string client_ID, const string& product_ID);
		OM::OrderIterator getOrders(const string& client_ID);
	};

	struct itr {
		itr() {}
		std::multimap<string, OrderManager::Order*>::const_iterator ptr;
		itr(std::multimap<string, OrderManager::Order*>::const_iterator p) :ptr{ p } {}
		const OrderManager::Order* operator*() const {
			return ptr->second;
		}
		void operator++() {
			ptr++;
		}
		bool operator!=(itr b) {
			auto re = (ptr) != (b.ptr);
			return re;
		}
	};
	struct OrderIterator {
	public:
		//decltype(orders_by_client_id)::iterator;
		OrderIterator() {}
		OrderIterator(std::multimap<string, OrderManager::Order*>::const_iterator b, std::multimap<string, OrderManager::Order*>::const_iterator e) : st{ b }, ed{ e } {}
	

		itr st, ed;

		itr begin() {
			return (st);
		}
		itr end() {
			return (ed);
		}
	};

}

using itr_type = std::multimap<string, OM::OrderManager::Order*>::const_iterator;
