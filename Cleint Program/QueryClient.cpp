#include "QueryClient.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "Table.cpp"

using namespace std;
//std::ostream& operator<< (std::ostream& os, const Client& c);
TB::Table QueryClient::table{ "id","name","phone number","address" };

QueryClient::QueryClient(ClientManager& cm) : cm{cm}
{
}

void QueryClient::QueryAddClient()
{
	string name;
	string phone_number;
	string address;
	cout << "name: ";
	cin >> name;
	cout << "phone number: ";
	cin >> phone_number;
	cout << "address: ";
	cin >> address;
	cm.addClient(name, phone_number, address);
	auto c = cm.getCleints();
	unsigned int id = (--c.end())->first;
	table.setFields({ to_string(id),name,phone_number,address });
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

void QueryClient::QueryShowClient()
{
	table.print_header();
	auto m = cm.getCleints();
	for (auto& itr : m) {
		const Client& c = itr.second;
		table.print({ std::to_string(c.getId()), c.getName(),c.getPhoneNumber(),c.getAddress()});
	}
	table.print_tail();
}
//std::ostream& operator<< (std::ostream& os, const Client& c) {
//	cout << "id: " << c.getId() << " ";
//	cout << "Name: " << c.getName()<<" ";
//	cout << "Phone: " << c.getPhoneNumber()<<" ";
//	cout << "Address: " << c.getAddress()<<" ";
//	return os;
//}