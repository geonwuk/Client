#include<iostream>
#include "Display.h"
#include "QueryClient.h"
#include "QueryProduct.h"
#include "QueryOrder.h"
#include "ClientManager.h"
#include "ProductManager.h"

using namespace std;
using namespace OM;
using namespace PM;


int main() {
	ClientManager cm;
	ProductManager pm;
	OrderManager om{ cm,pm };

	QueryClient qc{ cm };//템플릿? Query<Client>,Query<Product>? 컨셉을 이용해 Query를
	QueryProduct qp{ pm };//상속? Query를 상속받으면 query함수에서 첫번째 인자를 없앨 수 있다
	QueryOrder qo{ om };

	Display a1{ "고객관리프로그램"};
	Display b1{ "고객정보관리"};
	Display b2{ "상품정보관리"};
	Display b3{ "주문관리" };
	a1.addChild({ &b1, &b2, &b3 });

	//Querychild vs treechild?
	
	Display c1{ "고객추가",  query(qc, &QueryClient::QueryAddClient) };//a1["고객정보관리"].addchild{"고객추가", query(...)}으로 바꾼다
	Display c2{ "고객삭제", query(qc, &QueryClient::QueryEraseClient) };//qc.query?
	Display c3{ "고객조회",query(qc, &QueryClient::QueryShowClient) };
	Display c4{ "고객저장", query(qc, &QueryClient::QuerySaveClient) };
	Display c5{ "고객로드", query(qc, &QueryClient::QueryLoadClient) };
	b1.addChild({ &c1,&c2,&c3,&c4,&c5 });

	Display d1{ "상품추가", query(qp, &QueryProduct::QueryAddProduct) };
	Display d2{ "상품제거", query(qp, &QueryProduct::QueryEraseProduct) };
	Display d3{ "상품조회", query(qp, &QueryProduct::QueryShowProduct) };
	Display d4{ "상품저장", query(qp, &QueryProduct::QuerySaveProduct) };
	Display d5{ "상품로드", query(qp, &QueryProduct::QueryLoadProduct) };
	b2.addChild({ &d1,&d2,&d3,&d4,&d5 });

	Display e1{ "주문추가", query(qo, &QueryOrder::QueryAddOrder) };
	Display e2{ "주문조회", query(qo, &QueryOrder::QueryShowOrder) };
	Display e4( "주문저장", query(qo, &QueryOrder::QuerySaveOrder));
	Display e5( "주문로드", query(qo, &QueryOrder::QueryLoadOrder));
	b3.addChild({ &e1,&e2,&e4,&e5 });

	//cm.addClient(to_string(0));
	//pm.addProduct(to_string(0), 0, 0);
	//pm.addProduct(to_string(1), 1, 1);

	cin.exceptions(ios::failbit | ios::badbit);


	int go = 1;
	do {
		try {
			go = a1.run();
		}
		catch (const std::ios_base::failure& ) {
			cout << "입력 오류입니다. 다시 입력하십시오. 숫자만 입력할 수 있습니다." << endl;
			continue;
		}
	} while (go>=0);

	cout << "종료" << endl;
}