#pragma once
#include <ctime>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <utility>
#include "ProductManager.h"
#include "ClientManager.h"
namespace OM {
	using namespace CM;
	using namespace PM;
	using std::string;
	using std::vector;
	class OrderIterator;
	using Product_ID = unsigned int;
	using Client_ID = unsigned int;
	using Order_ID = unsigned int;

	struct No_Matching_Product {};
	struct No_Matching_Client {};
	struct Already_In_Order_No {};

	class OrderManager{
	public:
		
		OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}
		struct Order {
			Order_ID order_id;
			Client_ID client_id;
			std::tm date;
			vector<Product_ID> products;
		};
		const ProductManager& pm;
		const ClientManager& cm;
		const Order& getOrder(const Order_ID order_id) const;
		std::ofstream & saveOrders(std::ofstream&) const;
		std::pair<std::ifstream&, std::vector<Order>> loadOrders(std::ifstream&);

	private:
		unsigned int order_id = 0;
		std::multimap<Client_ID, Order*> orders_CID;
		std::map<Order_ID, Order> orders;
		std::map<Product_ID, Product> purchased_products;
		
	public:
		const Product& getPurchasedProducts(const Product_ID pid) const;
		using OM_itr = decltype(OrderManager::orders)::const_iterator;
		void addOrder(const Order_ID , const Client_ID , vector<Product_ID>, std::tm);
		std::pair<const unsigned int, bool> addOrder(const Client_ID client_id, vector<unsigned int>);
		OrderIterator getOrders(const unsigned int client_id) const;
		OrderIterator getOrders() const;
	};
	struct NoOrder : public OrderManager::Order { };
	const NoOrder no_order{};
	using itr_type = OrderManager::OM_itr;


	class OrderIterator {
	private:
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