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
	
	struct No_Matching_Product { Product_ID pid; }; //�ֹ��� �ε��� �� ���� ���Ͽ� �ִ� ��ǰ id�� ��ϵǾ� ���� �ʴٸ� ���ܸ� ����
	struct No_Matching_Client { Client_ID cid; };	//�ֹ��� �ε��� �� ���� ���Ͽ� �ִ� �� id�� ��ϵǾ� ���� �ʴٸ� ���ܸ� ����
	struct Already_In_Order { Order_ID oid; };		//�ֹ��� �ε��� �� ���Ͽ� �ִ� �ֹ���ȣ�� �̹� ��ϵǾ� �ִٸ� �߰��� �Ұ����ϹǷ� ���ܸ� ����

	class OrderManager{
	public:
		OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}
		struct Order {						//�ֹ��� �ڷᱸ��
			Order_ID order_id;				//�ֹ���ȣ
			Client_ID client_id;			//������ ��ȣ
			std::tm date;					//���Žñ�
			vector<Product_ID> products;	//������ ��ǰ ��ȣ��
		};
		const ProductManager& pm;
		const ClientManager& cm;
		const Order& getOrder(const Order_ID order_id) const;											//�ֹ�id�� �ش��ϴ� �ֹ� ����
		std::ofstream & saveOrders(std::ofstream&) const;												//�ֹ�����
		std::pair<std::ifstream&, vector<Order>> loadOrders(std::ifstream&);							//�ֹ��ҷ�����
		const Product& getPurchasedProducts(const Product_ID pid) const;								//���Ű� �� ��ǰ���� Ȯ��
		void addOrder(const Order&);																	//�ֹ��� ���Ϸκ��� �ҷ��� �� ���� �ֹ��߰�
		std::pair<const unsigned int, bool> addOrder(const Client_ID client_id, vector<unsigned int>);	//�ֹ��߰�
		OrderIterator getOrders() const;																//�ֹ���ȸ �� ���
	private:
		unsigned int order_id = 0;								//Primary Key
		std::map<Order_ID, Order> orders;						//�ֹ��� map���� ����
		std::multimap<Client_ID, Order*> orders_CID;			//���� �� ID�� �ֹ��� ��ȸ�� �� �� �� ���
		std::map<Product_ID, Product> purchased_products;		//�ֹ��� �̷���� ��ǰ�� ���� ������ ����(��ǰ�� ���ݵ��� ����� �� �����Ƿ�)
		
	public:
		using OM_itr = decltype(OrderManager::orders)::const_iterator;
	};
	struct NoOrder : public OrderManager::Order { };
	const NoOrder no_order{};	//�ش��ϴ� �ֹ��� ���� ��� �� ��ü�� �����Ѵ�
	using Itr_type = OrderManager::OM_itr;

	class OrderIterator { //�ֹ��� ��ȸ�� �� Iterator�� ��ȸ�� �� �ֵ��� �ϴ� Ŭ����
	private:
		struct Itr {
			Itr_type ptr;//map�� Order�� ����Ű�� ������
			Itr(Itr_type p) :ptr{ p } {}
			const OrderManager::Order& operator*() const {
				return ptr->second;
			}
			Itr_type operator++() {
				return ++ptr;
			}
			bool operator!=(Itr b) {
				auto re = (ptr) != (b.ptr);
				return re;
			}
		};
	public:
		OrderIterator(Itr_type b, Itr_type e) : st{ b }, ed{ e } {}
		Itr st, ed;
		Itr begin() {return (st);}  //���� ���� for loop�� �� �� �ְ� begin ����
		Itr end() {return (ed);}	//���� ���� for loop�� �� �� �ְ� end ����
	};
}