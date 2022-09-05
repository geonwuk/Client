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
	class OrderManager{
	public:
		OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}
		using product_sptr = std::shared_ptr<Product>;
		struct Order {
			unsigned int client_id;
			vector<product_sptr> products;
			std::tm date;
		};

	private:
		const ProductManager& pm;
		const ClientManager& cm;

		unsigned int order_id = 0;
		std::multimap<unsigned int, Order> orders;
		map<unsigned int, std::weak_ptr<Product>> purchased_products;
		
	public:
		bool addOrder(const unsigned int client_id, vector<unsigned int>);
		OrderIterator getOrders(const unsigned int client_id) const;
	};

	using itr_type = decltype(OrderManager::orders)::const_iterator;

	struct itr {
		itr() {} //todo
		itr_type ptr;
		itr(itr_type p) :ptr{ p } {}
		const OrderManager::Order& operator*() const {
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
		OrderIterator() {}
		OrderIterator(itr_type b, itr_type e) : st{ b }, ed{ e } {}

		itr st, ed;

		itr begin() {
			return (st);
		}
		itr end() {
			return (ed);
		}
	};

}