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

	QueryClient qc{ cm };//���ø�? Query<Client>,Query<Product>? ������ �̿��� Query��
	QueryProduct qp{ pm };//���? Query�� ��ӹ����� query�Լ����� ù��° ���ڸ� ���� �� �ִ�
	QueryOrder qo{ om };

	Display a1{ "���������α׷�"};
	Display b1{ "����������"};
	Display b2{ "��ǰ��������"};
	Display b3{ "��������" };
	a1.addChild({ &b1, &b2, &b3 });

	//Querychild vs treechild?
	
	Display c1{ "���߰�",  query(qc, &QueryClient::QueryAddClient) };//a1["����������"].addchild{"���߰�", query(...)}���� �ٲ۴�
	Display c2{ "������", query(qc, &QueryClient::QueryEraseClient) };//qc.query?
	Display c3{ "����ȸ",query(qc, &QueryClient::QueryShowClient) };
	Display c4{ "������", query(qc, &QueryClient::QuerySaveClient) };
	Display c5{ "���ε�", query(qc, &QueryClient::QueryLoadClient) };
	b1.addChild({ &c1,&c2,&c3,&c4,&c5 });

	Display d1{ "��ǰ�߰�", query(qp, &QueryProduct::QueryAddProduct) };
	Display d2{ "��ǰ����", query(qp, &QueryProduct::QueryEraseProduct) };
	Display d3{ "��ǰ��ȸ", query(qp, &QueryProduct::QueryShowProduct) };
	Display d4{ "��ǰ����", query(qp, &QueryProduct::QuerySaveProduct) };
	Display d5{ "��ǰ�ε�", query(qp, &QueryProduct::QueryLoadProduct) };
	b2.addChild({ &d1,&d2,&d3,&d4,&d5 });

	Display e1{ "���� �߰�", query(qo, &QueryOrder::QueryAddOrder) };
	Display e2{ "���� ��ȸ", query(qo, &QueryOrder::QueryShowOrder) };
	b3.addChild({ &e1,&e2 });

	cm.addClient(to_string(0));
	//pm.addProduct(to_string(0), 0, 0);
	//pm.addProduct(to_string(1), 1, 1);


	int go = 1;
	do {
		go = a1.run();
	} while (go>=0);


	cout << "end" << endl;
}