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
	
	struct No_Matching_Product { Product_ID pid; }; //주문을 로드할 때 만약 파일에 있는 제품 id가 등록되어 있지 않다면 예외를 던짐
	struct No_Matching_Client { Client_ID cid; };	//주문을 로드할 때 만약 파일에 있는 고객 id가 등록되어 있지 않다면 예외를 던짐
	struct Already_In_Order { Order_ID oid; };		//주문을 로드할 때 파일에 있는 주문번호가 이미 등록되어 있다면 추가가 불가능하므로 예외를 던짐

	class OrderManager{
	public:
		OrderManager(ClientManager& cm, ProductManager& pm) :cm{ cm }, pm{ pm }{}
		struct Order {						//주문의 자료구조
			Order_ID order_id;				//주문번호
			Client_ID client_id;			//구매자 번호
			std::tm date;					//구매시기
			vector<Product_ID> products;	//구매한 제품 번호들
		};
		const ProductManager& pm;
		const ClientManager& cm;
		const Order& getOrder(const Order_ID order_id) const;											//주문id에 해당하는 주문 리턴
		std::ofstream & saveOrders(std::ofstream&) const;												//주문저장
		std::pair<std::ifstream&, vector<Order>> loadOrders(std::ifstream&);							//주문불러오기
		const Product& getPurchasedProducts(const Product_ID pid) const;								//구매가 된 제품인지 확인
		void addOrder(const Order&);																	//주문을 파일로부터 불러올 때 쓰는 주문추가
		std::pair<const unsigned int, bool> addOrder(const Client_ID client_id, vector<unsigned int>);	//주문추가
		OrderIterator getOrders() const;																//주문조회 시 사용
	private:
		unsigned int order_id = 0;								//Primary Key
		std::map<Order_ID, Order> orders;						//주문을 map으로 관리
		std::multimap<Client_ID, Order*> orders_CID;			//추후 고객 ID로 주문을 조회할 때 쓸 때 사용
		std::map<Product_ID, Product> purchased_products;		//주문이 이루어진 제품에 대해 정보를 저장(제품의 가격등이 변경될 수 있으므로)
		
	public:
		using OM_itr = decltype(OrderManager::orders)::const_iterator;
	};
	struct NoOrder : public OrderManager::Order { };
	const NoOrder no_order{};	//해당하는 주문이 없을 경우 이 객체를 리턴한다
	using Itr_type = OrderManager::OM_itr;

	class OrderIterator { //주문을 순회할 떄 Iterator로 순회할 수 있도록 하는 클래스
	private:
		struct Itr {
			Itr_type ptr;//map의 Order를 가리키는 포인터
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
		Itr begin() {return (st);}  //범위 지정 for loop를 쓸 수 있게 begin 정의
		Itr end() {return (ed);}	//범위 지정 for loop를 쓸 수 있게 end 정의
	};
}