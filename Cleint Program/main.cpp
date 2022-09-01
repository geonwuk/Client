#include<iostream>
#include "Display.h"
#include "QueryClient.h"
using namespace std;

int main() {
	//for_each(client_list.begin(), client_list.end(), [](Client c) {cout << c << endl; });
	//void addClient(string name, string phone_number = "NONE", string address = "NONE");
	ClientManager cm;
	QueryClient qc{ cm };
	
	Display a1{ "���������α׷�"};
	Display b1{ "����������"};
	Display b2{ "��ǰ��������"};
	a1.addChild({ &b1, &b2 });
	Display c1{ "���߰�",  query(qc, &QueryClient::QueryAddClient) };
	Display c2{ "������", query(qc, &QueryClient::QueryEraseClient) };
	Display c3{ "����ȸ",query(qc,&QueryClient::QueryShowClient) };
	b1.addChild({ &c1,&c2,&c3 });

	int go = 1;
	do {
		go = a1.run();
	} while (go>=0);


	cout << "end" << endl;
}