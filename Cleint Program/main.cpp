#include<iostream>
#include "Display.h"
#include "QueryClient.h"
using namespace std;

int main() {
	//for_each(client_list.begin(), client_list.end(), [](Client c) {cout << c << endl; });
	//void addClient(string name, string phone_number = "NONE", string address = "NONE");
	ClientManager cm;
	QueryClient qc{ cm };
	
	Display a1{ "고객관리프로그램"};
	Display b1{ "고객정보관리"};
	Display b2{ "상품정보관리"};
	a1.addChild({ &b1, &b2 });
	Display c1{ "고객추가",  query(qc, &QueryClient::QueryAddClient) };
	Display c2{ "고객삭제", query(qc, &QueryClient::QueryEraseClient) };
	Display c3{ "고객조회",query(qc,&QueryClient::QueryShowClient) };
	b1.addChild({ &c1,&c2,&c3 });

	int go = 1;
	do {
		go = a1.run();
	} while (go>=0);


	cout << "end" << endl;
}