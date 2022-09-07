#include "QueryClient.h"
#include <iostream>
#include <string>
#include  <fstream>
#include <iomanip>

using namespace std;
using namespace CM;

TB::Table QueryClient::table{ "id","name","phone number","address" }; //����ȸ�� ����� ���̺� �ʵ���� �Է��Ѵ�

QueryClient::QueryClient(ClientManager& cm) : cm{cm} {}

void QueryClient::QueryAddClient(){
	QueryShowClient();
	string name;
	string phone_number;
	string address;
	cout << "name: ";
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	getline(cin, name);
	cout << "phone number: ";
	getline(cin, phone_number);
	cout << "address: ";
	getline(cin, address);
	cm.addClient(name, phone_number, address);

	unsigned int id = cm.getMaxIndex();
	table.setFields({ to_string(id),name,phone_number,address });
	//�߰��� Client�� �� �ʵ庰(id, name, phone_number, address)�� �ִ���̸� �˱� ���� setFields�� ȣ���Ѵ�
}

void QueryClient::QueryEraseClient()
{
	QueryShowClient();
	unsigned int id;
	cout << "������ Ŭ���̾�Ʈ id: ";
	cin >> id;
	bool success = cm.eraseClient(id);
	if (success) {
		cout <<"ID:" << id << " Ŭ���̾�Ʈ ���� �Ϸ�" << endl;
	}
	else {
		cout <<"ID:"<< id << " Ŭ���̾�Ʈ�� �������� �ʽ��ϴ�. ���� ����" << endl;
	}
}

void QueryClient::QueryShowClient(){
	table.printHeader();
	auto m = cm.getCleints();		      //map::iterator
	for (auto itr : m) {
		const Client& c = itr.second;     //iterator�κ��� client ��ü�� �޴´�
		table.print({ std::to_string(c.getId()), c.getName(),c.getPhoneNumber(),c.getAddress()}); //���̺��������� ���
	}
	table.printTail();
}


void QueryClient::QuerySaveClient() {
	std::ofstream out("Clients.txt");
	cm.saveClients(out);				//ClientManager�� ������ ����Ѵ�										
}

void QueryClient::QueryLoadClient(){										//���� �ҷ����� �޼ҵ�
	std::ifstream in{ "Clients.txt" };										//clients.txt�� ����
	auto pr = cm.loadClients(in);											//clientManager���� ���Ͽ� ����� Client���� ���ͷ� ������ ���� �޴´�.
	for (auto& i : pr.second) {												
		cm.addClient(i.getName(), i.getPhoneNumber(), i.getAddress());		//���Ͽ��� Client �ҷ��� ������ �߰��Ѵ�.
		unsigned int new_id = cm.getMaxIndex();												  
		table.setFields({ to_string(new_id),i.getName(),i.getPhoneNumber(),i.getAddress() }); //id, name, phone_number, address
		//�߰��� �׸�鿡 ���� �ִ� ���ڿ� ���̸� �� �ʵ庰�� �ľ��ؼ� table ��ü�� �����Ѵ�
	}
}