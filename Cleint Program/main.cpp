#include<iostream>
#include "Display.h"
#include "QueryClient.h"
#include "QueryProduct.h"
#include "QueryOrder.h"
using namespace std;

int main() {
	ClientManager cm;
	ProductManager pm;
	OrderManager om{ cm,pm };

	QueryClient qc{ cm };
	QueryProduct qp{ pm };
	QueryOrder qo{ om };

	Display a1{ "고객관리프로그램"};
	Display b1{ "고객정보관리"};
	Display b2{ "상품정보관리"};
	Display b3{ "오더관리" };
	a1.addChild({ &b1, &b2, &b3 });

	Display c1{ "고객추가",  query(qc, &QueryClient::QueryAddClient) };
	Display c2{ "고객삭제", query(qc, &QueryClient::QueryEraseClient) };
	Display c3{ "고객조회",query(qc, &QueryClient::QueryShowClient) };
	b1.addChild({ &c1,&c2,&c3 });

	Display d1{ "상품추가", query(qp, &QueryProduct::QueryAddProduct) };
	Display d2{ "상품제거", query(qp, &QueryProduct::QueryEraseProduct) };
	Display d3{ "상품조회", query(qp, &QueryProduct::QueryShowProduct) };
	b2.addChild({ &d1,&d2,&d3 });

	Display e1 {"오더 추가", query(qo, &QueryOrder::)}

	b3.addChild

	int go = 1;
	do {
		go = a1.run();
	} while (go>=0);


	cout << "end" << endl;
}